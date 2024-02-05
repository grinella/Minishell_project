/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:24:08 by Gabriele          #+#    #+#             */
/*   Updated: 2024/02/05 15:58:56 by Gabriele         ###   ########.fr       */
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
			while (s[i] != '"' && s[i] != '\0')
				i++;
			if(s[i] == '"' || s[i] != '\0')
				i++;
		}
		if (s[i] != c)
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
		if(s[i] == '"') // aggiunto
		{
			i++;
			while (s[i] != '"' && s[i] != '\0')//
				i++;
			if(s[i] == '"') //
				i++;
		} // aggiunto
	}
	printf("mini_len_word: %d\n", i);
	return (i);
}

static int	mini_len_quote(char const *s)
{
	int		i;

	i = 0;
	if(s[i] == '"')
	{
		i++;
		while (s[i] != '"' && s[i] != '\0')
			i++;
		if(s[i] == '"' || s[i] != '\0')
			i++;
	}
	printf("mini_len_quote: %d\n", i);
	sleep(1);
	return (i);
}

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
		if(s[i] == '"')
		{
			str[j] = (char *)malloc(sizeof(char) * (mini_len_quote(&s[i]) + 1));
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
		}
		else if (s[i] != c)
		{
			str[j] = (char *)malloc(sizeof(char) * (mini_len_word(&s[i], c) + 1));
			if (!str[j])
			{
				mini_free(str, j);
				return ;
			}
			k = 0;
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
