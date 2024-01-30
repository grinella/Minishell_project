/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:48:40 by eugenio           #+#    #+#             */
/*   Updated: 2024/01/30 16:10:41 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*clean_input(char *input, int i)
{
	int j;
	int n;
	int	flag;
	
	flag = 0;
	while(input[i] == ' ')
	{
		i++;
	}
	n = i;
	j = i;
	while(input[j] != '|' && input[j] != '\0')
	{
		while(input[j] == ' ')
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
		write(1, &input[j], 1);
		j++;
		i++;
		flag = 0;
	}
	write(1, "\n", 1);
	printf("j: %i\n", i-n);
	return (input);
}

void	lexer(t_mini *mini) //o t_mini o t_lexer
{
	int i;

	i = 0;
	if (!mini->input) // se input é vuoto
	{
		printf("\n");
	}
	if (mini->input) // se input ha qualcosa al suo interno
	{
		clean_input(mini->input, i);
	}
}