/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:37:33 by eugenio           #+#    #+#             */
/*   Updated: 2024/02/12 17:24:16 by Gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//QUALCOSINA FUNZIONA MA NON SO SE E' CORRETTO
void	splitter(t_mini *mini, t_toks *toks)
{
	if (mini->c_input)
		toks->word = mini_split(mini->c_input, ' ');
	// ft_print_matrix(toks->word);
	printf("prova %s\n", toks->word[0]);
	// tokenizer(mini, toks);
}

// void	tokenizer(t_mini *mini, t_toks *toks)
// {
// 	int	i;
	
// 	i = 0;
// }