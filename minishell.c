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
		free(mini->input);
	if(mini->c_input)
		free(mini->c_input);
}
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
			if(mini->input[0] != '\0')
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
		}
		free_matrix(mini->env);
		free(mini);
		free(toks);
	}
	return (0);
}
