/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:19 by grinella          #+#    #+#             */
/*   Updated: 2024/03/26 02:04:58 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_node(t_toks *toks)
{
	t_toks	*tmp;
	t_toks	*current;

	if (toks == NULL)
		return ;
	current = toks;
	while (current)
	{
		tmp = current->next;
		free_matrix(current->word);
		current = tmp;
	}
	free(current);
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
	// da controllare
	return ;
}

void	mini_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

void	free_all(t_mini *mini)
{
	if (mini->input != NULL)
		free (mini->input);
	if (mini->c_input != NULL)
		free (mini->c_input);
}

// void	exit_free(t_mini *mini, char **mtr)
// {
// 	free_all(mini);
// 	// free_node(toks);
// 	if (mtr)
// 		free_matrix(mtr);
// }
