/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:03:52 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/06 02:42:32 by ichaabi          ###   ########.fr       */
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
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}
// Si la ligne ne correspond pas au limiter
// elle est écrite dans le descripteur de fichier fd[1]
//qui est généralement le côté d'écriture d'un tube (pipe)
//Cela signifie que cette ligne sera écrite dans le tube pour être lue par un autre processus.

// here-doc est un bloc de texte délimité par une chaîne de caractères spécifique (LIMITER dans ce cas).

void	here_doc(t_data *arg, int ac, char **av)
{
	int		pid;
	int		fd[2];

	if (ac < 6)
		errors("INVALID\n");
	if (pipe(fd) == -1)
		errors("pipe failed");
	pid = fork();
	if (pid == -1)
		errors("fork failed");
	printf("pid  === %d\n", pid);
	if (pid == 0)
	{
		printf("child 1 process\n");
		close(fd[0]);//je ferme l extremité de lecture du pipe
		read_the_input(arg, fd);//lire stdin
	}
	printf("PARENT 1 process\n");//aytaficha parent en attendant la fin du process child
	dup2(fd[0], 0);//rediriger la lecture vers stdin du pipe
	close(fd[1]);//fermer l extremite inutilisee du pipe
	wait(NULL);//wait la fin du process child1

//----fork 2
	fork_for_execute(arg, ac, av);
}

void	fork_for_execute(t_data *arg, int ac, char **av)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		errors("pipe failed");
	// printf("pid 3awtanii  === %d\n", pid);
	pid = fork();
	if (pid == -1)
		errors("fork failed");
	if (pid == 0)
	{
		printf("child 2 process\n");
		arg->content = ft_split_spaces(av[3]);
		arg->cmd1 = add_slash_to_path(arg);
		close(fd[0]);
		dup2(fd[1], 1);//bash ankteb flpipe l output dial l execution dial l cmd1
		execve(arg->cmd1, arg->content, arg->env);
	}
	printf("PARENT 2 process\n");//donc ayt afficha parent wi wait la fin du process fils
	dup2(fd[0], 0);
	close(fd[1]);
	wait(NULL);

	arg->content = ft_split_spaces(av[4]);
	execute_cmd_two(arg, ac, av);
}

void	execute_cmd_two(t_data *arg, int ac, char **av)
{
	arg->cmd2 = add_slash_to_path(arg);
	arg->output_file = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	dup2(arg->output_file, 1);
	if (arg->output_file == -1)
		errors("error opening output file for here_doc\n");
	if (execve(arg->cmd2, arg->content, arg->env) == -1)
		errors("error executing command\n");
}


















// void	here_doc(t_data *arg, int ac, char **av)
// {
// 	int		pid;
// 	int		fd[2];

// 	if (ac < 6)
// 		errors("INVALID\n");
// 	if (pipe(fd) == -1)
// 		errors("pipe failed");
// 	pid = fork();
// 	if (pid == -1)
// 		errors("fork failed");
// 	printf("pid  === %d\n", pid);
// 	if (pid == 0)
// 	{
// 		printf("child 1 process\n");
// 		close(fd[0]);//je ferme l extremité de lecture du pipe
// 		read_the_input(arg, fd);//lire stdin
// 	}
// 	printf("PARENT 1 process\n");
// 	dup2(fd[0], 0);//rediriger la lecture vers stdin du pipe
// 	close(fd[1]);//fermer l extremite inutilisee du pipe
// 	wait(NULL);//wait la fin du process child1

// //----fork 2

// 	if (pipe(fd) == -1)
// 		errors("pipe failed");
// 	printf("pid 3awtanii  === %d\n", pid);
// 	pid = fork();
// 	if (pid == -1)
// 		errors("fork failed");
// 	if (pid == 0)
// 	{
// 		printf("child 2 process\n");
// 		arg->content = ft_split_spaces(av[3]);
// 		arg->cmd1 = add_slash_to_path(arg);
// 		close(fd[0]);
// 		dup2(fd[1], 1);
// 		execve(arg->cmd1, arg->content, arg->env);
// 	}
// 	printf("PARENT 2 process\n");
// 	dup2(fd[0], 0);
// 	close(fd[1]);
// 	wait(NULL);

// 	arg->content = ft_split_spaces(av[4]);
// 	execute_cmd_two(arg, ac, av);
// }
