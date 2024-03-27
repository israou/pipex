/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:03:52 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/27 01:25:45 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	read_the_input(int *fd, char **limiter, char *line)
{
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(*line, limiter, ft_strlen(*line - 1) == 0))//ila lqa limiter
			exit(EXIT_SUCCESS);
		write(fd[1], *line, ft_strlen(*line));
	}
}
// Si la ligne ne correspond pas au limiter
// elle est écrite dans le descripteur de fichier fd[1]
//qui est généralement le côté d'écriture d'un tube (pipe)
//Cela signifie que cette ligne sera écrite dans le tube pour être lue par un autre processus.

void	use_here_doc(char *limiter, int ac)
{
	pid_t	pid;
	char	*line;
	int		fd[2];

	if (ac < 6)
		errors("INSUFFISANT\n");
	if (pipe(fd) == -1)
		errors("pipe failat\n");
	pid = fork();
	if (pid == -1)
		errors("echec lors de la creation du process child\n");
	if (pid == 0)
	{
		close(fd[0]);
		read_the_input(fd, limiter, &line);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	wait(NULL);
}
void	here_doc_args(t_data *arg, int ac, char ***av, int *fd, int *r)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		*r = 3;
	}
}