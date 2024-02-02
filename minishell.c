/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:56:20 by grinella          #+#    #+#             */
/*   Updated: 2024/02/02 12:24:01 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// char	*lexer()
// {
// 	ft_find_word
// 	ft_find_redir // input[j] != '>' && input[j] != '>>' && input[j] != '<'
	
// }

char *routine(t_mini *riga)
{
	//lexer(riga->input);
	//parser(lexer);
	//executor(parser);
	return (riga->input);
}

//funzione da cancellare che printa la matrici
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



int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	t_toks	*toks;
	
	(void)argv;
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	if(argc == 1)
	{
		mini = (t_mini *)malloc(sizeof(t_mini));
		toks = (t_toks *)malloc(sizeof(t_toks));
		init_mini(mini, env);
		while(1)
		{
			mini->input = readline("shell>> ");
			//output // lexer, parser, executor
			// output = routine(mini);
			//clean_input(mini->input, i);
			if (mini->input && mini->input[0])
			{
				add_history(mini->input);
			}
			lexer(mini, toks);
			printf("input:%s\n", mini->input);
			printf("input pulito:%s\n", mini->c_input);
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
