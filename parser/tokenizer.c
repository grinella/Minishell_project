/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:39:20 by grinella          #+#    #+#             */
/*   Updated: 2024/03/26 03:12:20 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_count(t_mini *mini, t_toks *toks)
{
	t_toks	*tmp;

	tmp = toks;
	while (tmp != NULL)
	{
		if (tmp->type == 0)
		{
			mini->cmd_count++;
			tmp->cmd_pos = mini->cmd_count;
		}
		tmp = tmp->next;
	}
}

void	append_node(char **tokens, t_toks **toks, int type, int *i)
{
	t_toks	*node;
	t_toks	*last_node;

	node = (t_toks *)ft_calloc(1, sizeof(t_toks));
	if (node == NULL)
		return ;
	node->next = NULL;
	node->cmd_pos = 0;
	node->type = type;
	if (*toks == NULL)
	{
		*toks = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*toks);
		last_node->next = node;
		node->prev = last_node;
	}
	if (type != 0)
		fill_node(tokens, node, i);
	else
		fill_complex_node(tokens, toks, node, i);
}

void	tokenizer(char **tokens, t_toks **toks)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
		{
			printf("Error: double pipe\n");
			//richiamo funzione free;
			return ;
		}
		else if (tokens[i][0] == '|')
			append_node(tokens, toks, 1, &i);
		else if (tokens[i][0] == '>' && tokens[i][1] == '>')
			append_node(tokens, toks, 3, &i);
		else if (tokens[i][0] == '>')
			append_node(tokens, toks, 2, &i);
		else if (tokens[i][0] == '<' && tokens[i][1] == '<')
			append_node(tokens, toks, 5, &i);
		else if (tokens[i][0] == '<')
			append_node(tokens, toks, 4, &i);
		else
			append_node(tokens, toks, 0, &i);
	}
	free_matrix(tokens);
}
//l'ultimo free matrix nella funzione sopra NON SO SE FUNZIONA

//QUALCOSINA FUNZIONA ED é PURE CORRETTO
void	splitter(t_mini *mini, t_toks *toks)
{
	char	**tokens;

	tokens = NULL;
	if (mini->c_input)
		tokens = mini_split(mini, ' ');
	tokenizer(tokens, &toks);
	cmd_count(mini, toks);
	//is_builtin(toks); // per testare builtins, poi dovrà essere implementata probabilmente nell'executor
	//ft_print_node(toks);
	executor(mini, toks);
}
