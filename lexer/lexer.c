#include "../include/minishell.h"

//--------------------------------------------------------------------
// DA ADATTARE PER FAR TROVARE UNA RIGA SPIECIFICA NELL'ENV
// int	*find_dollar_env(t_toks *toks, t_mini *mini, char **env, int *i, int *j)
// {
// 	int n;
// 	*i++;
// 	while(mini->input[*i] >= 'A' && mini->input[*i] <= 'Z'
// 		|| mini->input[*i] >= 'a' && mini->input[*i] <= 'z' || mini->input[*i] == '_')
// 	{
// 		n++;
// 	}
// }

//la funzione find_dollar_env_len dovrà calcolare la lunghezza della variabile
// d'ambiente per aggiornre la j di clean_input_len da passare poi a clean_input
// così avremo es:
//	input		 -> echo "ciao $SSH_AUTH_SOCK"
//	input_pulito -> echo ciao /private/tmp/com.apple.launchd.Or31a9lSsT/Listeners

// int find_dollar_env_len( t_mini *mini, int *i)
// {
// 	int x;
// 	int y;
// 	int len;

// 	y = 0;
// 	x = 0;
// 	while(mini->input[*i] >= 'A' && mini->input[*i] <= 'Z'
// 		|| mini->input[*i] >= 'a' && mini->input[*i] <= 'z' || mini->input[*i] == '_')
// 	{
// 		(*i)++;
// 	}
// 	while (ft_strncmp(mini->env[x], mini->input, 5))
// 	{
// 		i++;
// 	}
// 	while(mini->env[x])
// 	{
// 		if(ft_strncmp(mini->env[x][y], &mini->input[*i], ft_strlen(&mini->input[*i])) == 0)
// 		{
// 			while(mini->env[x][y] != '=')
// 				y++;
// 			//printf("len = %i\n", ft_strlen(mini->env[x] + y));
// 		return (ft_strlen(mini->env[x] + y));
// 		}
// 	}
// 	return 0;
// }
//--------------------------------------------------------------------

void	clean_input(t_mini *mini, int len)
{
	int	i;
	int	j;
	int	flag;
	
	i = 0;
	j = 0;
	flag = 0;

	mini->c_input = malloc(sizeof(char *) * (len + 1));
	while(mini->input[i] == ' ')
		i++;
	while(mini->input[i] != '\0')
	{
		if(mini->input[i] == ' ')
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
		}
		else if(mini->input[i] == '"')
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
		else
		{
			mini->c_input[j] = mini->input[i];
			j++;
			i++;
		}
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
	j = 0;
	flag = 0;
	while(mini->input[i] == ' ')
		i++;
	while(mini->input[i] != '\0')
	{
		if (mini->input[i] == ' ')
		{
			while(mini->input[i] == ' ')
			{
				if(flag == 0 && ++flag)
					j++;
				i++;
			}
		}
		else if(mini->input[i] == '"')
		{
			i++;
			j++;
			while(mini->input[i] != '"' && mini->input[i] != '\0')
			{
				j++;
				i++;
			}
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
		else
		{
			j++;
			i++;
		}
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
