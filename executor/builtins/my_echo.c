#include "../include/minishell.h"

// il primo if controlla se è presente l'opzione -n
// il while stampa gli argomenti come nell'implementazione originale
// il secondo if controlla se deve stampare il carattere di nuova riga
void	print_env(t_mini *p, int i)
{
	char	*cor_env;

	p->toks[i]++;
	cor_env = ft_strdup(p->toks[i]);
	printf("env preso: %s\n", cor_env);
}

void	my_echo(t_mini *p)
{
	// t_parse	*parser;
	int		i;
	int		n;
	int		j;

	j = 1;
	i = 0;
	n = 1; // p->toks_count contiene il numero di argomenti
	while (ft_strncmp(p->toks[j], "echo", 4))
	{
		j++;
	}
	while (p->toks)
	{
		//ft_putstr_fd(p->toks[n++], 1);
		i++;
	}
	if (ft_strncmp(p->toks[i], "-n", 2))
		//ft_putstr_fd("\n", 1);
	return ;
}
	// parser = (t_parse *)ft_calloc(sizeof(t_parse));
	// printf("%d\n", n);
	// if (p->toks_count > 0)
	// {
	// 	if (!ft_strncmp(p->toks[1], "-n", 2))
	// 		i++;
	// }
	// while (i <= n)
	// {
	// 	ft_putstr_fd(p->toks[i], 1);
	// 	i++;
	// }
	// if (!ft_strncmp(p->toks[1], "-n", 2))
	// 	write(1, "\n", 1);
//}
/*
int	my_echo(t_prompt *p)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	// Gestisce l'opzione -n per non stampare il carattere di nuova riga alla fine.
	if (((t_mini *)p->cmds->content)->toks && \
		!ft_strncmp(((t_mini *)p->cmds->content)->toks[1], "-n", 2))
	{
		newline = 0;
		i++;
	}
	// Stampa gli argomenti separati da spazi sulla console.
	while (((t_mini *)p->cmds->content)->toks && \
		((t_mini *)p->cmds->content)->toks[i])
	{
		ft_putstr_fd(((t_mini *)p->cmds->content)->toks[i], 1);
		if (((t_mini *)p->cmds->content)->toks[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	// Stampa una nuova riga se l'opzione -n non è specificata.
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
*/