/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:48:40 by eugenio           #+#    #+#             */
/*   Updated: 2024/02/02 17:41:48 by Gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_input(t_mini *mini, int len)
{
	int	i;
	int	j;
	int	flag;
	
	i = 0;
	flag = 0;
	j = 0;
	//ho creato questa condizione cosi se rientra in questa funzione piu di una volta non alloca la stessa variabile due volte però anche se la commento non da errore
	if (mini->c_input)
		free(mini->c_input);
	mini->c_input = malloc(sizeof(char *) * (len + 1));
	while(mini->input[i] == ' ')
		i++;
	while(mini->input[i] != '\0')
	{
		while(mini->input[i] == ' ')
		{
			if(flag == 0)
			{
				mini->c_input[j] = mini->input[i];
				flag = 1;
				j++;
			}
			i++;
		}
		if(mini->input[i] == '"')
		{
			mini->c_input[j] = mini->input[i];
			j++;
			i++;
			while(mini->input[i] != '"' && mini->input[i] != '\0')
			{
				mini->c_input[j] = mini->input[i];
				j++;
				i++;
			}
			mini->c_input[j] = mini->input[i];
			j++;
			i++;
		}
		mini->c_input[j] = mini->input[i];
		j++;
		i++;
		flag = 0;
	}
	mini->c_input[j] = '\0';
}

void	clean_input_len(t_mini *mini)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while(mini->input[i] == ' ')
		i++;
	j = 0;
	while(mini->input[i] != '\0')
	{
		printf("j2:%i\n", j);
		while(mini->input[i] == ' ')
		{
			if(flag == 0 && ++flag)
				j++;
			i++;
		}
		if(mini->input[i] == '"')
		{
			printf("j1:%i\n", j);
			j++;
			i++;
			while(mini->input[i] != '"' && mini->input[i] != '\0')
			{
				printf("j3:\n");
				j++;
				i++;
			}
			j++;
			i++;
		}
		j++;
		i++;
		flag = 0;
	}
	printf("j:%i\n", j);
	clean_input(mini, j);
}

char	*lexer(t_mini *mini, t_toks *toks) //o t_mini o t_lexer
{
	if (mini->input[0] == '\0') // se input é vuoto
	{
		return (NULL);
	}
	if (mini->input) // se input ha qualcosa al suo interno // aggiornamento con while per iterare su tutta la stringa
	{
		clean_input_len(mini);
		splitter(mini, toks);
		// (void)toks;
	}
	return (mini->input);
}
