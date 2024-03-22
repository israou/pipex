/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:37:53 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/21 01:55:20 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_fd(t_data *arg)
{
	int	fd;

	close(arg->input_file);
	close(arg->output_file);
	close(arg->fd[0]);//je ferme les deux extremités du pipe
	close(arg->fd[1]);
}
// ferme les fd associés aux entrées (arg->input_file) et (arg->output_file)
//ainsi que les deux extrémités du tube (arg->fd[0] et arg->fd[1])

void	file_protect(t_data *arg)
{
	if (arg->fd[0] < 0 || arg->fd[1] < 0)
	{
		close_all_fd(arg);
		if (arg->fd[0] < 0)
			errors("file unreadable");
		if (arg->fd[1] < 0)
			errors("unable to create output file");
	}
}
