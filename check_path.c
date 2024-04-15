/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:19:13 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/15 20:53:26 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
				perror("ERROR\n find path\n");
				exit(EXIT_FAILURE);
		}
		i++;
	}
	return (NULL);
}

char	*add_slash_to_path(t_data *arg)
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
			free(tmp);
			if (cmd_w_slash && access(cmd_w_slash, F_OK | X_OK) == 0)
				return (cmd_w_slash);
			free(cmd_w_slash);
		}
		i++;
	}
	return (NULL);
}

void close_and_print_error(int *fd, int to_close, char *error)
{
	perror(error);
	close(fd[to_close]);
}
