/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:15:38 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 23:36:21 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_realloc(char **mtr_old, char *str, int size)
{
	char	**mtr_new;
	int		i;

	mtr_new = malloc(sizeof(char *) * (size));
	i = 0;
	while (i < size)
	{
		printf("realloc\n");
		if (mtr_old[i])
			mtr_new[i] = ft_strdup(mtr_old[i]);
		else
			mtr_new[i] = ft_strdup(str);
		i++;
	}
	// free_matrix(mtr_old);
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
		mini->env = ft_realloc(mini->env, ft_strjoin("OLDPWD=", old),
				sizeof(char *) * (i + 1));
}

void	my_cd(t_mini *mini, t_toks *toks)
{
	char	*oldpwd;
	char	*get;

	oldpwd = getcwd(0, 0);
	if (toks->word[1] == NULL)
	{
		chdir(get_env("HOME", mini));
		set_pwd(oldpwd, get_env("HOME", mini), mini, 0);
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
	}
	if (oldpwd != NULL)
		free(oldpwd);
	free(get);
}
