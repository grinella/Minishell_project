/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:46:00 by grinella          #+#    #+#             */
/*   Updated: 2024/01/29 18:44:12 by Gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Stampa il percorso corrente (current working directory) sulla console.
void	my_pwd(t_mini *p)
{
	char	*cwd;
	(void)p;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cont_error(NDIR, "", 1);
	}
	ft_putendl_fd(cwd, 1);
	// p->mini_prompt->envp = set_env("OLDPWD", cwd, p->mini_prompt->envp, 6);
	// p->mini_prompt->envp = set_env("PWD", cwd, p->mini_prompt->envp, 3);
	free(cwd);
}
