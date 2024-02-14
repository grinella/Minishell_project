#include "../include/minishell.h"

/*
int	builtin(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "exit") == 0) //free everything and exit
			exit(0);
	else if (strcmp(mini->toks[0], "echo") == 0 && mini->toks[1])
	{
		i = 1;
		if (strncmp(mini->toks[i], "-n", 2) == 0) //funzione che trova la prima parola e fa strcmp con -n
		{
			i++;
			while (mini->toks[i])
			{
				ft_putstr_fd(mini->toks[i], 1); // ricordarsi nel parser di cambiare il $ con il valore della variabile d'ambiente
				i++;
				//if (mini->toks[i])
				//	write(1, " ", 1);
			}
		}
		else
		{
			while (mini->toks[i])
			{
				ft_putstr_fd(mini->toks[i], 1);
				//write(1, " ", 1);
				i++;
			}
			printf("\n");
		}
		return (0);
	}
	return (1);
}

int	builtin_2(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "env") == 0)
	{
		while (mini->env[i])
		{
			printf("%s\n", mini->env[i]);
			i++;
		}
		printf("\n");
	}
	else if (strcmp(mini->toks[0], "export") == 0);
	else if (strcmp(mini->toks[0], "unset") == 0)
	{
		//funzione che cerca la variabile d'ambiente e la elimina
		if (mini->toks[1] == NULL)
			return (0);
		while (mini->toks[i])
		{
			if (ft_isdigitalpha(mini->toks[i]) == 0)
			{
				write(1, "unset: not a valid identifier\n", 31);
				return (0);
			}
			i++;
		}
		mini->env = unset_cmd(mini->env, mini->toks[1]);
	}
	else
		return (1);
	return (0);
}

int	builtin_3(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "cd") == 0)
	{
		if (mini->toks[1])
			chdir(mini->toks[1]);
		else
			chdir(getenv("HOME"));
		//change_pwd(mini);
		//cambiare la variabile d'ambiente PWD nell'env
	}
	else if	(strcmp(mini->toks[0], "pwd") == 0)
		printf("%s\n", getcwd(NULL, 0)); // questo oppure cerca nell'envp la variabile PWD e la printa
	else
		return (1);
	return (0);
}*/

// typedef struct	s_prompt
// {
// 	char	**env;
// 	char	*pwd;
// }	t_prompt;

void	is_builtin(t_mini *mini)
{
	if (!ft_strncmp(mini->toks[0], "exit", 4))
		my_exit(mini);
	else if (!ft_strncmp(mini->toks[0], "cd", 2))
		my_cd(mini);
	else if (!ft_strncmp(mini->toks[0], "export", 6))
		my_export(mini);
	else if (!ft_strncmp(mini->toks[0], "unset", 5))
		my_unset(mini);
	else if (!ft_strncmp(mini->toks[0], "pwd", 3))
		my_pwd(mini);
	else if (!ft_strncmp(mini->toks[0], "env", 3))
		my_env(mini->env);
	else if (!ft_strncmp(mini->toks[0], "echo", 4))
		my_echo(mini);
	else if (1)
	{
		execute_commands(mini);
	}
	// else
	// {
	// 	signal(SIGINT, SIG_IGN);
	// 	signal(SIGQUIT, SIG_IGN);
	// 	//exec_cmd(prompt, cmd);
	// }
	return ;
}

/*
int	is_builtin(t_mini *n)
{
	int		l;

	if (!n->toks)
		return (0);
	if ((n->toks && ft_strchr(*n->toks, '/')) || (n->env && \
		ft_strchr(*n->env, '/')))
		return (0);
	l = ft_strlen(*n->toks);
	if (!ft_strncmp(*n->toks, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->toks, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->toks, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*n->toks, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*n->toks, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*n->toks, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*n->toks, "exit", l) && l == 4)
		return (1);
	return (0);
}
*/