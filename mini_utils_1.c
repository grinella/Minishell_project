/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:50:59 by grinella          #+#    #+#             */
/*   Updated: 2024/03/25 10:51:00 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	mini_count_words(t_mini *mini, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (mini->c_input[i] != '\0')
	{
		if (mini->c_input[i] != c)
		{
			if (mini->c_input[i] == '"')
			{
				count++;
				i++;
				while (mini->c_input[i] != '"' && mini->c_input[i] != '\0')
					i++;
				if (mini->c_input[i] == '"')
					i++;
			}
			if (mini->c_input[i] == '\'')
			{
				count++;
				i++;
				while (mini->c_input[i] != '\0' && mini->c_input[i] != '\'')
					i++;
				if (mini->c_input[i] == '\'')
					i++;
			}
			if (mini->c_input[i] != c && mini->c_input[i] != '\0'
				&& mini->c_input[i] != '"' && mini->c_input[i] != '\''
				&& mini->c_input[i] != '|' && mini && mini->c_input[i] != '<'
				&& mini->c_input[i] != '>')
			{
				count++;
				while (mini->c_input[i] != c && mini->c_input[i] != '\0'
					&& mini->c_input[i] != '|' && mini->c_input[i] != '<'
					&& mini->c_input[i] != '>' && mini->c_input[i] != '"'
					&& mini->c_input[i] != '\'')
					i++;
				if (mini->c_input[i] == '|' || mini->c_input[i] == '<'
					|| mini->c_input[i] == '>')
				{
					count++;
					i++;
					if (mini->c_input[i] == '|' || mini->c_input[i]
						== '<' || mini->c_input[i] == '>')
						i++;
				}
			}
			else if (mini->c_input[i] == '|' || mini->c_input[i] == '<'
				|| mini->c_input[i] == '>')
			{
				count++;
				i++;
				if (mini->c_input[i] == '|' || mini->c_input[i]
					== '<' || mini->c_input[i] == '>')
					i++;
			}
		}
		else
			i++;
	}
	printf("count %i\n", count);
	return (count);
}

static int	mini_len_word(char const *s, int i, char c)
{
	int		len;

	len = i;
	while (s[i] != c && s[i] != '\0' && s[i]
		!= '|' && s[i] != '<' && s[i] != '>' && s[i] != '"' && s[i] != '\'')
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			return (i - len);
		i++;
	}
	return (i - len);
}

// mini_len_quotes
static int	m_len_q(char const *s, int i, char c)
{
	int		len;

	len = i;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	return (i - len);
}

int	is_pipe_redir(char const *s, int i)
{
	if (s[i] == '<' || s[i] == '>')
	{
		if (s[i + 1] == '<' || s[i + 1] == '>')
			return (2);
	}
	else if (s[i] == '|')
	{
		if (s[i + 1] == '|')
			return (2);
	}
	return (1);
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
		{
			i++;
			if (mini->c_input[i] != '"')
			{
				str[j] = ft_substr(mini->c_input, i, m_len_q(mini->c_input, i, '"'));
				if (m_len_q(mini->c_input, i, '"') == 0)
				{
					printf("Error: missing quote\n");
					g_exit_status = -1;
					free(str[j]);
					str[j] = NULL;
					return ;
				}
				i += m_len_q(mini->c_input, i, '"');
				if (!str[j])
				{
					mini_free(str, j);
					return ;
				}
				j++;
			}
			if (mini->c_input[i] == '"')
				i++;
		}
		else if (mini->c_input[i] == '\'')
		{
			i += 1;
			str[j] = ft_substr(mini->c_input, i, m_len_q(mini->c_input, i, '\''));
			if (m_len_q(mini->c_input, i, '\'') == 0)
			{
				printf("Error: missing quote\n");
				g_exit_status = -1;
				free(str[j]);
				str[j] = NULL;
				return ;
			}
			i += m_len_q(mini->c_input, i, '\'');
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			if (mini->c_input[i] == '\'')
				i++;
			j++;
		}
		else if (mini->c_input[i] != c && mini->c_input[i] != '"'
			&& mini->c_input[i] != '\'' && mini->c_input[i] != '\0')
		{
			if (mini->c_input[i] != '|' && mini->c_input[i] != '>'
				&& mini->c_input[i] != '<')
			{
				str[j++] = ft_substr(mini->c_input, i,
						mini_len_word(mini->c_input, i, c));
				i += mini_len_word(mini->c_input, i, c);
			}
			if (mini->c_input[i] == '|' || mini->c_input[i] == '>'
				|| mini->c_input[i] == '<')
			{
				str[j++] = ft_substr(mini->c_input, i,
						is_pipe_redir(mini->c_input, i));
				i += is_pipe_redir(mini->c_input, i);
			}
		}
		while (mini->c_input[i] == c && (mini->c_input[i] != '\0'
				&& mini->c_input[i] != '"' && mini->c_input[i] != '\''))
			i++;
	}
	str[j] = NULL;
}

char	**mini_split(t_mini *mini, char c)
{
	char	**mtr;

	if (!mini->c_input)
		return (NULL);
	mtr = (char **)ft_calloc(sizeof(char *), (mini_count_words(mini, c) + 1));
	if (!mtr)
		return (NULL);
	mini_fill_str(mtr, mini, c);
	ft_print_matrix(mtr);
	return (mtr);
}
