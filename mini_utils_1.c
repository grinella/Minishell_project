/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:24:08 by Gabriele          #+#    #+#             */
/*   Updated: 2024/02/07 14:40:28 by Gabriele         ###   ########.fr       */
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

static int	mini_len_word(char const *s, char c) // DA MODIFICARE AGGIUNGENDO UNA CONDIZIONE PER LE VIRGOLETTE
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	printf("mini_len_word: %d\n", i);
	return (i);
}

// static int	mini_len_quote(char const *s, char c)
// {
// 	int		i;

// 	i = 0;
// 	if (s[i] == c )
// 		i++;
// 	while (s[i] != c && s[i] != '\0')
// 	{
// 		i++;
// 	}
// 	printf("mini_len_quote: %d\n", i);
// 	printf("stringa tra le quote: %s\n", &s[i]);
// 	return (i);
// }

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
	int		k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		k = 0;
		// if (s[i] == '"')
		// {
		// 	str[j] = (char *)malloc(sizeof(char) * (mini_len_quote(&s[i], '"') + 1));
		// 	// str[j] = (char *)malloc(sizeof(char) * (len + 1));
		// 	if (!str[j])
		// 	{
		// 		// In caso di fallimento dell'allocazione della memoria, puoi gestire l'errore qui
		// 		fprintf(stderr, "Errore durante l'allocazione della memoria\n");
		// 		exit(EXIT_FAILURE); // O qualsiasi altra gestione dell'errore che preferisci
		// 	}
			
		// 	// strncpy(str[j], &s[i], len); // Copia la porzione tra virgolette nella nuova stringa
		// 	str[j][k++] = '\0'; // Assicura che la stringa sia terminata correttamente
		// 	// alloc_quote(&str[j], i, j, s);
		// 	i += mini_len_quote(&s[i], '"') + 1;
		// 	j++;
		// }
		if (s[i] != c)
		{
			str[j] = (char *)malloc(sizeof(char) * (mini_len_word(&s[i], c) + 1));
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			while (s[i] != c && s[i] != '\0')
				str[j][k++] = s[i++];
			str[j++][k] = '\0';
		}
		else
			i++;
	}
	str[j] = NULL;
}

char	**mini_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (mini_count_words(s, c) + 1));
	if (!str)
		return (NULL);
	mini_fill_str(str, s, c);
	ft_print_matrix(str);
	return (str);
}

/*
while(s[i] == '"')
		{
			printf("mini_fill_str: %d\nlettera: %c\n", i, s[i]);
			str[j] = (char *)malloc(sizeof(char) * (mini_len_quote(&s[i]) + 1));
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			k = 0;
			printf("stringa tra le quote1: %s\n", &s[i]);
			while (s[i] != c && s[i] != '\0')
				str[j][k++] = s[i++];
			str[j++][k] = '\0';
			printf("stringa tra le quote2: %s\n", &s[i]);
		}



		if (s[i] == '"')
		{
			str[j] = malloc(sizeof(char) * (mini_len_quote(&s[i]) + 1));
			i += mini_len_quote(&s[i]);
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			k = 0;
			while (s[i] == '"' && s[i] != '\0')
				str[j][k++] = s[i++];
			str[j++][k] = '\0';
		}


mini_len_word
				if(s[i] == '"') // aggiunto
		{
			i++;
			while (s[i] != '"' && s[i] != '\0')//
				i++;
			if(s[i] == '"') //
				i++;
		} // aggiunto

*/
// static int	mini_len_quote(char const *s)
// {
// 	int		i;

// 	i = 0;
// 	if(s[i] == '"')
// 	{
// 		i++;
// 		while (s[i] != '"' && s[i] != '\0')
// 			i++;
// 		if(s[i] == '"' || s[i] != '\0')
// 			i++;
// 	}
// 	printf("mini_len_quote: %d\n", i);
// 	sleep(1);
// 	return (i);
// }