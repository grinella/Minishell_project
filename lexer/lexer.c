/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:48:40 by eugenio           #+#    #+#             */
/*   Updated: 2024/01/29 18:28:13 by Gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*clean_input(char *input, int i)
{
	t_list	*j;
	int n;
	int	flag;
	
	flag = 0;
	while(input[i] == ' ')
	{
		i++;
	}
	n = i;
	j->n_cmd = i;
	while(input[j->n_cmd] != '|' && input[j->n_cmd] != '\0')
	{
		while(input[j->n_cmd] == ' ')
		{
			if(flag == 0)
			{
				write(1, " ", 1);
				flag = 1;
				i++;
			}
			n++;
			j++;
			i++;
		}
		write(1, &input[j->n_cmd], 1);
		j->n_cmd++;
		i++;
		flag = 0;
	}
	write(1, "\n", 1);
	printf("j: %i\n", i-n);
	return (input);
}

char	*lexer(t_mini *input) //o t_mini o t_lexer
{
	t_list *j;
	int 	i;

	i = 0;
	if (!input) // se input é vuoto
	{
		printf("\n");
	}
	while (input) // se input ha qualcosa al suo interno // aggiornamento con while per iterare su tutta la stringa
	{
		clean_input(input, j->n_cmd);
		j->n_cmd++;
	}
	return (input);
}