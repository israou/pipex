/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:09:19 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/15 22:25:32 by ichaabi          ###   ########.fr       */
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
			{
				perror("ERROR\n path, split");
				exit(EXIT_FAILURE);
			}
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
			{
				free_path(arg);
				return (cmd_w_slash);
			}
			free(cmd_w_slash);
		}
		i++;
	}
	return (NULL);
}

void	free_path(t_data *arg)
{
	int	j;

	j = 0;
	while(arg->path[j])
		free(arg->path[j++]);
	free(arg->path);
}
