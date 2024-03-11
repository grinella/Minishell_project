#include "../include/minishell.h"

void	redir_out(char	**word, int type)
{
	char	*file_name;
	int		fd;

	file_name = ft_strdup(word[1]);
	if (type == 2)
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == 3)
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
		perror("minishell: error while opening the file\n");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_in(char **word)
{
	char	*file_name;
	int		fd;

	file_name = ft_strdup(word[1]);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		perror("minishell: error while opening the file\n");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	reset_redir(t_mini *mini)
{
			dup2(mini->std_in, STDIN_FILENO);
			close(mini->std_in);
			dup2(mini->std_out, STDOUT_FILENO);
			close(mini->std_out);
}