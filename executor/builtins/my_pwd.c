/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:14:14 by grinella          #+#    #+#             */
/*   Updated: 2024/04/03 22:03:59 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	my_pwd(int i)
{
	char	*pwd;
	i = 0;

	pwd = getcwd(0, 0);
	i += 1;
	printf("%s\n", pwd);
	g_exit_status = 0;
	free(pwd);
}
