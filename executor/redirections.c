#include "../include/minishell.h"

void	create_pipes(t_mini *mini)
{
	int	fdpipe[2];

	pipe(fdpipe);
	mini->tmp_in = fdpipe[0];
	mini->tmp_out = fdpipe[1];
}

void	redir_out(char	**word, int type, t_mini *mini)
{
	char	*file_name;

	file_name = ft_strdup(word[1]);
	if (type == 2)
		mini->tmp_out = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == 3)
		mini->tmp_out = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (mini->tmp_out < 0)
		perror("minishell: error while opening the file\n");
}

void	redir_in(char **word, t_mini *mini)
{
	char	*file_name;

	file_name = ft_strdup(word[1]);
	mini->tmp_in = open(file_name, O_RDONLY);
	if (mini->tmp_in < 0)
		perror("minishell: error while opening the file\n");
}

void	here_doc(char **word, t_mini *mini)
{
	int		fd;
	char	*str;

	fd = open("temp.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		perror("Input open error\n");
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, word[1], ft_strlen(word[1])) == 0)
		{
			free(str);
			break ;
		}
		free(str);
	}
	close(fd);
	mini->tmp_in = open("temp.txt", O_RDONLY);
}

void	reset_redir(int fdin, int fdout)
{
	dup2(fdin, 0);
	close(fdin);
	dup2(fdout, 1);
	close(fdout);
}
