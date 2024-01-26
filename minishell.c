/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:56:20 by grinella          #+#    #+#             */
/*   Updated: 2024/01/26 18:06:08 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// char	*lexer()
// {
// 	ft_find_word
// 	ft_find_redir // input[j] != '>' && input[j] != '>>' && input[j] != '<'
	
// }
char *ft_output(input)
{
	lexer(input);
	parser(lexer);
	executor(parser);
}



int	main(int argc, char **argv, char **envp)
{
	char		*input;
	int i = 0;

	(void)argv;
	if(argc == 2);
	{
	// if (argc != 1)
	// {
	// 	printf("Error: too many arguments\n");
	// 	return (1);
	// }
	//get_env(envp);
	while(1)
	{
		input = readline("shell>> ");
		//output // lexer, parser, executor
		output = 
		clean_input(input, i);
		if (input && input[0])
		{
			add_history(input);
		}
		// if (input && input[0])
		// {
		// 	if (run_lexer(input, mini) && parse_input(mini))
		// 	{
		// 		is_builtin(mini);
		// 	}
		// }
		// free_cmds(&mini, input);
	}
	}
	return (0);
}