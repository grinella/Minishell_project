/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:48:07 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 03:02:50 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	is_builtin(t_mini *mini, t_toks *toks)
{
	int		i;

	i = 0;
	if (!ft_strncmp(toks->word[i], "exit", 5))
		my_exit(toks);
	else if (!ft_strncmp(toks->word[i], "cd", 3))
		my_cd(mini, toks);
	else if (!ft_strncmp(toks->word[i], "export", 7))
		my_export(mini, toks, 0);
	else if (!ft_strncmp(toks->word[i], "unset", 6))
		my_unset(mini, toks);
	else if (!ft_strncmp(toks->word[i], "pwd", 4))
		my_pwd(mini);
	else if (!ft_strncmp(toks->word[i], "env", 4))
		my_env(mini, toks);
	else if (!ft_strncmp(toks->word[i], "echo", 5))
		my_echo(toks, 0);
	else
	{
		printf("\nEXECUTOR:\n");
		executor(mini, toks);
	}
	// else
	// {
	// 	signal(SIGINT, SIG_IGN);
	// 	signal(SIGQUIT, SIG_IGN);
	// 	//exec_cmd(prompt, cmd);
	// }
	return ;
}
