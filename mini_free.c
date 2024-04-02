/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:19 by grinella          #+#    #+#             */
/*   Updated: 2024/04/02 17:00:57 by grinella         ###   ########.fr       */
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

void	free_all(t_mini *mini, t_toks *toks)
{
	if (mini->input != NULL)
		free (mini->input);
	if (mini->c_input != NULL)
		free (mini->c_input);
	if (toks != NULL)
		free_node(toks);
	// exit(0);
	//find_head(toks);
	//if (toks)
	//{
		//printf("boh = %s\n", toks->word[0]);
	//}
}

// void	exit_free(t_mini *mini, char **mtr)
// {
// 	free_all(mini);
// 	// free_node(toks);
// 	if (mtr)
// 		free_matrix(mtr);
// }
