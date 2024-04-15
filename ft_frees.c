/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:15:51 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/14 23:01:04 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	free_cmd(char **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		free(exp[i]);
		i++;
	}
	free(exp);
}