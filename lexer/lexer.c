#include "../include/minishell.h"

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
		while ((mini->input[len] == mini->env[r++][c]) && ((mini->input[len] >= 'a' && mini->input[len] <= 'z')
			|| (mini->input[len] >= 'A' && mini->input[len] <= 'Z') || (mini->input[len] == '_')))
		{
			len++;
			c++;
			if (mini->env[r][c] == '=' && mini->input[len] )
			{
				c++;
				*j += envlen(mini->env[r], c);
				*i = len;
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
	
	i = 0;
	j = 0;
	printf("len=%i\n", len);
	mini->c_input = malloc(sizeof(char *) * (len + 1));
	while(mini->input[i] == ' ')
		i++;
	while(mini->input[i] != '\0')
	{
		if(mini->input[i] == ' ')
			alloc_spaces(&i, &j, mini);
		else if(mini->input[i] == '"' || mini->input[i]  == '\'')
			alloc_quotes(&i, &j, mini); // find dollar_env
		else
		{
			// find_dollar
			mini->c_input[j] = mini->input[i++];
			j++;
		}
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
			if (mini->input[i] == '$')
				find_dollar_env_len(&i, &j, mini); // da controllare
			else
			{
				j++;
				i++;
			}
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
