/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:28:28 by grinella          #+#    #+#             */
/*   Updated: 2024/04/04 15:36:43 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(char **cmd, char **env)
{
	struct stat	buff;
	int			i;
	char		**base;
	char		*temp;
	char		*path;

	i = 0;
	search_ap(cmd, buff);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == NULL)
		return (printf("Execve failed: Bad Address\n"), NULL);
	base = ft_split((env[i] + 5), ':');
	i = -1;
	while (base && base[++i])
	{
		temp = ft_strjoin(base[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (!lstat(path, &buff))
			return (free_matrix(base), path);
		free(path);
	}
	free_matrix(base);
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
		if (path != NULL)
			execve(path, cmd, mini->env);
		else
		{
			perror("Execve failed");
			exit(EXIT_FAILURE);
		}
	}
	if (mini->here_doc_flag == 1)
		unlink("./temp.txt");
	free(path);
}

int	search_redir(t_mini *mini, t_toks *tmp)
{
	if (tmp->type == 4 || tmp->type == 5)
	{
		close(mini->tmp_in);
		if (tmp->type == 4)
		{
			if (redir_in(tmp->word, mini) == -1)
				return (-1);
		}
		else if (tmp->type == 5)
		{
			here_doc(tmp->word, mini);
			mini->here_doc_flag = 1;
		}
		dup2(mini->tmp_in, 0);
		close(mini->tmp_in);
	}
	else if (tmp->type == 2 || tmp->type == 3)
	{
		close(mini->tmp_out);
		redir_out(tmp->word, tmp->type, mini);
	}
	dup2(mini->tmp_out, 1);
	close(mini->tmp_out);
	return (0);
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

void	executor(t_mini *mini, t_toks *toks, int *std_in, int *std_out)
{
	t_toks	*tmp;

	*std_in = dup(0);
	*std_out = dup(1);
	mini->tmp_in = dup(*std_in);
	tmp = toks;
	while (tmp)
	{
		while (toks && toks->type != 0)
			toks = toks->next;
		setup(mini, toks, *std_out);
		while (tmp && tmp->type != 1)
		{
			if (search_redir(mini, tmp) == -1)
				return ;
			tmp = tmp->next;
		}
		if ((is_builtin(mini, toks)) == 0)
			execute_commands(mini, toks->word);
		if (tmp)
			tmp = tmp->next;
		if (toks)
			toks = toks->next;
	}
}
