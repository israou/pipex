/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israachaabi <israachaabi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:03:21 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/29 03:45:36 by israachaabi      ###   ########.fr       */
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
void	execute_cmds(t_data *arg, int i, int *fd, int ac, char **av);



#endif