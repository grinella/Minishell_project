/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:06:40 by grinella          #+#    #+#             */
/*   Updated: 2024/04/04 02:20:52 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_variable_env(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0
			&& ((mini->env[i][ft_strlen(str)] == '=')
			|| (mini->env[i][ft_strlen(str)] == '\0')))
		{
			free(mini->env[i]);
			while (mini->env[i])
			{
				mini->env[i] = mini->env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

static int	valid_str(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	my_unset(t_mini *mini, t_toks *toks)
{
	int	i;

	i = 1;
	while (toks->word[i])
	{
		if (!valid_str(toks->word[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				toks->word[i]);
			g_exit_status = 1;
			return ;
		}
		else
		{
			remove_variable_env(mini, toks->word[i]);
			g_exit_status = 0;
		}
		i++;
	}
}
