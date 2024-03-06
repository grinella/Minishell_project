#include "../include/minishell.h"

char	*find_path(char **cmd, char **env)
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
		if (!lstat(ft_strjoin(temp, cmd[0]), &buff))
		{
			path = ft_strjoin(temp, cmd[0]);
			free(temp);
			return (path);
		}
	}
	free(temp);
	return (NULL);
}

void	execute_commands(t_mini *mini, char **cmd)
{
	int		status;
	char	*path;
	pid_t	pid;

	path = find_path(cmd, mini->env);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, cmd, mini->env);
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
	while (toks)
	{
		//if (!ft_strncomp (toks->word[0]))//se c'è exit)
		//	my_exit(mini);
		//if (toks->next->word[0] != NULL && toks->next->type == 1)
			//is pipe = true
		//is_builtin(mini, toks, &i);
		if(toks->type == 0)
			execute_commands(mini, toks->word);
		toks = toks->next;
	}
}
