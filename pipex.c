/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:39:34 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/22 14:58:00 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	*check_env(t_data *data)
// {
// 	if (data->path == NULL)
// 		perror("Error\n ENV");
// 		exit(EXIT_FAILURE);
// 	if (ft_strchr(data->cmd_p, '/'))
// 	{
// 		if (access(data->cmd_p, F_OK | X_OK) == 0)
// 			return (data->cmd_p);
// 	}
// 	return (NULL);
// }
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
			else
				perror("ERROR\n path, split");
				exit(EXIT_FAILURE);
		}
		i++;
	}
	return (NULL);
}

//PATH contient une liste de répertoires où le système recherche les exécutables
//access()vérifie si le programme peut accéder au fichier pathname

char	*add_slash_to_path(t_data *arg)
{
	int		i;
	char	*tmp;
	char	*cmd_w_slash;

	i = 0;
	cmd_w_slash = NULL;
	whereis_paths(arg);
	while (arg->path[i])
	{
		tmp = ft_strjoin(arg->path[i], "/");
		if (tmp)
		{
			cmd_w_slash = ft_strjoin(tmp, arg->cmd_p);
			free(tmp);
			if (cmd_w_slash && access(cmd_w_slash, F_OK | X_OK) == 0)
			return (cmd_w_slash);
		// free(cmd_w_slash);
		}
		i++;
	}
	return (NULL);
}

//Par exemple, si arg->path[i] est "/usr/bin" et arg->cmd_p est "ls"
// la fonction crée un nouveau chemin "/usr/bin/ls",
// représentant le chemin complet de la commande "ls" située dans le répertoire "/usr/bin"


void	process_child1(int *fd, char *av[], char *env[])
{
	t_data	*arg;

	close(fd[0]);//processchild1 ne lira pas a partir du | car il doit se concentrer sur la lecture a partir de fichier d entrée specifiéas
	arg->input_file = open(av[1], O_RDONLY, 0666);//ouvrir le fichier d entrée en lecture seule
	if (arg->input_file == -1)
	{
		perror("ERROR OPENING INPUT FILE\n");
		process_child2(arg, av, env);//cat | ls
	}
	//redirection de l'entrée strandard
	if (dup2(arg->input_file, STDIN_FILENO) == -1)
	{
		perror("ERROR IN REDIRECTION VERS STDIN\n");
		close(arg->input_file);
		process_child2(arg, av, env);//n exit
	}
	close(arg->input_file);//fermer le fichier d entrée apres redirection
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("ERROR IN REDIRECTION VERS STDOUT");
		process_child2(arg, av, env);//n exit
	}
	// execve(av[2], &av[2], env);//executer la cmd1
	perror("ERREUR LORS DE L'EXECUTION DE LA 1ERE CMD");
	process_child2(arg, av, env);
}

void	process_child2(int *fd, char *av[], char *env[])
{
	t_data	*arg;

	close(fd[1]);//fermer le fd stoutput,, il n ecrira pas dans |
	arg->output_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);//O_TRUNC vide le fichier avant son ouverture
	if (arg->output_file == -1)
		errors("ERROR OPENING OUTPUT FILE");
	if (dup2(arg->output_file, STDOUT_FILENO) == -1)
	{
		perror("ERROR IN REDIRECTIOON VERS STDOUT\n");
		close(arg->output_file);
		exit(EXIT_FAILURE);
	}
	close(arg->output_file);//fermer en cas de succês
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		errors("ERROR IN REDIRECTION VERS STDIN");
	}
	execve(av[3], &av[3], env);
	errors("ERREUR LORS DE L'EXECUTION DE LA CMD2");
}

int main()
{
	pid_t pid;

    printf("Fork ici.\n");
    pid = fork();
    if (pid == -1)
    {
        // Si fork renvoie -1, il y a eu une erreur !
        return (1);
    }
    printf("\nFork reussi !\n");
    if (pid == 0)
    {
        // La valeur de retour de fork
        // est 0, ce qui veut dire qu'on est
        // dans le processus fils
        printf("Fils : Je suis le fils, mon pid interne est %d.\n", pid);
    }
    else if (pid > 0)
    {
        // La valeur de retour de fork
        // est différente de 0, ce qui veut dire
        // qu'on est dans le processus père
        printf("Pere : Je suis le pere, le pid de mon fils est %d.\n", pid);
    }
    return(0);
}
// int main(int ac, char **av, char **env) {
//     // char *cmd_path;
//     // char *options[3] = {"ls", "-la", NULL};
// 	// t_data arg;
// 	// arg.cmd = "ls";

//     // (void)ac;
//     // (void)av;

// 	// arg.env = env;
// 	// cmd_path = NULL;

// 	// arg.path = whereis_paths(&arg);
// 	// if (arg.path)
// 	// 	add_slash_to_path(&arg);


//     // execve(cmd_path, options, env);
//     // perror("Error in execve!\n");
//     // free(cmd_path);
//     // return(0);
// }

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

