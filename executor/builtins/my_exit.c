#include "../include/minishell.h"

void	print_error(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
}

int	ft_isdigit_mini(char *str)
{
	int i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		if (str[i] != '\0')
			return (1);
	}
	return (0);
}

void	my_exit(t_toks *toks)
{
	int	i;

	i = 0;
	// Check per vedere se c'è più di un argomento
	if (toks->word[2] != NULL)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	else if (ft_isdigit_mini(toks->word[1]) == 0) // se l'argomento non è numerico stampa l'errore
	{
		if (toks->next == NULL)
		{
			printf("exit\nminishell: exit %s: numeric argument required\n", toks->word[1]);
			g_exit_status = 255;
			exit (g_exit_status);
		}
		else if (toks->next != NULL)
		{
			printf("exit\nminishell: exit %s: numeric argument required\n", toks->word[1]);
			g_exit_status = 0;
			return ;
		}
	}
	else if (toks->word[1] == NULL && toks->next != NULL)
	{
		printf("exit\n");
		g_exit_status = 0;
	}
	// if (!ft_strncmp (toks->word[0], "exit", 5))
	else if (toks->word[1] != NULL && toks->next == NULL)
	{
		printf("exit\n");
		exit (ft_atoi(toks->word[1]));
	}
	// si dovrebbe controllare tutta la riga di comando per vedere
	// se ci sono degli exit ed in caso tutto ciò che lo precede va ignorato
}
