/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israachaabi <israachaabi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:08:58 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/29 04:01:09 by israachaabi      ###   ########.fr       */
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
				perror("ERROR\n path, split");
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
			// printf(2, "%s\n", cmd_w_slash);
			free(tmp);
			if (cmd_w_slash && access(cmd_w_slash, F_OK | X_OK) == 0)
				return (cmd_w_slash);
			free(cmd_w_slash);
		}
		i++;
	}
	return (NULL);
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
}
void	redirect_output(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}
void	redirect_multiples_cmd(t_data *arg, int ac, char **av)
{
	int	i;
	int	fd[2];

	i = 2;
	arg->cmd = add_slash_to_path(arg);
	arg->prcss = count_commands(av, ac);
	while (i < ac - 1)
	{
		if (pipe(fd) == -1)
			errors("ERROR CREATION FAILED");
		arg->cmds = ft_split_spaces(av[i]);
		if (i != 2)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		else
			redirect_input(arg, &av[1]);
		if (i != ac - 2)
			redirect_output(fd);
		execute_cmds(arg, ac, av);
		exit(EXIT_SUCCESS);
		i++;
	}
}

void	execute_cmds(t_data *arg, int ac, char **av)
{
	pid_t	pid;

	while (arg->prcss)
	{
		pid = fork();
		if (pid == -1)
			errors("FORK FAILED");
		else if (pid == 0)
			redirect_multiples_cmd(arg, ac, av);
		else
			waitpid(pid, NULL, 0);
		arg->prcss--;
	}	
}

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

int main(int ac, char **av, char **env)
{
	t_data *arg;
	arg = (t_data *)malloc(sizeof(t_data));
	if (!arg)
		perror("MEMORY ALLOCATION FAILED!\n");
		exit(EXIT_FAILURE);
	arg->env = env;
	if (ac <= 5)
		errors("y a pas assez de commandes\n");
	while (ac >= 6)
	{
		puts("israa");
		execute_cmds(arg, ac, av);	
	}
}
	//while (arg->prcss)
	//{
	//	pid = fork();
	//	arg->prcss--;


	//arg->input_file = open(av[1], O_RDONLY, 0666);
			//if (arg->input_file == -1)
			//{
			//	perror("ERROR OPENING INPUT FILE");
			///	continue;
			//}
			//dup2(arg->input_file, STDIN_FILENO);