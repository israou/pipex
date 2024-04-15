/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:39:34 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/15 22:53:15 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_child1(t_data *arg, int *fd, char *av[])
{
	arg->content = ft_split_spaces(av[2]);
	close(fd[0]);
	arg->input_file = open(av[1], O_RDONLY, 0666);
	if (arg->input_file == -1)
	{
		close_and_print_error(fd, 1, "ERROR OPENING INPUT FILE\n");
		process_child2(arg, fd, av);//cat | ls
	}
	//redirection de l entree standard vers le fichier d entree
	//Crée un duplicata du descripteur de fichier du fichier d'entrée (arg->input_file).
	//Place ce duplicata à l'emplacement de l'entrée standard (STDIN_FILENO)
	if (dup2(arg->input_file, STDIN_FILENO) == -1)//constante predefinie 0,, toutes lecture lira le contenu du fichier d entree av[1]
	{
		close_and_print_error(fd, arg->input_file, "ERROR IN REDIRECTION VERS STDIN\n");
		process_child2(arg, fd, av);
	}
	close(arg->input_file);
	if (dup2(fd[1], STDOUT_FILENO) == -1)//l output likikhrej khass ndewzo lpipe bash tqrah lcommande lakhra
	{
		close_and_print_error(fd, 1, "ERROR IN REDIRECTION VERS STDOUT");
		process_child2(arg, fd, av);//n exit
	}
	close(fd[1]);
	execute_command(arg);
	perror("ERREUR LORS DE L'EXECUTION DE LA 1ERE CMD");
	process_child2(arg, fd, av);
}

void	process_child2(t_data *arg, int *fd, char *av[])
{
	arg->content = ft_split_spaces(av[3]);
	close(fd[1]);//fermer le fd stoutput,, il n ecrira pas dans |
	arg->output_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);//O_TRUNC vide le fichier avant son ouverture
	if (arg->output_file == -1)
		errors("ERROR OPENING OUTPUT FILE");
	if (dup2(arg->output_file, STDOUT_FILENO) == -1)//cree duplicate dial output_file et le pace a l emplacement de stdout,, cela redirige toutess les ecritures a la stdout
	{
		perror("ERROR IN REDIRECTIOON VERS STDOUT\n");
		close(arg->output_file);
		exit(EXIT_FAILURE);
	}
	close(arg->output_file);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		errors("ERROR IN REDIRECTION VERS STDIN\n");
		close(fd[0]);
	}
	close(fd[0]);
	execute_command_two(arg);
	errors("ERREUR LORS DE L'EXECUTION DE LA CMD2");
}

void	execute_command(t_data *arg)
{
	arg->cmd = add_slash_to_path(arg);
	if (!arg->cmd)
		errors("Error\n --lors de la verification de la validité de la premiere commande--\n");
	execve(arg->cmd, arg->content, arg->env);
	errors("ERROR EXECUTING COMMAND 1\n");
}

void	execute_command_two(t_data *arg)
{
	arg->cmd2  = add_slash_to_path(arg);
	if (!arg->cmd2)
		errors("Error\n --lors de la verification de la validité de la deuxième commande--\n");
	execve(arg->cmd2, arg->content, arg->env);
	errors("ERROR EXECUTING COMMAND 2\n");
}

void	f()
{
	system("leaks pipex");
}

int main(int ac, char **av, char **env)
{
	atexit(f);
	t_data	*arg;

	arg = (t_data *)malloc(sizeof(t_data));
	if (arg == NULL)
		errors("ARG ALLOCATION\n");
	arg->env = env;
	arg->cmd = av[2];
	arg->cmd2 = av[3];
	if (ac == 5)
	{
		generate_processes(av, arg);
	}
	else
	{
		perror("FAILURE\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

//exemples
// step 1:
// 	PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
// step 2:
// 	path[0] = "/usr/local/bin/"
// 	path[1] = "/usr/bin/"
// 	path[2] = "/bin/"
// 	path[3] = "/usr/sbin/"
// 	path[4] = "/sbin/"
// 	path[5] = NULL


//Le descripteur de fichier fd[1] reste ouvert car il est utilisé par le processus parent pour écrire dans le pipe.
//La fermeture de fd[0] n'affecte pas la capacité de process_child1 à lire depuis le fichier d'entrée av[1].
//Il est important de toujours fermer les descripteurs de fichiers lorsqu'ils ne sont plus utilisés afin de garantir une utilisation efficace des ressources système.


//fd[0] correspond à l'extrémité de lecture du pipe créé par pipe().
//En fermant fd[0], le processus process_child1 s'assure qu'il ne lira jamais les données du pipe.
//Cela est crucial car process_child1 doit se concentrer uniquement sur la lecture du fichier d'entrée spécifié (av[1]).
