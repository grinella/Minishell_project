/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:19 by grinella          #+#    #+#             */
/*   Updated: 2024/04/03 21:43:50 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_node(t_toks *toks)
{
	t_toks	*current;
	t_toks	*next;

	if (toks == NULL)
		return ;
	current = toks;
	while (current != NULL)
	{
		next = current->next;
		free_matrix(current->word);
		free(current);
		current = next;
	}
	toks = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
	return ;
}
	// il free(matrix) qui sopra è da controllare

void	mini_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

// void	find_head(t_toks *toks)
// {
// 	while (toks->prev != NULL)
// 		toks = toks->prev;
// }

void	free_routine(t_mini *mini, t_toks *toks)
{
	if (mini->input != NULL)
		free (mini->input);
	if (mini->c_input != NULL)
		free (mini->c_input);
	if (mini->str_exit_status)
	{
		free(mini->str_exit_status);
		mini->str_exit_status = NULL;
	}
	if (toks != NULL)
		free_node(toks);
}

void	free_all(t_mini *mini, t_toks *toks)
{
	if (mini->input != NULL)
		free (mini->input);
	if (mini->c_input != NULL)
		free (mini->c_input);
	if (mini->str_exit_status)
	{
		free(mini->str_exit_status);
		mini->str_exit_status = NULL;
	}
	if (toks != NULL)
		free_node(toks);
	free_matrix(mini->env);
	if (mini != NULL)
	{
		free(mini);
		mini = NULL;
	}
}
