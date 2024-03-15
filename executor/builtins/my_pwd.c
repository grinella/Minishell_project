#include "../../include/minishell.h"

// Stampa il percorso corrente (current working directory) sulla console.
// int	my_pwd(void)
// {
// 	char	pwd[4096];

// 	if(getcwd(pwd, sizeof(pwd)) == NULL)
// 		printf("%s\n", pwd);
// 	else
// 		printf("shell: the path is borken\n");
// 	return ;
// }

void	my_pwd(t_mini *mini)
{
	char *pwd = get_env("PWD", mini);
	printf("%s\n", pwd);
	// get_env("PWD", mini);
}