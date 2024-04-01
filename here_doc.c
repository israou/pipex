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

void	read_the_input(t_data *arg)
{
	int		*fd;
	char	*line;
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(*line, arg->limiter, ft_strlen(*line) - 1) == 0)//ila lqa limiter av[2]
		{	
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], *line, ft_strlen(*line));
		free(line);
	}
}
// Si la ligne ne correspond pas au limiter
// elle est écrite dans le descripteur de fichier fd[1]
//qui est généralement le côté d'écriture d'un tube (pipe)
//Cela signifie que cette ligne sera écrite dans le tube pour être lue par un autre processus.

void	create_here_doc(t_data *arg, int ac, char ***av)
{
	int	in;

	in = dup(STDIN_FILENO);
	if (ac < 5)
		errors("insuffisant pour here_doc\n");
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		arg->here_doc = open(arg->here_doc, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (arg->here_doc == -1)
		{
			errors("ERROR CREATING HEREDOC\n");
		}
		dup2(in, STDIN_FILENO);
		read_the_input(arg);
		close(arg->here_doc);
		close(in);
	}
}

void	use_here_doc(t_data *arg, int ac)
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
		read_the_input(arg);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	wait(NULL);
}


int main(t_data *arg, int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		arg->here_doc = av[1];
		arg->limiter = av[2];
	}
	else
		errors("nononono\n");
}