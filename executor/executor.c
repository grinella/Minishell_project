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
		if (access(path, F_OK) == 0)
			execve(path, cmd, mini->env);
		perror("Execve failed");
		exit(EXIT_FAILURE);
	}
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_exit_status = status;
}

void	executor(t_mini *mini, t_toks *toks)
{
	t_toks	*tmp;
	int		fdin;
	int		fdout;


	fdin = dup(0);
	fdout = dup(1);
	tmp = toks;
	if(toks->type == 0 && toks->next == NULL && toks->prev == NULL)
		execute_commands(mini, toks->word);
	else
	{
		while(tmp)
		{
			while(toks && toks->type != 0)
				toks = toks->next;
			if (toks->cmd_pos == mini->cmd_count)
				set_redir(mini, toks, &fdout);
			if (mini->cmd_count > 1)
				create_pipes(mini);
			while (tmp && tmp->type != 1)
			{
				if (tmp->type == 4)
				{
					redir_in(tmp->word, mini);
				}
				else if (tmp->type == 2 || tmp->type == 3)
				{
					redir_out(tmp->word, tmp->type, mini);
				}
				tmp = tmp->next;
			}
			if (toks->cmd_pos < mini->cmd_count)
				set_redir(mini, toks, &fdout);
			execute_commands(mini, toks->word);
			if (tmp)
				tmp = tmp->next;
			if (toks)
				toks = toks->next;
		}
		reset_redir(fdin, fdout);
	}
}
