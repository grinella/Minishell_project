/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:24:08 by Gabriele          #+#    #+#             */
/*   Updated: 2024/02/12 16:18:36 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printf("count = %d\n", count);
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
		(i)++;
	}
	printf("mini_len_word: %d\n", (i - len));
	return (i - len);
}

static int	mini_len_quotes(char const *s, int *i, char c)
{
	int		len;

	len = *i;
	*i += 1;
	while (s[*i] != c && s[*i] != '\0')
	{
		(*i)++;
	}
	if (s[*i] == '\0')
	{
		printf("Error: missing quote\n");
		return (0);
	}
	printf("mini_len_quote: %d\n", (*i - len));
	printf("stringa tra le quote: %s\n", &s[len]);
	printf("lettera: %c\n", s[*i]);
	return (*i - len);
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
		printf("s: %s\n", s);
		if (s[i] == '"')
		{
			i += 1;
			str[j] = ft_substr(s, i, mini_len_quotes(s, &i, '"'));
			printf("stringa tra le quote: %s\n", str[j]);
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			if (s[i] == '"')
				i++;
			j++;
		}
		if (s[i] == '\'')
		{
			i += 1;
			str[j] = ft_substr(s, i, mini_len_quotes(s, &i, '\''));
			printf("stringa tra le quote: %s\n", str[j]);
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			if (s[i] == '\'')
				i++;
			j++;
		}
		else if (s[i] != c)
		{
			if (s[i] == '"' || s[i] == '\'')
			{
				j++;
			}
			else
			{
				printf("j value %d\n", j);
				str[j] = ft_substr(s, i, mini_len_word(s, i, c));
				printf("stringa caratteri: %s\n", str[j]);
				if (!str[j])
				{
					mini_free(str, j);
					return ;
				}
				j++;
			}
		}
		else
			i++;
		while (s[i] == c && s[i] != '\0' && s[i] != '"' && s[i] != '\'')
			i++;
	}
	printf("meglio la j quanto vale %d  %s\n", j, str[0]);
	str[j] = NULL;
	printf("ancora meglio %s\n", str[0]);
	//ft_print_matrix(str);
}

char	**mini_split(char const *s, char c)
{
	char	**str;
	
	printf("la stringona %s\n", s);
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (mini_count_words(s, c)));
	if (!str)
		return (NULL);
	mini_fill_str(str, s, c);
	//ft_print_matrix(str);
	return (str);
}
