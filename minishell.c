#include "include/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("check");
		free(matrix[i]);
		i++;
	}
}

void	free_all(t_mini *mini)
{
	if(mini->input)
		free (mini->input);
	if(mini->c_input)
		free (mini->c_input);
}

int	only_space(char* str)
{
	int	i;

	i = 0;
	while(str[i] == ' ')
	{
		i++;
		if(str[i] == '\0')
			return (0);
	}
	return(1);
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

void	mini_routine(t_mini *mini, t_toks *toks)
{
	mini->input = readline("shell>> ");
	if(mini->input[0] != '\0' && only_space(mini->input) == 1)
	{
		if (mini->input && mini->input[0])
		{
			add_history(mini->input);
		}
		lexer(mini, toks);
		printf("input:%s\n", mini->input);
		printf("input pulito:%s\n", mini->c_input);
		free_all(mini);//free_all(mini, toks);
	}
	else
		free(mini->input);
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
			mini_routine(mini, toks);
		free_matrix(mini->env);
		free(mini);
		free(toks);
	}
	return (0);
}
