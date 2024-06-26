/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_fill_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:57:47 by grinella          #+#    #+#             */
/*   Updated: 2024/04/03 21:25:19 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	toks_len(char **tokens, int *i)
{
	int	j;
	int	x;

	j = *i;
	x = 0;
	if (tokens[j][0] == '|' || tokens[j][0] == '<' || tokens[j][0] == '>')
	{
		if (tokens[j][0] == '<' || tokens[j][0] == '>')
			return (3);
		return (2);
	}
	while (tokens[j] && tokens[j][0] != '|'
		&& tokens[j][0] != '<' && tokens[j][0] != '>')
	{
		x++;
		j++;
	}
	x++;
	return (x);
}

void	fill_node(char **tokens, t_toks *node, int *i)
{
	int	j;

	j = 0;
	node->word = (char **)ft_calloc(sizeof(char *), (toks_len(tokens, i)));
	if (tokens[*i][0] == '|' || tokens[*i][0] == '<' || tokens[*i][0] == '>')
	{
		node->word[j] = ft_strdup(tokens[*i]);
		(*i)++;
		j++;
		if (tokens[*i - 1][0] == '<' || tokens[*i - 1][0] == '>')
		{
			node->word[j] = ft_strdup(tokens[*i]);
			(*i)++;
			j++;
		}
		node->word[j] = NULL;
		return ;
	}
	while (tokens[*i][0] != '|' && tokens[*i][0] != '<' && tokens[*i][0] != '>')
	{
		node->word[j] = ft_strdup(tokens[*i]);
		(*i)++;
		j++;
	}
	node->word[j] = NULL;
}

int	complex_toks_len(char **tokens, int *i)
{
	int	j;
	int	count;

	count = 0;
	j = *i;
	while (tokens[j] && tokens[j][0] != '|')
	{
		if (tokens[j][0] == '<' || tokens[j][0] == '>')
			j += 2;
		else
		{
			j++;
			count++;
		}
	}
	count++;
	return (count);
}

void	fill_cmplx_nd(char **tokens, t_toks *node, int *i, int *flag)
{
	int	j;

	j = 0;
	while (tokens[*i] && tokens[*i][0] != '|')
	{
		if (tokens[*i][0] == '<' || tokens[*i][0] == '>')
		{
			*flag = 1;
			*i += 2;
		}
		else
		{
			node->word[j] = ft_strdup(tokens[*i]);
			j++;
			(*i)++;
		}
	}
}

void	fill_complex_node(char **tokens, t_toks **toks, t_toks *node, int *i)
{
	int	flag;
	int	x;

	x = *i;
	flag = 0;
	node->word = (char **)ft_calloc(sizeof(char *),
			(complex_toks_len(tokens, i)));
	fill_cmplx_nd(tokens, node, i, &flag);
	while (tokens[x] && tokens[x][0] != '|' && flag == 1)
	{
		if (tokens[x][0] == '>' && tokens[x][1] == '>')
			append_node(tokens, toks, 3, &x);
		else if (tokens[x][0] == '>')
			append_node(tokens, toks, 2, &x);
		else if (tokens[x][0] == '<' && tokens[x][1] == '<')
			append_node(tokens, toks, 5, &x);
		else if (tokens[x][0] == '<')
			append_node(tokens, toks, 4, &x);
		else
			x++;
	}
	if (x > *i)
		*i = x;
}
