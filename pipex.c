/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:39:34 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/19 01:30:04 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"







//---------------------------------------------------
char	**whereis_paths(t_data *arg)
{
	int		i;//parcourt la variable env,, puis les chemins extraits de paths

	i = 0;
	while (arg->env[i])
	{
		if (ft_strncmp(arg->env[i], "PATH", 4) == 0)
		{
			arg->path = ft_split(arg->env[i] + 5, ':');//deplacer le pointeur de 5 positions pour eliminer PATHS=
			if (arg->path)
				return (arg->path);
		}
		i++;
	}
	return (NULL);
}

void	add_slash_to_path(t_data *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	whereis_paths(arg);
	while (arg->path[i])
	{
		tmp = ft_strjoin(arg->path[i], "/");
		// free(arg->path[i]);
		arg->path[i] = tmp;
		i++;
	}
}
char *valid_cmd(t_data *arg)
{
	int		i;

	i = 0;
	arg->cmd = arg->cmd;
	whereis_paths(arg);
	if (!(arg->path))
		return (NULL);
	while (arg->path[i]) // Tant qu'il y a un chemin a tester
	{
		arg->cmd_p = ft_strjoin(arg->path[i], arg->cmd);// j ajoute ma commande à la fin de la ligne
		if (!(arg->cmd_p))
		{
			perror("UNEXPECTED ERROR\n");
			exit(EXIT_FAILURE);
		}
		if (access(arg->cmd_p, F_OK | X_OK) == 0)// On teste si le chemin est accessible et executable
			return (arg->cmd_p);
		// free(arg->cmd_p);// Sinon, on free notre variable pour recommencer
		i++;
	}
	return (NULL);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	if (!path)

		return ;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}


int main(int ac, char **av, char **env) {
    char *cmd_path;
    char *options[3] = {"ls", "-la", NULL};
	t_data arg;
	arg.cmd = "ls";

    (void)ac;
    (void)av;

	arg.env = env;

	arg.path = whereis_paths(&arg);
	if (arg.path)
		add_slash_to_path(&arg);

    cmd_path = valid_cmd(&arg);
    if (!cmd_path) {
        perror("Error!\n");
        return(-1);
    }

    execve(cmd_path, options, env);
    perror("Error in execve!\n");
    free(cmd_path);
    return(0);
}



//exemples
// step 1:
// 	PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
// step 2:
// 	path[0] = "/usr/local/bin/"
// 	path[1] = "/usr/bin/"
// 	path[2] = "/bin/"
// 	path[3] = "/usr/sbin/"
// 	path[4] = "/sbin/"
// 	path[5] = NULL
// int main(int ac, char **av, char **envp)
// {
// 	char *options[3] = {"ls", "-la", NULL};

// 	(void)ac;
// 	(void)av;
// 	execve("/bin/ls", options, envp);
// 	return (0);
// }

// int main(int ac, char **av, char **env)
// {
// 	int	i;

// 	i = 0;
// 	if (ac == 5)
// 	{

// 	}
// 	else
// 		perror("FAILURE");
// 	exit(EXIT_FAILURE);
// }

// char	**parsing(char **av)
// {
// 	int	i;
// 	char	**splitted_args;

// 	i = 0;
// 	splitted_args = ft_split(av, ' ');
// 	if (splitted_args == NULL)
// 		perror("Error\nSPLITTED_ARGS");
// 		exit(EXIT_FAILURE);
// 	return (splitted_args);
// }