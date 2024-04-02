/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:28:34 by grinella          #+#    #+#             */
/*   Updated: 2024/04/02 18:39:56 by grinella         ###   ########.fr       */
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
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free_matrix(mini->env);
	if (toks)
		free_all(mini, toks);
	exit(g_exit_status);
}

void	sig_ignore(void)
{
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
