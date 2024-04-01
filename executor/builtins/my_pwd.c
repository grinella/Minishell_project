/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:14:14 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 23:39:17 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	my_pwd(t_mini *mini)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	(void)mini;
	printf("%s\n", pwd);
	g_exit_status = 0;
	free(pwd);
}
