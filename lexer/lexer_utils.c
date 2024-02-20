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

void	quotes_len(int *i, int *j, char* input)
{
	if(input[*i] == '"')
	{
		(*i)++;
		(*j)++;
		while(input[*i] != '"' && input[*i] != '\0')
		{
			(*j)++;
			(*i)++;
		}
		(*i)++;
		(*j)++;
	}
	else if(input[*i] == '\'')
	{
		(*j)++;
		(*i)++;
		while(input[*i] != '\'' && input[*i] != '\0')
		{
			(*j)++;
			(*i)++;
		}
		(*j)++;
		(*i)++;
	}
}

void	alloc_spaces(int *i, int *j, int *flag, t_mini *mini)
{
	while(mini->input[*i] == ' ')
	{
		if((*flag) == 0)
		{
			mini->c_input[*j] = mini->input[*i];
			(*flag) = 1;
			(*j)++;
		}
		(*i)++;
	}
}

void	alloc_quotes(int *i, int *j, t_mini *mini)
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
