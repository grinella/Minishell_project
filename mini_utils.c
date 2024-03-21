/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:06:26 by grinella          #+#    #+#             */
/*   Updated: 2024/03/20 16:06:27 by grinella         ###   ########.fr       */
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
void	put_env(t_mini *mini, char **env)
{
	int	i;
	int	m_len;

	i = 0;
	m_len = ft_count_matrix(env);
	mini->env = ft_calloc(m_len + 1, sizeof(char **));
	while (env[i] != NULL)
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = NULL;
}
