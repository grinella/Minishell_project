#include "../include/minishell.h"

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
		free(cmd[0]);
		cmd[0] = ft_strdup(str);
	}
}