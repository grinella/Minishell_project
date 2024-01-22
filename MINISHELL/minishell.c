# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    file.txt                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grinella <grinella@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 19:56:20 by grinella          #+#    #+#              #
#    Updated: 2024/01/22 10:00:16 by grinella          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini		*mini;
	char		*input;

	(void)argv;
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	mini = malloc(sizeof(t_mini));
	initialize_mini(mini);
	get_env(envp, mini);
	while (1)
	{
		input = readline("shell>> ");
		if (input && input[0])
		{
			add_history(input);
		}
		if (input && input[0])
		{
			if (run_lexer(input, mini) && parse_input(mini))
			{
				is_builtin(mini);
			}
		}
		free_cmds(&mini, input);
	}
	return (0);
}