/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:03:21 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/26 01:03:13 by ichaabi          ###   ########.fr       */
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
	char	*firscmd;
	char	*lastcmd;
	int		input_file;
	int		output_file;
	char	*cmd_w_slash;
}			t_data;

int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, char *s2, unsigned int n);
void	errors(char	*str);
char	**ft_split_spaces(char *str);




#endif