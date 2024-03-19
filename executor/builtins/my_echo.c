/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:11:28 by grinella          #+#    #+#             */
/*   Updated: 2024/03/19 20:40:14 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	my_echo(t_toks *toks, int n)
{
	int	i;

	i = 1;
	if (toks->word[i] == NULL)
	{
		printf("\n");
		return ;
	}
	else if (!ft_strncmp(toks->word[i], "-n", 3))
	{
		i++;
		n++;
	}
	while (toks->word[i] != NULL)
	{
		printf("%s", toks->word[i]);
		if (toks->word[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	g_exit_status = 0;
	return ;
}
