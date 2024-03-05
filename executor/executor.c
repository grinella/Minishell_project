#include "../include/minishell.h"

char	*find_path(t_toks *toks, char **env)
{
	struct stat	buff;
	int			i;
	char		**base;
	char		*temp;
	char		*path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
	{
		i++;
	}
	base = ft_split((env[i] + 5), ':');
	i = -1;
	while (base && base[++i])
	{
		temp = ft_strjoin(base[i], "/");
		if (!lstat(ft_strjoin(temp, toks->word[0]), &buff))
		{
			path = ft_strjoin(temp, toks->word[0]);
			free(temp);
			return (path);
		}
	}
	free(temp);
	return (NULL);
}

void	execute_commands(t_mini *mini, t_toks *toks)
{
	int		status;
	char	*path;
	pid_t	pid;

	path = find_path(mini, mini->env);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, toks->word, mini->env);
		perror("Execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("%d\n", WEXITSTATUS(status));
		else
			printf("\n");
	}
}

void	executor(t_mini *mini, t_toks *toks)
{
	// serve un modo per passare i nodi a questa funzione
	int i; // questa i serve per iterare i nodi
	
	i = 0;
	// while (/*nodo[i]*/)
	// {
		// if ()//se c'è exit)
		// 	my_exit(mini);
		// if (nodo.next != NULL && nodo.next->type == 1)
		// 	//is pipe = true
		// is_builtin(mini, toks, &i);

		//if (is pipe == true)
		//fork
		//se '|' continui
		//else wait 
		// child
			//check builtin
			//exec	
	// 	i++;
	// }
}
