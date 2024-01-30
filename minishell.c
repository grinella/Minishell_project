/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:56:20 by grinella          #+#    #+#             */
/*   Updated: 2024/01/28 19:01:34 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// char	*lexer()
// {
// 	ft_find_word
// 	ft_find_redir // input[j] != '>' && input[j] != '>>' && input[j] != '<'
	
// }
void	routine(t_mini *mini)
{
	lexer(mini);
	//parser(lexer);
	//executor(parser);
}

int	main(int argc, char **argv, char **envp)
{
	char	*output;
	t_mini	*mini;
	
	(void)argv;
	mini = malloc(sizeof(t_mini));
	if(argc == 2)
	{
		// if (argc != 1)
		// {
		// 	printf("Error: too many arguments\n");
		// 	return (1);
		// }
		//get_env(envp);
		while(1)
		{
			mini->input = readline("shell>> ");
			//output // lexer, parser, executor
			{
				add_history(mini->input);
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