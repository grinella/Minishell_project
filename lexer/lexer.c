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

int	envlen(const char *str, int c)
{
	int	a;

	a = 0;
	while (str[c])
	{
		a++;
		c++;
	}
	return (a);
}

void	find_dollar_env_len(int *i, int *j, t_mini *mini)
{
	int r;//riga
	int c;//colonna
	int	len;

	r = 0;
	c = 0;
	len = *i;
	if (mini->input[*i] == '$')
	{
		len++;
		while (mini->input[len] == mini->env[r++][c] //va sostituito *i con len
			&& mini->input[len] >= 'a' && mini->input[len] <= 'z'
			|| mini->input[len] >= 'A' && mini->input[len] <= 'Z'
			|| mini->input[len] == '_')
		{
			len++;
			c++;
			if (mini->env[r][c] == '=')
			{
				c++;
				*j += envlen(mini->env[r], c);
				*i == len;
				return ;
			}
			len = *i;
		}
	}
}

void	clean_input(t_mini *mini, int len)
{
	int	i;
	int	j;
	int	flag;
	
	i = 0;
	j = 0;
	flag = 0;

	printf("len=%i\n", len);
	mini->c_input = malloc(sizeof(char *) * (len + 1));
	while(mini->input[i] == ' ')
		i++;
	while(mini->input[i] != '\0')
	{
		if(mini->input[i] == ' ')
			alloc_spaces(&i, &j, &flag, mini);
		else if(mini->input[i] == '"' || mini->input[i]  == '\'')
			alloc_quotes(&i, &j, mini);
			// find_dollar
		else
		{
			// find_dollar
			mini->c_input[j] = mini->input[i++];
			j++;
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
		if(mini->input[i] == ' ')
			space_len(&i, &j, &flag, mini->input);
		else if(mini->input[i] == '"' || mini->input[i] == '\'')
			quotes_len(&i, &j, mini->input);
		else
		{
			// find_dollar_env_len
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
