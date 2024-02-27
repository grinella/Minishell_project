#include "../include/minishell.h"

void	space_len(int *i, int *j, int *flag, char* input)
{
	while(input[*i] == ' ')
	{
		if((*flag) == 0 && ++(*flag))
			(*j)++;
		(*i)++;
	}
}

void	quotes_len(int *i, int *j, t_mini *mini)//char* input)
{
	if(mini->input[*i] == '"')
	{
		(*i)++;
		(*j)++;
		while(mini->input[*i] != '"' && mini->input[*i] != '\0')
		{
			if (mini->input[*i] == '$')
				find_dollar_env_len(i, j, mini);
			else
			{
				(*j)++;
				(*i)++;
			}
		}
		(*i)++;
		(*j)++;
	}
	else if(mini->input[*i] == '\'' && ++(*i))
	{
		(*j)++;
		while(mini->input[*i] != '\'' && mini->input[*i] != '\0' && ++(*j))
			(*i)++;
		(*j)++;
		(*i)++;
	}
}

void	alloc_spaces(int *i, int *j, t_mini *mini)
{
	int flag;

	flag = 0;
	while(mini->input[*i] == ' ')
	{
		if(flag == 0)
		{
			mini->c_input[*j] = mini->input[*i];
			flag = 1;
			(*j)++;
		}
		(*i)++;
	}
	flag = 0;
}

void	alloc_quotes(int *i, int *j, t_mini *mini)// single quotes
{
	if(mini->input[*i] == '"' || mini->input[*i] == '\'')
	{
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
		while(mini->input[*i] != '"' && mini->input[*i] != '\'' && mini->input[*i] != '\0')
		{
			mini->c_input[*j] = mini->input[*i];
			(*j)++;
			(*i)++;
		}
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
	}
}

void	alloc_d_quotes(int *i, int *j, t_mini *mini)//double quotes
{
	if(mini->input[*i] == '"')
	{
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
		while(mini->input[*i] != '"' && mini->input[*i] != '\0')
		{
			mini->c_input[*j] = mini->input[*i];
			(*j)++;
			(*i)++;
		}
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
	}
}

void	alloc_dollar_env(int *i, int *j, t_mini *mini)
{
	int r;//riga
	int c;//colonna
	int	len;

	r = 0;
	c = 0;
	len = *i;
	if (mini->input[*i] == '$')
	{
		printf("\nalloc primo if dollaro\n");
		len++;
		printf("alloc dopo il primo if sulla readline: %c\n", mini->input[len]);
		while (mini->env[r]!= NULL)
		{
			printf("\nalloc primo while dollaro\n");
			printf("cosa vede sulla readline: %c\n", mini->input[len]);
			printf("cosa vede sulla env: %c\n", mini->env[r][c]);
			while ((mini->input[len] == mini->env[r][c]) && ((mini->input[len] >= 'a' && mini->input[len] <= 'z')
				|| (mini->input[len] >= 'A' && mini->input[len] <= 'Z') || (mini->input[len] == '_')))
			{
				printf("\nalloc becca la corrispondenza\n");
				printf("cosa vede sulla readline: %c\n", mini->input[len]);
				printf("cosa vede sulla env: %c\n\n", mini->env[r][c]);
				c++;
				len++;
			}
			printf("\nalloc dopo il secondo while dollaro\n");
			printf("cosa vede sulla readline: %c\n", mini->input[len]);
			printf("cosa vede sulla env: %c\n", mini->env[r][c]);
			if (mini->env[r][c] == '=' && ((mini->input[len] < 'a' || mini->input[len] > 'z')
				&& (mini->input[len] < 'A' || mini->input[len] > 'Z') && (mini->input[len] != '_')))
			{
				printf("alloc uguale trovato\n");
				c++;
				(*j)++;
				while(mini->env[r][c]!= '\0')
				{
					printf("sto allocando in c_input %c\n", mini->env[r][c]);
					mini->c_input[*j] = mini->env[r][c];
					c++;
					printf("\n1: c_input %c\n\n", mini->c_input[*j]);
					(*j)++;
					if(mini->env[r][c] == '\0')
					{
						printf(" if mini->env[r][c] == '0' alloc adesso sto su %c\n", mini->env[r][c]);
						printf("len nel $ = %i\n", len);
						*i = len;
						return ;
					}
					// sleep(1);
				}
				printf("\nadesso sto su %c\n", mini->env[r][c]);
			}
			else
			{
				printf("arriva all'else\n");
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
