/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:03:52 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/04 17:35:44 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	read_the_input(t_data *arg, int *fd)
{
	char	*line;
	while (1)
	{
		line = get_next_line(0);
		if (line[0] == '\0' || line == NULL)
		{
			free(line);
			continue;
		}
		if (ft_strcmp(line, arg->limiter) == 0)//ila lqa limiter av[2]
		{
			free(line);
			// close(fd); fermer avant d executer
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}
// Si la ligne ne correspond pas au limiter
// elle est écrite dans le descripteur de fichier fd[1]
//qui est généralement le côté d'écriture d'un tube (pipe)
//Cela signifie que cette ligne sera écrite dans le tube pour être lue par un autre processus.

void	create_here_doc(t_data *arg, int ac, char **av)
{
	pid_t	pid;
	int		fd[2];
	(void)ac;

	pid = 0;
	if (pipe(fd) == -1)
		errors("pipe failed\n"),
	pid = fork();
	if (pid == -1)
		errors("echec lors de la creation du process child\n");
	if (pid == 0)//child
	{
		arg->cmd1 = add_slash_to_path(arg);
		close(fd[0]);//fermer l extremite de lecture du pipe
		dup2(fd[1], STDOUT_FILENO);//rediriger la sortie standard vers le pipe
		close(fd[1]);
		read_the_input(arg, fd);
		execve(arg->cmd1, arg->content, arg->env);
		errors("execve process child here_doc failed\n");
	}
	else//parent
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO); // Rediriger l'entrée standard vers le tube,, lire depuis pipe cmd1
		close(fd[0]);
		arg->content = ft_split_spaces(av[4]);
		execute_cmd_two(arg, ac, av);
		wait(NULL);
	}
}

void	execute_cmd_two(t_data *arg, int ac, char **av)
{
	arg->cmd2 = add_slash_to_path(arg);
	arg->output_file = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (arg->output_file == -1)
		errors("error opening output file for here_doc\n");
	if (execve(arg->cmd2, arg->content, arg->env) == -1)
		errors("error executing command\n");
}

// here-doc est un bloc de texte délimité par une chaîne de caractères spécifique (LIMITER dans ce cas).

// int main(t_data *arg, int ac, char **av)
// {
// 	if (ft_strncmp(av[1], "here_doc", 8) == 0)
// 	{
// 		arg->here_doc = av[1];
// 		arg->limiter = av[2];
// 		arg->cmd1 = av[3];
// 		arg->cmd2 = av[4];
// 		create_here_doc(arg, ac, av);
// 	}
// 	else
//  		errors("nononono\n");
// }
