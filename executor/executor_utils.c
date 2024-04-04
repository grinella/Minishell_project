/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 22:13:48 by ecaruso           #+#    #+#             */
/*   Updated: 2024/04/04 19:50:23 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_and_wait(int std_in, int std_out)
{
	int		status;

	reset_redir(std_in, std_out);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = (WEXITSTATUS(status));
	}
}

char	*trim_path(char *str, char c)
{
	int	i;

	i = (ft_strlen(str) - 1);
	while (i != 0)
	{
		if (str[i] == c)
		{
			return (ft_substr(str, i + 1, ft_strlen(str) - i));
		}
		i--;
	}
	return (NULL);
}

void	search_ap(char **cmd, struct stat buff)
{
	char	*str;

	if (!lstat(cmd[0], &buff))
	{
		str = trim_path(cmd[0], '/');
		if (!str)
		{
			free (str);
			return ;
		}
		free(cmd[0]);
		cmd[0] = ft_strdup(str);
		free(str);
	}
}
