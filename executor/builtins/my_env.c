#include "../../include/minishell.h"

void	my_env(t_mini *mini, t_toks *toks)
{
	int	i;

	i = 0;
	if (toks->word[1] == NULL)
	{
		while (mini->env[i] != NULL)
		{
			printf("%s\n", mini->env[i]);
			i++;
		}
	}
	else
	{
		printf("env: %s: No such file or directory\n", toks->word[1]);
		printf("env: too many arguments\n");
		g_exit_status = 127;
	}
}
