#include "../include/minishell.h"

void	ft_ctrlc(int sign)
{
		(void)sign;
		write(1, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
}

void	ft_ctrld(t_mini *mini)
{
	g_exit_status = 0;
	free_matrix(mini->env);
	if (mini->input != NULL)
		free(mini->input);
	exit(g_exit_status);
}

void	sig_ignore(void)
{
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

