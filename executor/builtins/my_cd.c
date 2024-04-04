/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:15:38 by grinella          #+#    #+#             */
/*   Updated: 2024/04/04 02:21:05 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_realloc(t_mini *mini, char *str, int size)
{
	char	**mtr_new;
	int		i;

	mtr_new = malloc(sizeof(char *) * (size));
	i = 0;
	while (i < size)
	{
		if (mini->env[i])
			mtr_new[i] = ft_strdup(mini->env[i]);
		else
			mtr_new[i] = ft_strdup(str);
		i++;
	}
	free_matrix(mini->env);
	mtr_new[i] = NULL;
	return (mtr_new);
}

void	set_pwd(char *old, char *new, t_mini *mini, int i)
{
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "PWD=", 4) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("PWD=", new);
			break ;
		}
		i++;
	}
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD=", 7) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("OLDPWD=", old);
			break ;
		}
		i++;
	}
	if (mini->env[i] == NULL)
		mini->env = ft_realloc(mini, ft_strjoin("OLDPWD=", old),
				sizeof(char *) * (i + 1));
}

void	my_cd(t_mini *mini, t_toks *toks)
{
	char	*oldpwd;
	char	*get;

	oldpwd = getcwd(0, 0);
	if (toks->word[1] == NULL)
	{
		// chdir(get_env("HOME", mini));
		chdir(ft_substrchr(get_env("HOME", mini), '=', 1));
		set_pwd(oldpwd, ft_substrchr(get_env("HOME", mini), '=', 1), mini, 0);
		g_exit_status = 0;
	}
	else if (toks->word[1] && chdir(toks->word[1]) == -1)
	{
		printf("minishell: cd: ");
		if (errno == EACCES)
			printf("%s: Permission denied\n", toks->word[1]);
		else
			printf("%s: No such file or directory\n", toks->word[1]);
		g_exit_status = 1;
	}
	else
	{
		get = getcwd(0, 0);
		chdir(get);
		set_pwd(oldpwd, get, mini, 0);
		g_exit_status = 0;
		free(get);
		get = NULL;
	}
	free(oldpwd);
}
