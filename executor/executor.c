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
		close(mini->tmp_in);
		if (access(path, F_OK) == 0)
			execve(path, cmd, mini->env);
		else
		{
			perror("Execve failed");
			exit(EXIT_FAILURE);
		}
	}
	if (mini->here_doc_flag == 1)
		unlink("./temp.txt");
}

void	search_redir(t_mini *mini, t_toks *tmp)
{
	if (tmp->type == 4 || tmp->type == 5)
	{
		close(mini->tmp_in);
		if (tmp->type == 4)
		{
			redir_in(tmp->word, mini);
		}
		else if (tmp->type == 5)
		{
			here_doc(tmp->word, mini);
			mini->here_doc_flag = 1;
		}
		if (mini->tmp_in > 0)
		{
			dup2(mini->tmp_in, 0);
			close(mini->tmp_in);
		}
	}
	else if (tmp->type == 2 || tmp->type == 3)
	{
		close(mini->tmp_out);
		redir_out(tmp->word, tmp->type, mini);
	}
	dup2(mini->tmp_out, 1);
	close(mini->tmp_out);
}

void	setup(t_mini *mini, t_toks *toks, int std_out)
{
	dup2(mini->tmp_in, 0);
	close(mini->tmp_in);
	mini->here_doc_flag = 0;
	if (mini->cmd_count > 1 && toks->cmd_pos != mini->cmd_count)
		create_pipes(mini);
	if (toks->cmd_pos == mini->cmd_count)
		mini->tmp_out = dup(std_out);
}

void	executor(t_mini *mini, t_toks *toks)
{
	int		status;
	t_toks	*tmp;
	int		std_in;
	int		std_out;

	std_in = dup(0);
	std_out = dup(1);
	mini->tmp_in = dup(std_in);
	tmp = toks;
	if (toks->type == 0 && toks->next == NULL && toks->prev == NULL)
		execute_commands(mini, toks->word);
	else
	{
		while (tmp)
		{
			while (toks && toks->type != 0)
				toks = toks->next;
			setup(mini, toks, std_out);
			while (tmp && tmp->type != 1)
			{
				search_redir(mini, tmp);
				tmp = tmp->next;
			}
			execute_commands(mini, toks->word);
			if (tmp)
				tmp = tmp->next;
			if (toks)
				toks = toks->next;
		}
		reset_redir(std_in, std_out);
	}
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_exit_status = status;
}
