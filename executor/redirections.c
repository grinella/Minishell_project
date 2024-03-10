#include "../include/minishell.h"

void	redir_out(char	**word)
{
	char	*file_name;
	int		fd;

	file_name = ft_strdup(word[1]);
	fd = open(file_name, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		perror("minishell: error while opening the file\n");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}