/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:23:20 by grinella          #+#    #+#             */
/*   Updated: 2024/03/21 16:01:19 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	find_dollar_env_len(int *i, int *j, t_mini *mini)
// {
// 	int	r;
// 	int	c;
// 	int	len;

// 	r = 0;
// 	c = 0;
// 	len = *i;
// 	if (mini->input[*i] == '$')
// 	{
// 		len++;
// 		if (mini->input[len] == '?')
// 		{
// 			len++;
// 			if (mini->input[len] == '\0' || mini->input[len] == ' ')
// 			{
// 				*i = len;
// 				*j += ft_strlen(mini->str_exit_status);
// 				return ;
// 			}
// 			while (mini->input[len] != ' ')
// 			{
// 				len++;
// 				(*j)++;
// 				if (mini->input[len] != ' ')
// 				{
// 					*i = len;
// 					return ;
// 				}
// 			}
// 		}
// 		while (mini->env[r] != NULL)
// 		{
// 			while ((mini->input[len] == mini->env[r][c])
// 				&& ((mini->input[len] >= 'a' && mini->input[len] <= 'z')
// 				|| (mini->input[len] >= 'A' && mini->input[len] <= 'Z')
// 				|| (mini->input[len] >= '0' && mini->input[len] <= '9')
// 				|| (mini->input[len] == '_')))
// 			{
// 				c++;
// 				len++;
// 			}
// 			if (mini->env[r][c] == '='
// 				&& ((mini->input[len] < 'a' || mini->input[len] > 'z')
// 				&& (mini->input[len] < 'A' || mini->input[len] > 'Z')
// 				&& (mini->input[len] < '0' || mini->input[len] > '9')
// 				&& (mini->input[len] != '_')))
// 			{
// 				c++;
// 				(*j)++;
// 				while (mini->env[r][c] != '\0')
// 				{
// 					c++;
// 					(*j)++;
// 				}
// 				if (mini->env[r][c] == '\0')
// 				{
// 					*i = len;
// 					return ;
// 				}
// 			}
// 			else
// 			{
// 				r++;
// 				c = 0;
// 				if (mini->env[r] == NULL)
// 				{
// 					while ((mini->input[len] >= 'a' && mini->input[len] <= 'z')
// 						|| (mini->input[len] >= 'A' && mini->input[len] <= 'Z')
// 						|| (mini->input[len] >= '0' && mini->input[len] <= '9')
// 						|| (mini->input[len] == '_'))
// 						len++;
// 					*i = len;
// 					return ;
// 				}
// 				len = *i + 1;
// 			}
// 		}
// 	}
// }
int	question_mark(int *len, int *i, int *j, t_mini *mini)
{
	*len += 1;
	if (g_exit_status > 255)
	{
		while (g_exit_status > 255)
			g_exit_status -= 256;
		free(mini->str_exit_status);
		mini->str_exit_status = ft_itoa(g_exit_status);
	}
	*j += ft_strlen(mini->str_exit_status);
	while (mini->input[*len] != ' ' && mini->input[*len] != '\0')
	{
		*len += 1;
		(*j)++;
		if (mini->input[*len] == ' ' || mini->input[*len] == '\0')
		{
			*i = *len;
			return (1);
		}
	}
	return (0);
}

void	find_dollar_env_len(int *i, int *j, t_mini *mini, int len)
{
	char	*tmp;

	len++;
	while (mini->input[len])
	{
		if (mini->input[len] == '?')
			if (question_mark(&len, i, j, mini) == 1)
				return ;
		if (ft_isalnum(mini->input[len]) || mini->input[len] == '_')
			len++;
		else
			break ;
	}
	tmp = get_env(ft_substr(mini->input, *i + 1, len - *i), mini);
	if (tmp == NULL)
	{
		*i = len;
		return ;
	}
	*i = len;
	*j += ft_strlen(tmp);
}

void	clean_input(t_mini *mini, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mini->c_input = ft_calloc(sizeof(char *), (len + 1));
	while (mini->input[i] == ' ')
		i++;
	while (mini->input[i] != '\0')
	{
		if (mini->input[i] == ' ')
			alloc_spaces(&i, &j, mini);
		else if (mini->input[i] == '\'')
			alloc_single_quotes(&i, &j, mini);
		else if (mini->input[i] == '"')
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

void	clean_input_len(t_mini *mini)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (mini->input[i] == ' ')
		i++;
	while (mini->input[i] != '\0')
	{
		if (mini->input[i] == ' ')
			space_len(&i, &j, &flag, mini->input);
		else if (mini->input[i] == '"' || mini->input[i] == '\'')
			quotes_len(&i, &j, mini);
		else if (mini->input[i] == '$')
			find_dollar_env_len(&i, &j, mini, i);
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
	if (mini->input[0] == '\0')
	{
		return (NULL);
	}
	if (mini->input)
	{
		clean_input_len(mini);
		splitter(mini, toks);
	}
	return (mini->input);
}
