#include "../include/minishell.h"

//QUALCOSINA FUNZIONA MA NON SO SE E' CORRETTO
void	splitter(t_mini *mini, t_toks *toks)
{
	//int	i;

	//i = 0;
	if (mini->c_input)
		toks->word = mini_split(mini->c_input, ' ');
	//while(toks->word)
	//{
	//	if(toks->word[i] == )
	//}
}
