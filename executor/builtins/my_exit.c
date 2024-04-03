/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:58:46 by grinella          #+#    #+#             */
/*   Updated: 2024/04/03 21:16:01 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isdigit_mini(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

// se l'argomento non è numerico stampa l'errore
void	error_numeric(t_mini *mini, t_toks *toks)
{
	if (toks->next == NULL)
	{
		printf("exit\n");
		printf("minishell: exit %s: ", toks->word[1]);
		printf("numeric argument required\n");
		g_exit_status = 255;
		free_all(mini, toks);
		exit (g_exit_status);
	}
	else if (toks->next != NULL)
	{
		printf("exit\nminishell: exit %s: ", toks->word[1]);
		printf("numeric argument required\n");
		g_exit_status = 0;
		return ;
	}
}

void	my_exit(t_mini *mini, t_toks *toks)
{
	if (toks->word[1] == NULL && toks->next == NULL)
	{
		printf("exit\n");
		free_all(mini, toks);
		exit (g_exit_status);
	}
	else if (ft_isdigit_mini(toks->word[1]) == 0 && toks->word[2] == NULL)
		error_numeric(mini, toks);
	else if (toks->word[1] == NULL && toks->next != NULL)
	{
		printf("exit\n");
		g_exit_status = 0;
	}
	else if (ft_isdigit_mini(toks->word[1]) == 1 && toks->word[1] != NULL
		&& toks->word[2] == NULL && toks->next == NULL)
	{
		printf("exit\n");
		free_all(mini, toks);
		exit (ft_atoi(toks->word[1]));
	}
	else
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_exit_status = 1;
	}
}
