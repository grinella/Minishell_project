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

void	alloc_double_quotes(int *i, int *j, t_mini *mini)// single quotes
{
	if(mini->input[*i] == '"')
	{
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
		while(mini->input[*i] != '"' && mini->input[*i] != '\0')
		{
			if (mini->input[*i] == '$')
				alloc_dollar_env(i, j, mini);
			else
			{
				mini->c_input[*j] = mini->input[*i];
				(*j)++;
				(*i)++;
			}
		}
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
	}
}

void	alloc_single_quotes(int *i, int *j, t_mini *mini)//single quotes
{
	if(mini->input[*i] == '\'')
	{
		mini->c_input[*j] = mini->input[*i];
		(*j)++;
		(*i)++;
		while(mini->input[*i] != '\'' && mini->input[*i] != '\0')
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
	int	q;//? str_exit_status
	int	len;

	r = 0;
	c = 0;
	q = -1;
	len = *i;
	printf("posizione[%i] e carattere[%c]\n", len, mini->input[*i]);
	if (mini->input[*i] == '$')
	{
		len++;
		if (mini->input[len] == '?')
		{
			while(mini->str_exit_status[++q])
					mini->c_input[(*j)++] = mini->str_exit_status[q];
			len++;
			if (mini->input[len] == '\0' || mini->input[len] == ' ')
			{
				*i = len;
				return ;
			}
			while (mini->input[len] != ' ')
			{
				mini->c_input[*j] = mini->input[len];
				(len)++;
				(*j)++;
				if (mini->input[len] == ' ' || mini->input[len] == '\0')
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
				&& (mini->input[len] < 'A' || mini->input[len] > 'Z') && (mini->input[len] != '_' )))
			{
				c++;
				while(mini->env[r][c]!= '\0')
				{
					mini->c_input[*j] = mini->env[r][c];
					c++;
					(*j)++;
					if(mini->env[r][c] == '\0')
					{
						*i = len;
						if (mini->input[len] == '"')
						{
							printf("d quote\n");
							alloc_double_quotes(i, j, mini);
						}
						else if (mini->input[len] == '\'')
						{
							printf("s quote\n");
							alloc_single_quotes(i, j, mini);
						}
						return ;
					}
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
