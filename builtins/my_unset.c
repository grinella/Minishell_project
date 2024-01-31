#include "../include/minishell.h"

/*
// Rimuove variabili d'ambiente.
int	my_unset(t_mini *p)
{
    int g_status = 0;

    // Rimuove le variabili d'ambiente specificate come argomenti.
    while (p->cmds->next)
    {
        char **var = ((t_mini *)p->cmds->content)->toks;
        if (var && *var)
            p->mini_prompt->envp = unset_env(*var, p->mini_prompt->envp);
        p->cmds = p->cmds->next;
    }

    return g_status;
}
*/

/*----------------------------------------------------------*/

// Rimuove una variabile d'ambiente specifica dalla lista.
char	**remove_env(char *var, char **envp)
{
	int		i;
	int		j;
	int		env_len;
	char	**new_envp;

	// Calcola la lunghezza della lista delle variabili d'ambiente.
	env_len = ft_matrixlen(envp);
	// Alloca memoria per la nuova lista senza la variabile d'ambiente specificata.
	new_envp = malloc(sizeof(char *) * (env_len));
	if (!new_envp)
		return (cont_error(MEM, NULL, 1));
	i = -1;
	j = 0;
	while (envp[++i])
	{
		// Se la variabile d'ambiente corrente non corrisponde a quella specificata, la aggiunge alla nuova lista.
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			new_envp[j++] = ft_strdup(envp[i]);
		free(envp[i]);
	}
	// Termina la nuova lista con NULL.
	new_envp[j] = NULL;
	// Libera la memoria della vecchia lista.
	free(envp);
	return (new_envp);
}

// Trova la posizione di una variabile d'ambiente nella lista.
int	find_env_pos(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		// Confronta il nome della variabile d'ambiente con quello specificato.
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	// Se non trova la variabile d'ambiente, restituisce -1.
	return (-1);
}

// Rimuove variabili d'ambiente specifiche dalla lista.
char	**unset_env(char **vars, char **envp)
{
	int	i;
	int	pos;

	i = -1;
	while (vars && vars[++i])
	{
		// Trova la posizione della variabile d'ambiente nella lista e la rimuove.
		pos = find_env_pos(vars[i], envp);
		if (pos != -1)
			envp = remove_env(vars[i], envp);
	}
	return (envp);
}

// Rimuove variabili d'ambiente.
void	my_unset(t_mini *p)
{
	char	**var;

	// Rimuove le variabili d'ambiente specificate come argomenti.
	while (p->cmds->next)
	{
		var = ((t_mini *)p->cmds->content)->toks;
		if (var && *var)
			p->mini_prompt->envp = unset_env(var, p->mini_prompt->envp);
		p->cmds = p->cmds->next;
	}
}
