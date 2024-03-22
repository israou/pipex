/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:15:51 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/21 02:03:18 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(t_data *arg)
{
	int	i;

	i = 0;
	if (!arg->path)

		return ;
	while (arg->path[i])
	{
		free(arg->path[i]);
		i++;
	}
	free(arg->path);
}
void	free_cmd(t_data *arg)
{
	int	i;

	i = 0;
	if (!arg->cmd)
		return ;
	while (arg->cmd[i])
	{
		free(arg->cmd[i]);
		i++;
	}
	free(arg->cmd);
}