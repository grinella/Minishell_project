/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:37:33 by eugenio           #+#    #+#             */
/*   Updated: 2024/02/02 12:38:44 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//NON FUNZIONA UN CAZZO
void	tokenizer(t_mini *mini, t_toks *toks)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (mini->c_input[i] != '\0')
	{
		while(mini->c_input[i] != '|' || mini->c_input[i] != '>'
			|| mini->c_input[i] != '<' || mini->c_input[i] != '\0')
		{
			toks->word[n] = mini->c_input[i];	//inserisce le lettere in word
			i++;
		}
		while(mini->c_input[i] == ' ' || mini->c_input[i] != '\0')
			i++;
		n++;
	}
}