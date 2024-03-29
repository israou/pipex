/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israachaabi <israachaabi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:07:36 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/29 03:50:51 by israachaabi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_strncpy(char *s1, char *s2, int n)
{
	int i = 0;
	while (s2[i] && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return(s1);
}

char	**ft_split_spaces(char *str)
{
	char **otp;
	int wrd = 0;
	int ptr = 0;
	int i = 0;
	int j;

	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wrd++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	}
	otp = malloc((wrd + 1) * sizeof(char *));
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	j = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	if (i > j)
	{
		otp[ptr] = malloc(i - j + 1);
		ft_strncpy(otp[ptr++], &str[j], i - j);
	}
	}
	otp[ptr] = NULL;
	return (otp);
}
