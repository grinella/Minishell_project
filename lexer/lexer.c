/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:48:40 by eugenio           #+#    #+#             */
/*   Updated: 2024/03/06 15:49:00 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*clean_input(t_mini *mini, int i)
{
	int	j;
	int	flag;

	flag = 0;
	while(mini->input[i] == ' ')
	{
		i++;
	}
	j = 0;
	while(mini->input[i] != '|' && mini->input[i] != '\0')
	{
		while(mini->input[i] == ' ')
		{
			if(flag == 0)
			{
				write(1, " ", 1);
				flag = 1;
				j++;
			}
			i++;
		}
		write(1, &mini->input[i], 1);
		j++;
		i++;
		flag = 0;
	}
	write(1, "\n", 1);
	printf("j: %i\n", j);
	// printf("input pulito: %s\n", input);
	return (mini->input);
	// richiamo funzione che restituisce l'imput pulito (clean_alloc)
}

char	*lexer(t_mini *mini) //o t_mini o t_lexer
{
	int j;

	j = 0;
	if (mini->input[0] == '\0') // se input é vuoto
	{
		return (NULL);
	}
	if (mini->input) // se input ha qualcosa al suo interno // aggiornamento con while per iterare su tutta la stringa
	{
		clean_input(mini, j);
		printf("mini->input:%s\n", mini->input);
		j++;
	}
	//search_token(mini->input);
	return (mini->input);
}