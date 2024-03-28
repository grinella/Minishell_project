/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_fill_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:11:25 by grinella          #+#    #+#             */
/*   Updated: 2024/03/26 12:33:04 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_fill_d_quote(t_mini *mini, char **str, int *i, int *j)
{
	(*i)++;
	if (mini->c_input[*i] != '"')
	{
		str[*j] = ft_substr(mini->c_input, *i, m_len_q(mini->c_input, *i, '"'));
		if (m_len_q(mini->c_input, *i, '"') == 0)
		{
			printf("Error: missing quote\n");
			g_exit_status = -1;
			free(str[*j]);
			str[*j] = NULL;
			return ;
		}
		(*i) += m_len_q(mini->c_input, *i, '"');
		if (!str[*j])
		{
			mini_free(str, *j);
			return ;
		}
		(*j)++;
	}
	if (mini->c_input[*i] == '"')
		(*i)++;
}

void	mini_fill_s_quote(t_mini *mini, char **str, int *i, int *j)
{
	(*i)++;
	str[*j] = ft_substr(mini->c_input, *i, m_len_q(mini->c_input, *i, '\''));
	if (m_len_q(mini->c_input, *i, '\'') == 0)
	{
		printf("Error: missing quote\n");
		g_exit_status = -1;
		free(str[*j]);
		str[*j] = NULL;
		return ;
	}
	(*i) += m_len_q(mini->c_input, *i, '\'');
	if (!str[*j])
	{
		mini_free(str, *j);
		return ;
	}
	if (mini->c_input[*i] == '\'')
		(*i)++;
	(*j)++;
}

void	mini_fill_other(t_mini *mini, char **str, int *i, int *j)
{
	if (mini->c_input[*i] != '|' && mini->c_input[*i] != '>'
		&& mini->c_input[*i] != '<')
	{
		str[*j] = ft_substr(mini->c_input, *i,
				mini_len_word(mini->c_input, *i, ' '));
		(*j)++;
		(*i) += mini_len_word(mini->c_input, *i, ' ');
	}
	if (mini->c_input[*i] == '|' || mini->c_input[*i] == '>'
		|| mini->c_input[*i] == '<')
	{
		str[*j] = ft_substr(mini->c_input, *i,
				is_pipe_redir(mini->c_input, *i));
		(*j)++;
		(*i) += is_pipe_redir(mini->c_input, *i);
	}
}

void	mini_fill_str(char **str, t_mini *mini, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mini->c_input[i] != '\0')
	{
		if (mini->c_input[i] == '"')
			mini_fill_d_quote(mini, str, &i, &j);
		else if (mini->c_input[i] == '\'')
			mini_fill_s_quote(mini, str, &i, &j);
		else if (mini->c_input[i] != c && mini->c_input[i] != '"'
			&& mini->c_input[i] != '\'' && mini->c_input[i] != '\0')
			mini_fill_other(mini, str, &i, &j);
		while (mini->c_input[i] == c && (mini->c_input[i] != '\0'
				&& mini->c_input[i] != '"' && mini->c_input[i] != '\''))
			i++;
	}
	str[j] = NULL;
}
