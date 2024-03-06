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
		return ;
	}
	else if (toks->word[1])
	{
		// Error: numeric argument required
		// se l'argomento non è numerico stampa l'errore
		if (ft_isdigit_mini(toks->word[1]) == 0)
		{
			printf("exit\nminishell: exit %s: numeric argument required\n", toks->word[1]);
			// return ;
			exit (1);
		}
	}
	else
	// if (!ft_strncmp (toks->word[0], "exit", 5))
	{
		printf("exit\n");
		exit (ft_atoi(toks->word[1]));
	}
	// si dovrebbe controllare tutta la riga di comando per vedere
	// se ci sono degli exit ed in caso tutto ciò che lo precede va ignorato
}
