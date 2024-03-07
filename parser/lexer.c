#include "../include/minishell.h"

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
		if (mini->input[len] == '?')
		{
			len++;
			if (mini->input[len] == '\0' || mini->input[len] == ' ')
			{
				*i = len;
				printf("LA J PRIMA [%i]\n", *j);
				*j += ft_strlen(mini->str_exit_status);
				printf("LA J DOPO [%i]\n", *j);
				return ;
			}
			while (mini->input[len] != ' ')
			{
				len++;
				(*j)++; 
				if (mini->input[len] != ' ')
				{
					*i = len;
					return ;
				}
			}
		}
		while (mini->env[r]!= NULL)
		{
			while ((mini->input[len] == mini->env[r][c]) && ((mini->input[len] >= 'a' && mini->input[len] <= 'z')
				|| (mini->input[len] >= 'A' && mini->input[len] <= 'Z') || (mini->input[len] == '_')))
			{
				c++;
				len++;
			}
			if (mini->env[r][c] == '=' && ((mini->input[len] < 'a' || mini->input[len] > 'z')
				&& (mini->input[len] < 'A' || mini->input[len] > 'Z') && (mini->input[len] != '_')))
			{
				c++;
				(*j)++;
				while(mini->env[r][c]!= '\0')
				{
					c++;
					(*j)++;
				}
				if(mini->env[r][c] == '\0')
				{
					*i = len;
					return ;
				}
			}
			else
			{
				r++;
				if (mini->env[r] == NULL)
				{
					while ((mini->input[len] >= 'a' && mini->input[len] <= 'z')
						|| (mini->input[len] >= 'A' && mini->input[len] <= 'Z') || (mini->input[len] == '_'))
						len++;
					*i = len;
					return ;
				}
				len = *i + 1;
			}
		}

	}
}

void	clean_input(t_mini *mini, int len)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	mini->c_input = ft_calloc(sizeof(char *) , (len + 1));
	while(mini->input[i] == ' ')
		i++;
	while(mini->input[i] != '\0')
	{
		if(mini->input[i] == ' ')
			alloc_spaces(&i, &j, mini);
		else if(mini->input[i] == '\'')
			alloc_single_quotes(&i, &j, mini);
		else if(mini->input[i] == '"')
			alloc_double_quotes(&i, &j, mini);
		else if (mini->input[i] == '$')
			alloc_dollar_env(&i, &j, mini);
		else
		{
			mini->c_input[j] = mini->input[i++];
			j++;
		}
	}
	mini->c_input[j] = '\0';
}
// ************************************************************************************** //
// la situa migliora, va allocata effettivamente con get_env la stringa corrispondente,   //
// va sfruttato get_env a parte tra le single quote										  //
// ************************************************************************************** //

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
			quotes_len(&i, &j, mini);
		else if (mini->input[i] == '$')
			find_dollar_env_len(&i, &j, mini); // da controllare
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
