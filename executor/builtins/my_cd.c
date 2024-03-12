#include "../../include/minishell.h"

// void	my_cd(t_mini mini)
// {
// 	char	*new_dir;
// 	char	*cwd;

// 	cwd = (char *)ft_calloc(sizeof(char *) * mini->prova);
// 	new_dir = NULL;
// 	if (p->args > 0)
// 	{
// 		new_dir = p->toks[1];
// 	}
// 	else
// 	{
// 		printf("entra env");	// Se l'utente non fornisce una directory, vai alla home
// 		new_dir = get_env_char("HOME", mini->env, ft_strlen("HOME"));
// 		printf("%s\n", new_dir);
// 	}
// 	if (new_dir)
// 	{
// 		if (chdir(new_dir) == 0)
// 		{
// 			// L'operazione di cambio directory è avvenuta con successo
// 			// Aggiorna la variabile d'ambiente PWD
// 			if (getcwd(cwd, sizeof(cwd)) != NULL)
// 			{
// 				set_env("PWD", cwd, p->env, 1);
// 			}
// 			//free(cwd);
// 			//Successo
// 		}
// 		else
// 		{
// 			// Errore durante il cambio directory
// 			cont_error(NDIR, new_dir, 1);
// 			free(cwd);
// 			return ; // Errore
// 		}
// 	}
// 	free(cwd);
// 	return ;// Errore
// }

// main per testare la funzione my_cd
// int main(int argc, char **argv)
// {
// 	t_mini	prompt;

// 	prompt.toks = argv;
// 	prompt.toks_count = argc;
// 	return (my_cd(&prompt));
// }
void	set_pwd(char *old, char *new, t_mini *mini)
{
	int i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD=", 7) == 0)
			free(mini->env[i]);
		i++;
	}
	i--;
	mini->env[i] = ft_strjoin("OLDPWD=", old);
}

void	my_cd(t_mini *mini, t_toks *toks)
{
	char	*oldpwd;

	if (toks->word[1] == NULL)
	{
		oldpwd = getcwd(0, 0);
		chdir(getenv("HOME"));
		set_pwd(oldpwd, "HOME", mini); //reset PWD and OLDPWD in env matrix
	}
	else if (toks->word[1] && chdir(toks->word[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", toks->word[1]);
		g_exit_status = 1;
	}
	else
	{
		oldpwd = getcwd(0, 0);
		chdir(toks->word[1]);
	}
}