/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:44:16 by grinella          #+#    #+#             */
/*   Updated: 2024/04/05 16:31:20 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	alloc_double_quotes(int *i, int *j, t_mini *mini)
{
	if (mini->input[*i] == '"')
	{
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
		while (mini->input[*i] != '"' && mini->input[*i] != '\0')
		{
			if (mini->input[*i] == '$')
				alloc_dollar_env(i, j, *i, mini);
			else
			{
				mini->c_input[*j] = mini->input[*i];
				(*j)++;
				(*i)++;
			}
		}
		if (!mini->input[*i])
		{
			mini->c_input[*j] = mini->input[*i];
			(*j)++;
			(*i)++;
		}
	}
}

void	alloc_single_quotes(int *i, int *j, t_mini *mini)//single quotes
{
	if (mini->input[*i] == '\'')
	{
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
		while (mini->input[*i] != '\'' && mini->input[*i] != '\0')
		{
			mini->c_input[*j] = mini->input[*i];
			(*j)++;
			(*i)++;
		}
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
	}
}

int	question_alloc(int *i, int *j, int *len, t_mini *mini)
{
	int	q;

	q = 0;
	while (mini->str_exit_status[q])
	{
		mini->c_input[(*j)++] = mini->str_exit_status[q];
		q++;
	}
	(*len)++;
	if (mini->input[*len] == '\0' || mini->input[*len] == ' ')
	{
		*i = *len;
		return (1);
	}
	while (mini->input[*len] != ' ')
	{
		mini->c_input[(*j)++] = mini->input[*len];
		(*len)++;
		if (mini->input[*len] == ' ' || mini->input[*len] == '\0')
		{
			*i = *len;
			return (1);
		}
	}
	return (0);
}

// alloc per quotes oppure calcolo lunghezza subito prima di alloc tmp
void	alloc_quotes_or_tmp(int *i, int *j, int *len, t_mini *mini)
{
	if (mini->input[*len] == '"')
		alloc_double_quotes(i, j, mini);
	else if (mini->input[*len] == '\'')
		alloc_single_quotes(i, j, mini);
	else
	{
		while (mini->input[*len] && (ft_isalnum(mini->input[*len])
				|| mini->input[*len] == '_'))
			(*len)++;
	}
	if (*i < 0)
		*i = 0;
	if ((size_t)(*i) > ft_strlen(mini->input))
		(*i)--;
	if (mini->input[*i] == '$')
		(*i)++;
	return ;
}

void	alloc_dollar_env(int *i, int *j, int len, t_mini *mini)
{
	char	*tmp;
	char	*tmp1;
	int		x;

	x = 0;
	if (mini->input[len] == '$')
		len++;
	if (mini->input[len] == '?')
		if (question_alloc(i, j, &len, mini) == 1)
			return ;
	alloc_quotes_or_tmp(i, j, &len, mini);
	tmp1 = get_env(ft_substr(mini->input, *i, len - *i), mini);
	tmp = ft_substrchr(tmp1, '=', 1);
	if (tmp1 != NULL)
		free(tmp1);
	if (free_tmp_env(tmp, i, len, mini) == 1)
		return ;
	while (tmp[x])
		mini->c_input[(*j)++] = tmp[x++];
	*i = len;
	if (mini->input[len] == '"' || mini->input[len] == '\'')
		alloc_quotes_or_tmp(i, j, &len, mini);
	return (free(tmp));
}
