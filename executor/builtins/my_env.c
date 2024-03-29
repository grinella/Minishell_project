/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:47:06 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 01:26:24 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_search_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i + 1] != '\0')
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_env(char *search, t_mini *mini)
{
	int	i;
	int	search_len;

	search_len = ft_strlen(search);
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], search, search_len) == 0)
			return (mini->env[i] + search_len + 1);
		i++;
	}
	return (NULL);
}

void	my_env(t_mini *mini, t_toks *toks)
{
	int	i;

	i = 0;
	if (toks->word[1] == NULL)
	{
		while (mini->env[i] != NULL)
		{
			if (ft_search_char(mini->env[i], '=') == 1
				|| ft_search_char(mini->env[i], '=') == 2)
				printf("%s\n", mini->env[i]);
			i++;
		}
	}
	else
	{
		printf("env: %s: No such file or directory\n", toks->word[1]);
		printf("env: too many arguments\n");
		g_exit_status = 127;
	}
}
