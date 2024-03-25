#include "../include/minishell.h"

void	create_pipes(t_mini *mini)
{
	int	fdpipe[2];

	pipe(fdpipe);
	mini->std_in = fdpipe[0];
	mini->std_out = fdpipe[1];
}

void	redir_out(char	**word, int type, t_mini *mini)
{
	char	*file_name;

	file_name = ft_strdup(word[1]);
	if (type == 2)
		mini->std_out = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == 3)
		mini->std_out = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (mini->std_out < 0)
		perror("minishell: error while opening the file\n");
	dup2(mini->std_out, STDOUT_FILENO);
	close(mini->std_out);
}

void	redir_in(char **word, t_mini *mini)
{
	char	*file_name;

	file_name = ft_strdup(word[1]);
	mini->std_in = open(file_name, O_RDONLY);
	if (mini->std_in < 0)
		perror("minishell: error while opening the file\n");
	dup2(mini->std_in, STDIN_FILENO);
	close(mini->std_in);
}

void	set_redir(t_mini *mini, t_toks *toks, int *fdout)
{
	if (toks->cmd_pos == 1 && mini->cmd_count > 1)
	{
		dup2(mini->std_out, 1);
		close(mini->std_out);
		//close(mini->std_in);
	}
	else if (toks->cmd_pos > 1 && toks->cmd_pos < mini->cmd_count)
	{
		dup2(mini->std_in, 0);
		close(mini->std_in);
		dup2(mini->std_out, 1);
		close(mini->std_out);
	}
	else if (toks->cmd_pos > 1 && toks->cmd_pos == mini->cmd_count)
	{
		dup2(mini->std_in, 0);
		close(mini->std_in);
		dup2(*fdout, 1);
		close(*fdout);
		*fdout = -1;
	}
}

void	reset_redir(int fdin, int fdout)
{
	if (fdin > 0)
	{
		dup2(fdin, 0);
		close(fdin);
	}
	if (fdout != -1 || fdout > 1) //porcoddio funziona così nce credo lallero
	{
		dup2(fdout, 1);
		close(fdout);
	}
}
