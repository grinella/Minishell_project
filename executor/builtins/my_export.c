/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:08:19 by grinella          #+#    #+#             */
/*   Updated: 2024/03/28 16:28:51 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_realloc_export(char **mtr_old, char *tmp, char *str, int size)
{
	char	**mtr_new;
	int		i;

	mtr_new = malloc(sizeof(char *) * (size));
	i = 0;
	while (i < size)
	{
		if (mtr_old[i] && ft_strncmp(mtr_old[i], tmp, ft_strlen(tmp)) != 0)
			mtr_new[i] = ft_strdup(mtr_old[i]);
		else if (mtr_old[i] && ft_strncmp(mtr_old[i], tmp, ft_strlen(tmp)) == 0)
			mtr_new[i] = ft_strdup(str);
		else if (!mtr_old[i])
			mtr_new[i] = ft_strdup(str);
		i++;
	}
	free_matrix(mtr_old);
	mtr_new[i] = NULL;
	return (mtr_new);
}

char	*ft_substrchr(const char *s, char c, int pre_or_post)
{
	int		i;
	int		s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (pre_or_post == -1)
				return (ft_substr(s, 0, i));
			else if (pre_or_post == 0)
				return (ft_substr(s, 0, i + 1));
			else if (pre_or_post == 1)
				return (ft_substr(s, i + 1, s_len));
		}
		i++;
	}
	return (NULL);
}

void	set_export(t_mini *mini, t_toks *toks, char *tmp)
{
	if (toks->word[1] != NULL && toks->word[2] == NULL)
	{
		if (get_env(tmp, mini) == NULL)
			mini->env = ft_realloc_export(mini->env, tmp, toks->word[1],
					(ft_count_matrix(mini->env) + 1));
		else if (get_env(tmp, mini) != NULL)
			mini->env = ft_realloc_export(mini->env, tmp, toks->word[1],
					(ft_count_matrix(mini->env)));
	}
	else if (toks->word[2] != NULL)
	{
		if (get_env(tmp, mini) == NULL)
			mini->env = ft_realloc_export(mini->env, tmp,
					ft_strjoin(toks->word[1], toks->word[2]),
					(ft_count_matrix(mini->env) + 1));
		else if (get_env(tmp, mini) != NULL)
			mini->env = ft_realloc_export(mini->env, tmp,
					ft_strjoin(toks->word[1], toks->word[2]),
					(ft_count_matrix(mini->env)));
	}
	return ;
}

void	my_export(t_mini *mini, t_toks *toks, int i)
{
	char	*tmp;

	if (toks->word[1] == NULL)
	{
		while (mini->env[i] != NULL)
		{
			printf("declare -x %s\n", mini->env[i]);
			i++;
		}
		return ;
	}
	tmp = ft_substrchr(toks->word[1], '=', -1);
	if (!tmp)
	{
		printf("Syntax error: '=' not found\n");
		return ;
	}
	else
		set_export(mini, toks, tmp);
}
