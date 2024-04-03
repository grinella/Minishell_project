/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:42:43 by grinella          #+#    #+#             */
/*   Updated: 2024/03/26 00:35:34 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	space_len(int *i, int *j, int *flag, char *input)
{
	while (input[*i] == ' ')
	{
		if ((*flag) == 0 && ++(*flag))
			(*j)++;
		(*i)++;
	}
}

void	quotes_len(int *i, int *j, t_mini *mini)//char* input)
{
	if (mini->input[*i] == '"')
	{
		(*i)++;
		(*j)++;
		while (mini->input[*i] != '"' && mini->input[*i] != '\0')
		{
			if (mini->input[*i] == '$')
				find_dollar_env_len(i, j, mini, *i);
			else
			{
				(*j)++;
				(*i)++;
			}
		}
		(*i)++;
		(*j)++;
	}
	else if (mini->input[*i] == '\'' && ++(*i))
	{
		(*j)++;
		while (mini->input[*i] != '\'' && mini->input[*i] != '\0' && ++(*j))
			(*i)++;
		(*j)++;
		(*i)++;
	}
}

void	alloc_spaces(int *i, int *j, t_mini *mini)
{
	int	flag;

	flag = 0;
	while (mini->input[*i] == ' ')
	{
		if (flag == 0)
		{
			mini->c_input[*j] = mini->input[*i];
			flag = 1;
			(*j)++;
		}
		(*i)++;
	}
	flag = 0;
}
