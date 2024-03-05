#include "../include/minishell.h"
#include <stdbool.h>

t_toks	*find_last_node(t_toks *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	toks_len(char **tokens)
{
	int	i;

	i = 0;
	if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
	{
		return(2);
	}
	while (tokens[i] && tokens[i][0] != '|' && tokens[i][0] != '<' && tokens[i][0] != '>')
		i++;
	i++;
	return(i);
}

void	fill_node(char **tokens, t_toks *node, int *i)
{
	int	j;

	j = 0;
	node->word = (char **)ft_calloc(sizeof(char *) , (toks_len(tokens)));
	if (tokens[*i][0] == '|' || tokens[*i][0] == '<' || tokens[*i][0] == '>')
	{
		node->word[j] = ft_strdup(tokens[*i]);
		(*i)++;
		j++;
		node->word[j] = NULL;
		return ;
	}
	while (tokens[*i] && tokens[*i][0] != '|' && tokens[*i][0] != '<' && tokens[*i][0] != '>')
	{
			node->word[j] = ft_strdup(tokens[*i]);
			(*i)++;
			j++;
	}
	node->word[j] = NULL;
}

void	append_node(char **tokens, t_toks **toks, int type, int *i)
{
	t_toks	*node;
	t_toks	*last_node;

	node = (t_toks *)ft_calloc(1 , sizeof(t_toks));
	if (node == NULL)
		return ;
	node->next = NULL;
	node->type = type;
	fill_node(tokens, node, i);
	if (*toks == NULL)
	{
		*toks = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*toks);
		last_node->next = node;
		node->prev = last_node;
	}
}

void	tokenizer(char **tokens, t_toks **toks)
{
	int	i;

	i = 0;
	while(tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
		{
			printf("Error: double pipe\n");
			//richiamo funzione free;
			return ;
		}
		else if (tokens[i][0] == '|')
			append_node(tokens, toks, 1, &i);
		else if (tokens[i][0] == '>' && tokens[i][1] == '>')
			append_node(tokens, toks, 3, &i);
		else if (tokens[i][0] == '>')
			append_node(tokens, toks, 2, &i);
		else if (tokens[i][0] == '<' && tokens[i][1] == '<')
			append_node(tokens, toks, 5, &i);
		else if (tokens[i][0] == '<')
			append_node(tokens, toks, 4, &i);
		else
			append_node(tokens, toks, 0, &i);
	}
}

//QUALCOSINA FUNZIONA ED é PURE CORRETTO
void	splitter(t_mini *mini, t_toks *toks)
{
	char	**tokens;

	tokens = NULL;
	if (mini->c_input)
	{
		tokens = mini_split(mini, ' ');
	}
	tokenizer(tokens, &toks);
	ft_print_node(toks);
	executor(mini, toks); //SBLOCCARE PER BUILTIN E EXECUTE_COMMANDS
}
