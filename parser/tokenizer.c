#include "../include/minishell.h"

void	cmd_count(t_mini *mini, t_toks *toks)
{
	t_toks	*tmp;

	tmp = toks;
	while (tmp != NULL)
	{
		if (tmp->type == 0)
		{
			mini->cmd_count++;
			tmp->cmd_pos = mini->cmd_count;
		}
		tmp = tmp->next;
	}
}

t_toks	*find_last_node(t_toks *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	toks_len(char **tokens, int *i)
{
	int	j;
	int	x;

	j = *i;
	x = 0;
	if (tokens[j][0] == '|' || tokens[j][0] == '<' || tokens[j][0] == '>')
	{
		if (tokens[j][0] == '<' || tokens[j][0] == '>')
			return (3);
		return (2);
	}
	while (tokens[j] && tokens[j][0] != '|'
		&& tokens[j][0] != '<' && tokens[j][0] != '>')
	{
		x++;
		j++;
	}
	x++;
	return(x);
}

void	fill_node(char **tokens, t_toks *node, int *i)
{
	int	j;

	j = 0;
	node->word = (char **)ft_calloc(sizeof(char *), (toks_len(tokens, i)));
	if (tokens[*i][0] == '|' || tokens[*i][0] == '<' || tokens[*i][0] == '>')
	{
		node->word[j] = ft_strdup(tokens[*i]);
		(*i)++;
		j++;
		if (tokens[*i - 1][0] == '<' || tokens[*i - 1][0] == '>')
		{
			node->word[j] = ft_strdup(tokens[*i]);
			(*i)++;
			j++;
		}
		node->word[j] = NULL;
		return ;
	}
	while (tokens[*i] && tokens[*i][0] != '|'
		&& tokens[*i][0] != '<' && tokens[*i][0] != '>')
	{
		node->word[j] = ft_strdup(tokens[*i]);
		(*i)++;
		j++;
	}
	node->word[j] = NULL;
}

int	complex_toks_len(char **tokens, int *i)
{
	int	j;
	int	count;

	count = 0;
	j = *i;
	while (tokens[j] && tokens[j][0] != '|')
	{
		if (tokens[j][0] == '<' || tokens[j][0] == '>')
			j += 2;
		else
		{
			j++;
			count++;
		}
	}
	count++;
	return (count);
}

void	fill_complex_node(char **tokens, t_toks **toks, t_toks *node, int *i)
{
	int	flag;
	int	j;
	int	x;

	x = *i;
	j = 0;
	flag = 0;
	node->word = (char **)ft_calloc(sizeof(char *),
			(complex_toks_len(tokens, i)));
	while (tokens[*i] && tokens[*i][0] != '|')
	{
		if (tokens[*i][0] == '<' || tokens[*i][0] == '>')
		{
			flag = 1;
			*i += 2;
		}
		else
		{
			node->word[j] = ft_strdup(tokens[*i]);
			j++;
			(*i)++;
		}
	}
	while (tokens[x] && tokens[x][0] != '|' && flag == 1)
	{
		if (tokens[x][0] == '>' && tokens[x][1] == '>')
			append_node(tokens, toks, 3, &x);
		else if (tokens[x][0] == '>')
			append_node(tokens, toks, 2, &x);
		else if (tokens[x][0] == '<' && tokens[x][1] == '<')
			append_node(tokens, toks, 5, &x);
		else if (tokens[x][0] == '<')
			append_node(tokens, toks, 4, &x);
		else
			x++;
	}
	if (x > *i)
		*i = x;
}

void	append_node(char **tokens, t_toks **toks, int type, int *i)
{
	t_toks	*node;
	t_toks	*last_node;

	node = (t_toks *)ft_calloc(1, sizeof(t_toks));
	if (node == NULL)
		return ;
	node->next = NULL;
	node->cmd_pos = 0;
	node->type = type;
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
	if (type != 0)
		fill_node(tokens, node, i);
	else
		fill_complex_node(tokens, toks, node, i);
}

void	tokenizer(char **tokens, t_toks **toks)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
		{
			printf("Error: double pipe\n");
			free_matrix(tokens); // freea tokens
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
	free_matrix(tokens);//NON SO SE FUNZIONA
}

void	splitter(t_mini *mini, t_toks *toks)
{
	char	**tokens;

	tokens = NULL;
	if (mini->c_input)
	{
		tokens = mini_split(mini, ' ');
	}
	tokenizer(tokens, &toks);
	cmd_count(mini, toks);
	//is_builtin(toks); // per testare builtins, poi dovrà essere implementata probabilmente nell'executor
	//ft_print_node(toks);
	executor(mini, toks);
}
