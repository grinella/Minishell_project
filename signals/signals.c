/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:13:26 by grinella          #+#    #+#             */
/*   Updated: 2024/04/04 19:41:53 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_ctrlc(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 1;
}

void	ft_ctrld(t_mini *mini, t_toks *toks)
{
	g_exit_status = 0;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free_matrix(mini->env);
	if (toks)
		free_all(mini, toks);
	if (mini->str_exit_status)
		free(mini->str_exit_status);
	free(mini);
	exit(g_exit_status);
}

void	handleback(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 131;
	exit(g_exit_status);
}
