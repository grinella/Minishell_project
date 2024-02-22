#include "include/minishell.h"

static int	mini_count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if(s[i] == '"')
		{
			count++;
			i++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
			if(s[i] == '"' || s[i] != '\0')
				i++;
		}
		else if (s[i] != c)
		{
			//condizione per le pipe
			while (s[i] != c && s[i] != '\0')
			{
				count++;
				while (s[i]!= c && s[i] != '\0' && s[i] != '|' && s[i] != '<' && s[i] != '>')
					i++;
				if (s[i] == '|' || s[i] == '<' || s[i] == '>')
				{
					if ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i - 1] != ' ')
					{
						count++;
						if (s[i + 1] == '<' || s[i + 1] == '>')
							i++;
					}
				}
				i++;
			}	
		}
		else
			i++;
	}
	printf("count=%i\n", count);
	return (count);
}

static int	mini_len_word(char const *s, int i, char c)
{
	int		len;

	len = i;
	while (s[i] != c && s[i] != '\0' && s[i] != '|' && s[i] != '<' && s[i] != '>')
	//&& s[i] != '|' && s[i] != '<' && s[i] != '>') parte aggiunta al while sopra
	//da controllare tutte le funzioni che utilizzano questa funzione 
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			i++;
			if ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i - 1] != ' ')
			{
				if (s[i + 1] == '<' || s[i + 1] == '>')
					i++;
			}
		}
		i++;
		// if(s[i] == '"' || s[i] == '|' || s[i] == '>' || s[i] == '<')
		// {
		// 	if (i - len == 0)
		// 		i++;
		// 	if ((s[i] == '>' || s[i] == '<') && (s[i - 1] != '|'))
		// 		i++;
		// 	printf("i-len=%i\n", (i - len));
		// 	return (i - len);
		// }
		// if (s[i + 1] == '|' && s[i + 1] == '<' && s[i + 1] == '>' && ++i)
		// 	return (i - len);
	}
	return (i - len);
}

static int	mini_len_quotes(char const *s, int i, char c)
{
	int		len;

	len = i;
	i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	if (s[i] == '\0')
	{
		return (0);
		// exit (0);
	}
	return (i - len);
}

int	is_pipe_redir(char const *s, int i)//da controllare tutte le funzioni che utilizzano questa funzione
{
	if (s[i] == '<' || s[i] == '>')
	{
		if (s[i + 1] == '<' || s[i + 1] == '>')
			return (2);
	}
	else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		return (1);
	return (1);
}

// void	alloc_quote(char **str, int i, int j, char const *s)
// {
// 	int len = mini_len_quote(&s[i], '"');
// 	str[j] = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!str[j])
// 	{
// 		// In caso di fallimento dell'allocazione della memoria, puoi gestire l'errore qui
// 		fprintf(stderr, "Errore durante l'allocazione della memoria\n");
// 		exit(EXIT_FAILURE); // O qualsiasi altra gestione dell'errore che preferisci
// 	}
// 	strncpy(str[j], &s[i], len); // Copia la porzione tra virgolette nella nuova stringa
// 	str[j][len] = '\0'; // Assicura che la stringa sia terminata correttamente
// }

static void	mini_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

void	mini_fill_str(char **str, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			i += 1;
			str[j] = ft_substr(s, i, mini_len_quotes(s, i, '"'));
			if (mini_len_quotes(s, i, '"') == 0)
			{
				printf("Error: missing quote\n");
				free_matrix(str);
				return ;
				// DEVE USCIRE DA QUI, TORNARE AL MAIN CON IL MESSAGGIO DI ERRORE
				// PRONTO PER RICEVERE UN NUOVO INPUT
			}
			i += mini_len_quotes(s, i, '"');
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			if (s[i] == '"')
				i++;
			j++;
		}
		else if (s[i] == '\'')
		{
			i += 1;
			str[j] = ft_substr(s, i, mini_len_quotes(s, i, '\''));
			i += mini_len_quotes(s, i, '\'');
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			if (s[i] == '\'')
				i++;
			j++;
		}
		else if (s[i] != c && s[i] != '"' && s[i] != '\'')
		{
				str[j] = ft_substr(s, i, mini_len_word(s, i, c));
				i += mini_len_word(s, i, c);
				if (s[i] == '|' || s[i] == '>' || s[i] == '<')//attualmente il comando restituisce una stringa vuota se c'è uno spazio prima della pipe
				{
					j++;
					str[j] = ft_substr(s, i, is_pipe_redir(s, i));
					i += 1;
				}
				printf("cosa guardo: %c\n", s[i]);
				if (!str[j])
				{
					mini_free(str, j);
					return ;
				}
				j++;
		}
		else
			i++;
		while (s[i] == c && (s[i] != '\0' && s[i] != '"' && s[i] != '\''))
			i++;
	}
	str[j] = 0;
}

char	**mini_split(char const *s, char c)
{
	char	**mtr;

	if (!s)
		return (NULL);
	mtr = (char **)calloc(sizeof(char *), (mini_count_words(s, c) + 1));
	if (!mtr)
		return (NULL);
	mini_fill_str(mtr, s, c);
	// if (mini_len_quotes(s, i, '\'') == 0 || mini_len_quotes(s, i, '"') == 0)
	// {
	// 	free_matrix(mtr);
	// 	return ;
	// }
	ft_print_matrix(mtr);
	return (mtr);
}
