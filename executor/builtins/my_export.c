/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:08:19 by grinella          #+#    #+#             */
/*   Updated: 2024/04/03 21:17:32 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_realloc_export(t_mini *mini, char *name, char *str, int size)
{
	char	**mtr_new;
	int		i;

	mtr_new = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		if (mini->env[i] && ft_strncmp(mini->env[i], name, ft_strlen(name)) != 0)
			mtr_new[i] = ft_strdup(mini->env[i]);
		else if (mini->env[i] && ft_strncmp(mini->env[i],
				name, ft_strlen(name)) == 0)
			mtr_new[i] = ft_strdup(str);
		else if (!mini->env[i])
			mtr_new[i] = ft_strdup(str);
		i++;
	}
	free_matrix(mini->env);
	mtr_new[i] = NULL;
	return (mtr_new);
}

void	type_one(t_mini *mini, t_toks *toks, int *i, char *tmp)
{
	if (ft_search_char(toks->word[*i], '=') == 2)
	{
		tmp = ft_substrchr(toks->word[*i], '=', -1);
		if (get_env(tmp, mini) == NULL)
			mini->env = ft_realloc_export(mini, tmp, toks->word[*i],
					ft_count_matrix(mini->env) + 1);
		else if (get_env(tmp, mini) != NULL)
			mini->env = ft_realloc_export(mini, tmp, toks->word[*i],
					(ft_count_matrix(mini->env)));
	}
	else
	{
		tmp = ft_strdup(toks->word[*i]);
		if (get_env(tmp, mini) == NULL)
			mini->env = ft_realloc_export(mini, tmp, toks->word[*i],
					ft_count_matrix(mini->env) + 1);
		// else if (get_env(tmp, mini) != NULL)
		// 	return ;
	}
	free(tmp);
}

void	type_tow(t_mini *mini, t_toks *toks, int *i, char *tmp)
{
	tmp = ft_substrchr(toks->word[*i], '=', -1);
	if (get_env(tmp, mini) == NULL)
	{
		if (toks->word[*i + 1] != NULL)
			mini->env = ft_realloc_export(mini, tmp,
					ft_strjoin(toks->word[*i], toks->word[*i + 1]),
					ft_count_matrix(mini->env) + 1);
		else if (toks->word[*i + 1] == NULL)
			mini->env = ft_realloc_export(mini, tmp, toks->word[*i],
					ft_count_matrix(mini->env) + 1);
	}
	else if (get_env(tmp, mini) != NULL)
	{
		if (toks->word[*i + 1] != NULL)
			mini->env = ft_realloc_export(mini, tmp,
					ft_strjoin(toks->word[*i], toks->word[*i + 1]),
					(ft_count_matrix(mini->env)));
		else if (toks->word[*i + 1] == NULL)
			mini->env = ft_realloc_export(mini, tmp, toks->word[*i],
					(ft_count_matrix(mini->env)));
	}
	(*i) += 1;
}

// if (toks->word[*i + 1] == NULL)
// 			type_one(mini, toks, i, tmp);

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
	check = NULL;
	while (i <= (ft_count_matrix(toks->word) - 1))
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
		free(check);
	}
	g_exit_status = 0;
}
