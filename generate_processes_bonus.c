/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_processes_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:10:17 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/14 18:11:15 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	count_commands(char **args, int ac)
{
	int	i;
	int	prcss;

	i = 2;//start apres l infile
	prcss = 0;
	while (i < ac - 1)//exclure output file
	{
		if (args[i])
			prcss++;
		i++;
	}
	return (prcss);
}

void	redirect_input(t_data *arg, char **av)
{
	arg->input_file = open(av[1], O_RDONLY, 0666);
	if (arg->input_file == -1)
	{
		perror("ERROR OPENING INPUT FILE");
		return ;
	}
	dup2(arg->input_file, STDIN_FILENO);
	close(arg->input_file);
}
void	redirect_output(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	last_cmd(int ac, char **av, t_data *arg)
{
	if (ft_strncmp(av[1], "here_doc", 10) == 0)
		arg->output_file = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		arg->output_file = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (arg->output_file == -1)
		errors("ERROR OPENING FILE\n");
	dup2(arg->output_file, STDOUT_FILENO);
	close(arg->output_file);
}
