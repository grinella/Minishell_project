#include "../../include/minishell.h"

void	my_echo(t_toks *toks)
{
	int n;
	int	i;

	n = 0;
	i = 1;
	if (toks->word[i] == NULL)
	{
		printf("\n");
		return ;
	}
	else if (!ft_strncmp(toks->word[i], "-n", 3))
	{
		i++;
		n++;
	}
	while(toks->word[i] != NULL)
	{
		printf("%s", toks->word[i]);
		if (toks->word[i+1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return ;
}
