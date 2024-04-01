/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_count_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:55:54 by grinella          #+#    #+#             */
/*   Updated: 2024/04/01 17:00:17 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	d_or_s_quote(t_mini *mini, int *i, int *count)
{
	if (mini->c_input[*i] == '"')
	{
		(*count)++;
		(*i)++;
		while (mini->c_input[*i] != '"' && mini->c_input[*i] != '\0')
			(*i)++;
		if (mini->c_input[*i] == '"')
			(*i)++;
	}
	if (mini->c_input[*i] == '\'')
	{
		(*count)++;
		(*i)++;
		while (mini->c_input[*i] != '\0' && mini->c_input[*i] != '\'')
			(*i)++;
		if (mini->c_input[*i] == '\'')
			(*i)++;
	}
	return ;
}

// se x è 0 va a fare il primo if
// se x è 1 va a fare il secondo if
int	ft_is_not(t_mini *mini, int i, char c, int x)
{
	if (x == 0)
	{
		if (mini->c_input[i] != c && mini->c_input[i] != '\0'
			&& mini->c_input[i] != '"' && mini->c_input[i] != '\''
			&& mini->c_input[i] != '|' && mini && mini->c_input[i] != '<'
			&& mini->c_input[i] != '>')
			return (0);
		return (1);
	}
	if (x == 1)
	{
		if (mini->c_input[i] == '|' || mini->c_input[i] == '<'
			|| mini->c_input[i] == '>')
			return (1);
		return (0);
	}
	return (2);
}

void	count_word(t_mini *mini, int *i, int *count, char c)
{
	(*count)++;
	while (ft_is_not(mini, *i, c, 0) == 0)
		(*i)++;
	if (ft_is_not(mini, *i, c, 1) == 1)
	{
		(*count)++;
		(*i)++;
		if (ft_is_not(mini, *i, c, 1) == 1)
			(*i)++;
	}
}

int	mini_count_words(t_mini *mini, char c, int i, int count)
{
	while (mini->c_input[i] != '\0')
	{
		if (mini->c_input[i] != c)
		{
			d_or_s_quote(mini, &i, &count);
			if (ft_is_not(mini, i, c, 0) == 0)
				count_word(mini, &i, &count, c);
			else if (ft_is_not(mini, i, c, 1) == 1)
			{
				count++;
				i++;
				if (ft_is_not(mini, i, c, 1) == 1)
					i++;
			}
		}
		else
			i++;
	}
	return (count);
}
