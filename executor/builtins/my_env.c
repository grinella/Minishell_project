/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:47:06 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 22:24:21 by eugenio          ###   ########.fr       */
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
			return (mini->env[i] );//+ search_len + 1);
		i++;
	}
	return (NULL);
}

void	error_status(t_toks *toks)
{
	if (errno == EACCES)
	{
		printf("env: %s: Permission denied\n", toks->word[1]);
		g_exit_status = 126;
	}
	else if (errno == ENOENT)
	{
		printf("env: %s: No such file or directory\n", toks->word[1]);
		g_exit_status = 127;
	}
	else
	{
		printf("env: Error executing command: %s\n", strerror(errno));
		g_exit_status = 1;
	}
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
		g_exit_status = 0;
	}
	else
		error_status(toks);
}
