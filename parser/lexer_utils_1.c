/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:56:54 by grinella          #+#    #+#             */
/*   Updated: 2024/03/18 16:22:44 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	question_mark(int *len, int *i, int *j, t_mini *mini)
{
	*len++;
	if (mini->input[*len] == '\0' || mini->input[*len] == ' ')
	{
		*i = *len;
		*j += ft_strlen(mini->str_exit_status);
		return (1);
	}
	while (mini->input[*len] != ' ')
	{
		*len++;
		(*j)++;
		if (mini->input[*len] == ' ' || mini->input[*len] == '\0')
		{
			*i = *len;
			return (1);
		}
	}
	return (0);
}

// env condition
int	e_c(t_mini *mini, int len)
{
	if ((mini->input[len] >= 'a' && mini->input[len] <= 'z')
		|| (mini->input[len] >= 'A' && mini->input[len] <= 'Z')
		|| (mini->input[len] >= '0' && mini->input[len] <= '9')
		|| (mini->input[len] == '_'))
		return (1);
	return (0);
}

void	find_dollar_env_len(int *i, int *j, t_mini *mini)
{
	int	r;
	int	c;
	int	len;

	r = 0;
	c = 0;
	len = *i;
	if (mini->input[*i] == '$' && len++)
	{
		if (mini->input[len] == '?')
		{
			if (question_mark(&len, i, j, mini) == 1)
				return ;
		}
		while (mini->env[r] != NULL)
		{
			while ((mini->input[len] == mini->env[r][c]) && e_c(mini, len) == 1)
			{
				c++;
				len++;
			}
			if (mini->env[r][c] == '='
				&& ((mini->input[len] < 'a' || mini->input[len] > 'z')
				&& (mini->input[len] < 'A' || mini->input[len] > 'Z')
				&& (mini->input[len] < '0' || mini->input[len] > '9')
				&& (mini->input[len] != '_')))
			{
				c++;
				(*j)++;
				while (mini->env[r][c] != '\0')
				{
					c++;
					(*j)++;
				}
				if (mini->env[r][c] == '\0')
				{
					*i = len;
					return ;
				}
			}
			else
			{
				r++;
				c = 0;
				if (mini->env[r] == NULL)
				{
					while (e_c(mini, len) == 1)
						len++;
					*i = len;
					return ;
				}
				len = *i + 1;
			}
		}
	}
}
