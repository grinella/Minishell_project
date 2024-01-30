/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:29:45 by eugenio           #+#    #+#             */
/*   Updated: 2024/01/30 17:29:40 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

//numero di stringhe in una matrice
int	ft_count_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		i++;
	}
	return (i);
}
//mette l'env nella struct
void	put_env(t_mini *mini,char **env)
{
    int	i;
	int	m_len;
	
	i = 0;
	m_len = ft_count_matrix(env);
	mini->env = malloc((sizeof(char **) * (m_len)));
	while(env[i] != NULL)
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
}