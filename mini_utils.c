/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:06:26 by grinella          #+#    #+#             */
/*   Updated: 2024/04/05 15:46:50 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

//crea la copia di una matrice
char	**ft_mtr_copy(t_mini *mini)
{
	int		i;
	char	**mtr_copy;

	i = 0;
	mtr_copy = ft_calloc((ft_count_mtr(mini->env) + 1), sizeof (char **));
	while (mini->env[i] != NULL)
	{
		mtr_copy[i] = ft_strdup(mini->env[i]);
		i++;
	}
	mtr_copy[i] = NULL;
	return (mtr_copy);
}

//numero di stringhe in una matrice
int	ft_count_mtr(char **matrix)
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
	m_len = ft_count_mtr(env);
	mini->env = ft_calloc(m_len + 1, sizeof(char **));
	while (env[i] != NULL)
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = NULL;
}

int	check_errors(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i][0] == '>' || matrix[i][0] == '<')
		{
			if ((matrix[i + 1] == NULL && i == 0) || matrix[i + 1] == NULL || \
				matrix[i + 1][0] == '|')
			{
				printf("ERROR: parse error\n");
				return (-1);
			}
		}
		i++;
	}
	i--;
	if (i < 0)
		return (-1);
	if (matrix[i][0] == '|')
	{
		printf("ERROR: parse error\n");
		return (-1);
	}
	return (0);
}
