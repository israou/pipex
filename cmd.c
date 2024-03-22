/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:55:31 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/21 03:35:37 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_cmd(t_data *arg)
{
	if (arg->cmd == NULL)
	{
		free_path(arg);
		free_cmd(arg);
		close_all_fd(arg);
		errors("COMMAND NOT FOUND\n");
	}
	fork();
}
void	initialize_cmd(t_data *arg, char *cmd)
{
	arg->cmd = ft_split(cmd, "");
	check_cmd(arg);
	arg->cmd_p = add_slash_to_path(arg);

}