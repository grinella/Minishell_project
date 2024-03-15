#include "../../include/minishell.h"

void	is_builtin(t_mini *mini, t_toks *toks)//(t_toks *toks) //da mettere il  puntatore *i
{
	int		i;

	i = 0;
	// LE FUNZIONI DEVONO ESSERE ESEGUITE QUANDO NEL NODO[i][0] C'E' UNA BUILTIN
	// NODO[i][0] sarebbe la prima stringa di un nodo x che ha come prima parola una possibile builtin
	if (!ft_strncmp(toks->word[i], "exit", 5))
		my_exit(toks);// se l'exit viene controllato in executor.c non serve controllarlo qui
	else if (!ft_strncmp(toks->word[i], "cd", 3))
		my_cd(mini, toks);
	// else if (!ft_strncmp(toks->word[i] /*nodo[i][0]*/, "export", 7))
	// 	my_export(mini);
	// else if (!ft_strncmp(toks->word[i] /*nodo[i][0]*/, "unset", 6))
	// 	my_unset(mini);
	else if (!ft_strncmp(toks->word[i], "pwd", 4))
		my_pwd(mini);
	else if (!ft_strncmp(toks->word[i], "env", 4))
		my_env(mini, toks);
	else if (!ft_strncmp(toks->word[i], "echo", 5))
		my_echo(toks);
	else
		executor(mini, toks);
	// else
	// {
	// 	signal(SIGINT, SIG_IGN);
	// 	signal(SIGQUIT, SIG_IGN);
	// 	//exec_cmd(prompt, cmd);
	// }
	return ;
}
