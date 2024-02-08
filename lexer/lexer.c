/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:48:40 by eugenio           #+#    #+#             */
/*   Updated: 2024/02/08 19:17:44 by Gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
//--------------------------------------------------------------------
char	*find_dollar_env(t_toks *toks, char **env, int *i) // DA ADATTARE PER FAR TROVARE UNA RIGA SPIECIFICA NELL'ENV
{
	int			e;
	struct stat	buff;
	char		**base;
	char		*temp;
	char		*path;

	e = 0;
	ft_strlen
	while (ft_strncmp(env[e], , ))
	{
		e++;
	}
	base = ft_split((env[e] + 5), ':');
	e = -1;
	while (base && base[++e])
	{
		temp = ft_strjoin(base[e], "/");
		if (!lstat(ft_strjoin(temp, toks->word[0]), &buff))
		{
			path = ft_strjoin(temp, toks->word[0]);
			free(temp);
			return (path);
		}
	}
	free(temp);
	return (NULL);
}

//la funzione find_dollar_env_len dovrà calcolare la lunghezza della variabile
// d'ambiente per aggiornre la j di clean_input_len da passare poi a clean_input
// così avremo es:
//	input		 -> echo "ciao $SSH_AUTH_SOCK"
//	input_pulito -> echo ciao /private/tmp/com.apple.launchd.Or31a9lSsT/Listeners
int	find_dollar_env_len(t_toks *toks, char **env, int *i, int	*j)
{
	
	
}
//--------------------------------------------------------------------
*/

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
				if (mini->input[i] == '$')
				{
					i++;
				//	find_dollar_env(); ANCORA DA SCRIVERE
				}
				mini->c_input[j] = mini->input[i];
				j++;
				i++;
			}
			mini->c_input[j] = mini->input[i];
			j++;
			i++;
		}
		else if(mini->input[i] == '\'')
		{
			mini->c_input[j] = mini->input[i];
			j++;
			i++;
			while(mini->input[i] != '\'' && mini->input[i] != '\0')
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
		while(mini->input[i] == ' ')
		{
			if(flag == 0 && ++flag)
				j++;
			i++;
		}
		if(mini->input[i] == '"')
		{
			// if (mini->input[i] == '$')
			// {
			// 	i++;
			// 	j += //find_dollar_env_len(); DA SCRIVERE
			// }
			j++;
			i++;
			while(mini->input[i] != '"' && mini->input[i] != '\0')
			{
				j++;
				i++;
			}
			j++;
			i++;
		}
		else if(mini->input[i] == '\'')
		{
			j++;
			i++;
			while(mini->input[i] != '\'' && mini->input[i] != '\0')
			{
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
