#include "../include/minishell.h"

//QUALCOSINA FUNZIONA MA NON SO SE E' CORRETTO
void	splitter(t_mini *mini, t_toks *toks)
{
	printf("\nAAAAc_input = %s\n", mini->c_input);
	if (mini->c_input)
		toks->word = mini_split(mini->c_input, ' ');
}
