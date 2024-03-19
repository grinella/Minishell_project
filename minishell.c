#include "include/minishell.h"

int	g_exit_status;

void	free_node(t_toks *toks)
{
	t_toks	*tmp;
	t_toks	*current;

	if (toks == NULL)
		return ;
	current = toks;
	while (current)
	{
		tmp = current->next;
		free_matrix(current->word);
		current = tmp;
	}
	free(current);
	toks = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	//free(matrix);
	return ;
}

void	free_all(t_mini *mini)
{
	if (mini->input != NULL)
		free (mini->input);
	if (mini->c_input != NULL)
		free (mini->c_input);
}

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
//funzione da cancellare che printa i nodi
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
		while (toks->word[i])
		{
			printf("posizione matrice:%i\ncontenuto matrice:%s\n", i, toks->word[i]);
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

//funzione che inizializza le varie variabili quando le aggiungeremo, per adesso inizializza soltanto l'env
void	init_mini(t_mini *mini, char **env)
{
	put_env(mini, env);
}

void	mini_routine(t_mini *mini, t_toks *toks)
{
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	mini->str_exit_status = ft_itoa(g_exit_status);// stringa con l'exit status aggiornato
	mini->input = readline("shell>> ");
	if (mini->input == NULL)
	{
		//free_node(toks);
		ft_ctrld(mini);
	}
	if (mini->input[0] != '\0' && only_space(mini->input) == 1)
	{
		if (mini->input && mini->input[0])
		{
			add_history(mini->input);
		}
		lexer(mini, toks);
		printf("input:%s\n", mini->input);
		printf("input pulito:%s\n", mini->c_input);
		free_all(mini);
	}
	else
		free(mini->input);
	free(mini->str_exit_status);// freeo la variabile str_exit_status per aggiornarla al prossimo giro senza sovrascriere
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
		init_mini(mini, env);
		while(1)
			mini_routine(mini, toks);
		free_matrix(mini->env);
		free(mini);
	}
	return (0);
}