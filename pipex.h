/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:40:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/19 01:05:15 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include <unistd.h>//open, close, write, read
# include <stdlib.h>//malloc, free, exit
# include <stdio.h>//prerror


typedef struct s_data
{
	char	**path;
	char	**env;
	char	**content;
	char	*cmd;
	char	*cmd_p;
	int		fd1;
	int		fd2;

}			t_data;


int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, char *s2, unsigned int n);
char	**whereis_paths(t_data *data);
char 	*valid_cmd(t_data *arg);
void	add_slash_to_path(t_data *arg);
void	free_path(char **path);



#endif