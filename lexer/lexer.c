/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:48:40 by eugenio           #+#    #+#             */
/*   Updated: 2024/02/08 15:40:52 by Gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//--------------------------------------------------------------------
char	*find_dollar_env(t_toks *toks, char **env) // DA ADATTARE PER FAR TROVARE UNA RIGA SPIECIFICA NELL'ENV
{
	struct stat	buff;
	int			i;
	char		**base;
	char		*temp;
	char		*path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
	{
		i++;
	}
	base = ft_split((env[i] + 5), ':');
	i = -1;
	while (base && base[++i])
	{
		temp = ft_strjoin(base[i], "/");
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

//--------------------------------------------------------------------

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
