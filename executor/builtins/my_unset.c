/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:06:40 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 03:26:32 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**remove_variable_env(t_mini *mini, char **mtr_old, char *str, int i)
{
	char	**mtr_new;

	if (get_env(str, mini) == NULL)
		return (mtr_old);
	else if (get_env(str, mini) != NULL)
	{
		mtr_new = malloc(sizeof(char *) * (ft_count_matrix(mtr_old) - 1));
		while (ft_strncmp(mini->env[i], str, ft_strlen(str)) != 0)
		{
			mtr_new[i] = ft_strdup(mtr_old[i]);
			i++;
		}
		if (ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0)
		{
			while (mtr_old[i + 1] != NULL)
			{
				mtr_new[i] = ft_strdup(mtr_old[i + 1]);
				i++;
			}
		}
		printf("AAAAAAA\n");
		mtr_new[i] = NULL;
		free_matrix(mtr_old); // stampa errore quando NON viene commentato
		return (mtr_new);
	}
	return (mtr_old);
}

void	my_unset(t_mini *mini, t_toks *toks)
{
	int	i;
	int	c;

	i = 1;
	c = 0;
	if (toks->word[1] == NULL)
		return ;
	while (toks->word[i] != NULL)
	{
		while (toks->word[i][c])
		{
			if (ft_isalnum(toks->word[i][c]) == 1 || toks->word[i][c] == '_')
				c++;
			else
			{
				printf("minishell: unset: `%s': not a valid identifier\n",
					toks->word[i]);
				g_exit_status = 1;
				return ;
			}
		}
		mini->env = remove_variable_env(mini, mini->env, toks->word[i], 0);
		i++;
	}
	return ;
}
