/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:08:19 by grinella          #+#    #+#             */
/*   Updated: 2024/03/21 12:08:20 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Stampa le variabili d'ambiente o imposta nuove variabili d'ambiente.
void	my_export(t_mini *p)
{
	char	**env;
	char	**pair;

	// Se il comando export è chiamato senza argomenti, stampa tutte
	// le variabili d'ambiente.
	if (!p->cmds->next)
	{
		env = p->env;
		while (env && *env)
			ft_putendl_fd(*env++, 1);
	}
	// Se il comando export è chiamato con argomenti, imposta nuove
	// variabili d'ambiente.
	while (p->cmds->next)
	{
		pair = ((t_mini *)p->cmds->content)->toks;
		if (pair && *pair)
			p->env = set_env(pair[0], pair[1], p->env, -1);
		p->cmds = p->cmds->next;
	}
}
