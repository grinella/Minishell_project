/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:53 by grinella          #+#    #+#             */
/*   Updated: 2024/03/30 01:15:25 by eugenio          ###   ########.fr       */
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

//DA CANCELLAREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
void	ft_print_node(t_toks *toks)
{
	int	pos;
	int	i;

	i = 0;
	pos = 0;
	while (toks)
	{
		i = 0;
		printf("\nPosizione nodo: %i\n", pos);
		printf("Tipo di token: %i\n", toks->type);
		printf("Cmd_pos: %i\n", toks->cmd_pos);
		while (toks->word[i])
		{
			printf("posizione matrice:%i\n", i);
			printf("contenuto matrice:%s\n", toks->word[i]);
			i++;
		}
		toks = toks->next;
		pos++;
	}
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

// funzione che inizializza le varie variabili
// quando le aggiungeremo, per adesso inizializza soltanto l'env
void	init_mini(t_mini *mini, char **env)
{
	put_env(mini, env);
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
		//free_node(toks);
		ft_ctrld(mini, toks);
	}
	if (mini->input[0] != '\0' && only_space(mini->input) == 1)
	{
		if (mini->input && mini->input[0])
		{
			add_history(mini->input);
		}
		toks = lexer(mini, toks);
		free_all(mini, toks);
	}
	//else if (mini->input != NULL)
	//	free(mini->input);
	free(mini->str_exit_status);
}
// freeo str_exit_status per aggiornarla al prossimo giro senza sovrascriere

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
		//init_mini(mini, env);
		while (1)
		{
			put_env(mini, env);
			mini_routine(mini, toks);
			free_matrix(mini->env);
		}
		if (mini->env)
			free_matrix(mini->env);
		free(mini);
	}
	return (0);
}
