/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:08:58 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/27 03:50:21 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**whereis_paths(t_data *arg)
{
	int		i;

	i = 0;

	while (arg->env[i])
	{
		if (ft_strncmp(arg->env[i], "PATH", 4) == 0)
		{
			arg->path = ft_split(arg->env[i] + 5, ':');
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

char	*add_slash_tpath(t_data *arg)
{
	int		i;
	char	*tmp;
	char	*cmd_w_slash;

	i = 0;
	cmd_w_slash = NULL;
	arg->path = whereis_paths(arg);
	while (arg->path[i])
	{
		tmp = ft_strjoin(arg->path[i], "/");
		if (tmp)
		{
			cmd_w_slash = ft_strjoin(tmp, arg->content[0]);
			// printf(2, "%s\n", cmd_w_slash);
			free(tmp);
			if (cmd_w_slash && access(cmd_w_slash, F_OK | X_OK) == 0)
				return (cmd_w_slash);
			free(cmd_w_slash);
		}
		i++;
	}
	return (NULL);
}


// int	count_cmd(t_data *arg)
// {
// 	int	i;
// 	int	count;

// 	i = 2;
// 	count = 0;
// 	while (arg->cmds[i])
// 	{
// 		count++;
// 		i++;
// 	}
// 	if (count == 0)
// 		errors("NO COMMANDS!!\n");
// 	return (count);
// }

void	multiples_cmd(t_data *arg, int ac, char **av)
{
	int	i;
	pid_t	pid;

	i = 2;
	if (ac <= 5)
		errors("y a pas assez de commandes\n");
	arg->path = add_slash_to_path(arg);
	int prcss = ac - 3;
	while(av[i])
	{
		arg->cmds = ft_split_spaces(av[i]);
		i++;
	}
	i = 2;
	while (prcss)
	{
		pid = fork();
		prcss--;
	}
}

int main(int ac, char **av, t_data *arg)
{
	t_data	*arg;
	arg = (char **)malloc(sizeof(t_data));

}