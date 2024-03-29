/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:08:19 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 02:26:02 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_realloc_export(char **mtr_old, char *name, char *str, int size)
{
	char	**mtr_new;
	int		i;

	mtr_new = malloc(sizeof(char *) * (size));
	i = 0;
	while (i < size)
	{
		if (mtr_old[i] && ft_strncmp(mtr_old[i], name, ft_strlen(name)) != 0)
			mtr_new[i] = ft_strdup(mtr_old[i]);
		else if (mtr_old[i] && ft_strncmp(mtr_old[i],
				name, ft_strlen(name)) == 0)
			mtr_new[i] = ft_strdup(str);
		else if (!mtr_old[i])
			mtr_new[i] = ft_strdup(str);
		i++;
	}
	free_matrix(mtr_old);
	mtr_new[i] = NULL;
	return (mtr_new);
}

void	type_one(t_mini *mini, t_toks *toks, int *i, char *tmp)
{
	if (ft_search_char(toks->word[*i], '=') == 2)
	{
		tmp = ft_substrchr(toks->word[*i], '=', -1);
		if (get_env(tmp, mini) == NULL)
			mini->env = ft_realloc_export(mini->env, tmp, toks->word[*i],
					ft_count_matrix(mini->env) + 1);
		else if (get_env(tmp, mini) != NULL)
			mini->env = ft_realloc_export(mini->env, tmp, toks->word[*i],
					(ft_count_matrix(mini->env)));
	}
	else
	{
		tmp = ft_strdup(toks->word[*i]);
		if (get_env(tmp, mini) == NULL)
			mini->env = ft_realloc_export(mini->env, tmp, toks->word[*i],
					ft_count_matrix(mini->env) + 1);
		else if (get_env(tmp, mini) != NULL)
			return ;
	}
}

void	type_tow(t_mini *mini, t_toks *toks, int *i, char *tmp)
{
	tmp = ft_substrchr(toks->word[*i], '=', -1);
	if (get_env(tmp, mini) == NULL)
	{
		if (toks->word[*i + 1] != NULL)
			mini->env = ft_realloc_export(mini->env, tmp,
					ft_strjoin(toks->word[*i], toks->word[*i + 1]),
					ft_count_matrix(mini->env) + 1);
		else if (toks->word[*i + 1] == NULL)
			mini->env = ft_realloc_export(mini->env, tmp, toks->word[*i],
					ft_count_matrix(mini->env) + 1);
	}
	else if (get_env(tmp, mini) != NULL)
	{
		if (toks->word[*i + 1] != NULL)
			mini->env = ft_realloc_export(mini->env, tmp,
					ft_strjoin(toks->word[*i], toks->word[*i + 1]),
					(ft_count_matrix(mini->env)));
		else if (toks->word[*i + 1] == NULL)
			mini->env = ft_realloc_export(mini->env, tmp, toks->word[*i],
					(ft_count_matrix(mini->env)));
	}
	(*i) += 1;
}

void	set_export_env(t_mini *mini, t_toks *toks, int *i, int type)
{
	char	*tmp;

	tmp = NULL;
	if (type == 1)
		type_one(mini, toks, i, tmp);
	else if (type == 2)
		type_tow(mini, toks, i, tmp);
	free(tmp);
}

void	my_export(t_mini *mini, t_toks *toks, int i)
{
	char	*check;

	if (toks->word[1] == NULL)
	{
		ft_print_env_export(mini);
		return ;
	}
	i = 1;
	check = NULL;
	while (toks->word[i] != NULL)
	{
		if (ft_search_char(toks->word[i], '=') == 0)
			check = ft_strdup(toks->word[i]);
		else
			check = ft_substrchr(toks->word[i], '=', -1);
		if (ft_check_export(check) == 0)
			return ;
		if ((ft_search_char(toks->word[i], '=') == 0)
			|| (ft_search_char(toks->word[i], '=') == 2))
			set_export_env(mini, toks, &i, 1);
		else if (ft_search_char(toks->word[i], '=') == 1)
			set_export_env(mini, toks, &i, 2);
		i++;
	}
}
