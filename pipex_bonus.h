/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:03:21 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/04 02:54:51 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif


# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_data
{
	char	**path;
	char	**env;
	char	**content;
	int		input_file;
	int		output_file;
	char	*cmd_w_slash;
	char	**cmds;
	char	*cmd;
	int		prcss;
	int		here_doc;
	char	*limiter;
	char	*cmd1;
	char	*cmd2;
}			t_data;

int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, char *s2, unsigned int n);
void	errors(char	*str);
char	**ft_split_spaces(char *str);
char	**whereis_paths(t_data *arg);
char	*add_slash_to_path(t_data *arg);
int		count_commands(char **args, int ac);
void	redirect_input(t_data *arg, char **av);
void	redirect_output(int *fd);
void	redirect_multiples_cmd(t_data *arg, int ac, char **av);
void	execute_cmds(t_data *arg, int *fd);
void	last_cmd(int ac, char **av, t_data *arg);
//----------------------heredoc
void	read_the_input(t_data *arg, int *fd);
void	create_here_doc(t_data *arg, int ac, char **av);
void	execute_cmd(t_data *arg);
char	*get_next_line(int fd);
char	*divising(char *s, char **reste);
int		checknewline(char *s);
char	*ft_strdup(char *s);
char	*join4gnl(char const *stash, char const *buf);
char	*extraction(char const *s, unsigned int start, size_t len);


// last_cmd(ac, av, arg);
#endif