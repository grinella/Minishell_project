/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:06:26 by grinella          #+#    #+#             */
/*   Updated: 2024/04/03 20:00:21 by ecaruso          ###   ########.fr       */
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
	if (matrix[i][0] == '|')
	{
		printf("ERROR: parse error\n");
		return (-1);
	}
	return (0);
}
