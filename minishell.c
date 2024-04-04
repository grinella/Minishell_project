/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:53 by grinella          #+#    #+#             */
/*   Updated: 2024/04/04 19:55:29 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_exit_status;

int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
	{
		i++;
		if (str[i] == '\0')
			return (0);
	}
	return (1);
}

void	mini_routine(t_mini *mini, t_toks *toks)
{
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	mini->cmd_count = 0;
	mini->str_exit_status = ft_itoa(g_exit_status);
	mini->input = readline("shell>> ");
	if (mini->input == NULL)
	{
		ft_ctrld(mini, toks);
	}
	if (mini->input[0] != '\0' && only_space(mini->input) == 1)
	{
		if (mini->input && mini->input[0])
		{
			add_history(mini->input);
		}
		toks = lexer(mini, toks);
		free_routine(mini, toks);
	}
	if (mini->str_exit_status)
	{
		free(mini->str_exit_status);
		mini->str_exit_status = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	t_toks	*toks;

	(void)argv;
	g_exit_status = 0;
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	if (argc == 1)
	{
		mini = (t_mini *)ft_calloc(1, sizeof(t_mini));
		toks = NULL;
		put_env(mini, env);
		while (1)
		{
			mini_routine(mini, toks);
		}
	}
	return (0);
}
