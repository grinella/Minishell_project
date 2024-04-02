/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:48:07 by grinella          #+#    #+#             */
/*   Updated: 2024/04/02 18:36:14 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_mini *mini, t_toks *toks)
{
	if (!ft_strncmp(toks->word[0], "exit", 5))
		my_exit(mini, toks);
	else if (!ft_strncmp(toks->word[0], "cd", 3))
		my_cd(mini, toks);
	else if (!ft_strncmp(toks->word[0], "export", 7))
		my_export(mini, toks, 0);
	else if (!ft_strncmp(toks->word[0], "unset", 6))
		my_unset(mini, toks);
	else if (!ft_strncmp(toks->word[0], "pwd", 4))
		my_pwd(mini);
	else if (!ft_strncmp(toks->word[0], "env", 4))
		my_env(mini, toks);
	else if (!ft_strncmp(toks->word[0], "echo", 5))
		my_echo(toks, 0);
	else
		return (0);
	// else
	// {
	// 	signal(SIGINT, SIG_IGN);
	// 	signal(SIGQUIT, SIG_IGN);
	// 	//exec_cmd(prompt, cmd);
	// }
	return (-1);
}
