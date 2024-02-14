#include "../include/minishell.h"

void	my_cd(t_mini *p)
{
	char	*new_dir;
	char	*cwd;

	cwd = (char *)malloc(sizeof(char *) * p->prova);
	new_dir = NULL;
	if (p->args > 0)
	{
		new_dir = p->toks[1];
	}
	else
	{
		printf("entra env");	// Se l'utente non fornisce una directory, vai alla home
		new_dir = get_env_char("HOME", p->env, ft_strlen("HOME"));
		printf("%s\n", new_dir);
	}
	if (new_dir)
	{
		if (chdir(new_dir) == 0)
		{
			// L'operazione di cambio directory è avvenuta con successo
			// Aggiorna la variabile d'ambiente PWD
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				set_env("PWD", cwd, p->env, 1);
			}
			//free(cwd);
			//Successo
		}
		else
		{
			// Errore durante il cambio directory
			cont_error(NDIR, new_dir, 1);
			free(cwd);
			return ; // Errore
		}
	}
	free(cwd);
	return ;// Errore
}

// main per testare la funzione my_cd
// int main(int argc, char **argv)
// {
// 	t_mini	prompt;

// 	prompt.toks = argv;
// 	prompt.toks_count = argc;
// 	return (my_cd(&prompt));
// }
