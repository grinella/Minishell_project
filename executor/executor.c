/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:16:46 by eugenio           #+#    #+#             */
/*   Updated: 2024/02/08 14:49:28 by Gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	execute_commands(t_mini *mini)
{
	int		status;
	char	*path;
	pid_t	pid;

	path = find_path(mini, mini->env);
	printf("J\n");
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, mini->toks, mini->env);
		printf("K\n");
		perror("Execve failed");
		printf("L\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("M\n");
		if (WIFEXITED(status))
			printf("%d\n", WEXITSTATUS(status));
		else
			printf("\n");
	}
}