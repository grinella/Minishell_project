/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:50:59 by grinella          #+#    #+#             */
/*   Updated: 2024/04/01 17:00:30 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// lunghezza parole
int	mini_len_word(char const *s, int i, char c)
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
int	m_len_q(char const *s, int i, char c)
{
	int		len;

	len = i;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	return (i - len);
}

// is pipe or redirection?
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

char	**mini_split(t_mini *mini, char c)
{
	char	**mtr;

	if (!mini->c_input)
		return (NULL);
	mtr = (char **)ft_calloc(sizeof(char *),
			(mini_count_words(mini, c, 0, 0) + 1));
	if (!mtr)
		return (NULL);
	mini_fill_str(mtr, mini, c);
	return (mtr);
}
