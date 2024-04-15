/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:08:58 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/15 01:16:43 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void	redirect_multiples_cmd(t_data *arg, int ac, char **av)
{
	int	i;
	int	fd[2];//tableau contenant deux fd pour le pipe
	int	in;//stocke dup dial stdin
	int	out;//stocke dup dial stdout

	i = 2;
	in = dup(0);//ki saver 0 w 1 aslyin
	out = dup(1);
	arg->prcss = count_commands(av, ac);
	while (i < ac - 1)
	{
		if (i != 2)//si ce n est pas la premiere commande
		{
			dup2(fd[0], STDIN_FILENO);//ncreer duplicate dial input nheto f l emplacement dial stdin,, la cmd suivante lise la sortie de la commande precedente
			close(fd[0]);
		}
		else
			redirect_input(arg, av);
		if (pipe(fd) == -1)
			errors("ERROR CREATION PIPE FAILED\n");
		if (i != ac - 2)
			redirect_output(fd);//mashi akhir commande
		else
		{
			last_cmd(ac, av, arg);
		}
		close(fd[1]);//ferme l extremite d ecriture inutilisee du pipe
		arg->content = ft_split_spaces(av[i]);
		arg->cmd = add_slash_to_path(arg);
		execute_cmds(arg,fd);

		int j = 0;
		while(arg->content[j])
			free(arg->content[j++]);
		free(arg->content);
		free(arg->cmd);
		dup2(in, STDIN_FILENO);//restaurer les fd in et out d origine enregistrés
		dup2(out, STDOUT_FILENO);
		i++;
	}
	i = -1;
	close(fd[1]);//fermer les fd du pipe inutilisées
	close(fd[0]);
	while (++i > arg->prcss)
		wait(NULL);//attendre la fin de tout processus fils
	exit(EXIT_SUCCESS);
}

void	execute_cmds(t_data *arg, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		errors("FORK FAILED\n");
	else if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		// printf("cmd: %s, content: %s\n", arg->cmd, *arg->content);
		if (execve(arg->cmd, arg->content, arg->env) == -1)
			perror("ERROR EXECUTING COMMAND\n");
		exit(EXIT_FAILURE);
	}
}

void	r()
{
	system("leaks pipex_bonus");
}
int main(int ac, char **av, char **env)
{
	atexit(r);
	t_data *arg;

	if (ac < 5)
		errors("NOT ENOUGH ARGUMENTS\n");
	arg = (t_data *)malloc(sizeof(t_data));
	if (!arg)
	{
		errors("MEMORY ALLOCATION FAILED!\n");
	}

	if (ft_strncmp(av[1], "here_doc", 10) == 0)
	{
		arg->env = env;
		arg->limiter = av[2];
		arg->cmd1 = av[3];
		arg->cmd2 = av[4];
		here_doc(arg ,ac, av);
	}
	else if (ft_strncmp(av[1], "here_doc", 10) != 0)
	{
		arg->env = env;
		redirect_multiples_cmd(arg, ac, av);
	}
}

//Le shell crée un pipe.
// Il lance un processus fils qui lit l'entrée standard jusqu'à ce qu'il rencontre un délimiteur spécifié.
// Le processus fils écrit l'entrée lue dans le pipe.
// Le shell lit le pipe et l'utilise comme entrée pour une autre commande.