/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:56:20 by grinella          #+#    #+#             */
/*   Updated: 2024/01/30 17:32:28 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// char	*lexer()
// {
// 	ft_find_word
// 	ft_find_redir // input[j] != '>' && input[j] != '>>' && input[j] != '<'	
// }

//funzione da cancellare
void	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("posizione matrice:%i\ncontenuto matrice:%s\n", i, matrix[i]);
		i++;
	}
	return ;
}

//funzione che inizializza le varie variabili quando le aggiungeremo, per adesso inizializza soltanto l'env
void	init_mini(t_mini *mini, char **env)
{
	put_env(mini, env);
}

/*void	routine(t_mini *mini)
{
	lexer(mini);
	//parser(lexer);
	//executor(parser);
}*/

int	main(int argc, char **argv, char **env)
{
	//char	*output;
	t_mini	*mini;

	(void)argv;
	if (argc == 1)
	{
		mini = malloc(sizeof(t_mini));
		init_mini(mini, env);
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