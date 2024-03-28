/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:47:06 by grinella          #+#    #+#             */
/*   Updated: 2024/03/27 16:28:34 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
