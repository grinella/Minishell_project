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
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	mini_len_word(char const *s, int i, char c)
{
	int		len;

	len = i;
	while (s[i] != c && s[i] != '\0')
	{
		if(s[i] == '"')
		{
			return (i - len);
		}
		i++;
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
		printf("Error: missing quote\n");
		return (0);
	}
	return (i - len);
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
				i += mini_len_word(s, i, ' ');
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
	char	**str;

	if (!s)
		return (NULL);
	//aggiunto un +1 a mini_count_words
	str = (char **)calloc(sizeof(char *), (mini_count_words(s, c) + 1));
	if (!str)
		return (NULL);
	mini_fill_str(str, s, c);
	ft_print_matrix(str);
	return (str);
}
