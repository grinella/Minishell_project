/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:24:08 by Gabriele          #+#    #+#             */
/*   Updated: 2024/02/02 17:45:50 by Gabriele         ###   ########.fr       */
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
			while (s[i] != '"' && s[i] != '\0')
			{
				count++;
				i++;
			}
			if(s[i] == '"' || s[i] != '\0')
			{
				count++;
				i++;
			}
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
	return (count);
}

static int	mini_len_word(char const *s, char c) // DA MODIFICARE AGGIUNGENDO UNA CONDIZIONE PER LE VIRGOLETTE
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
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
		if (s[i] != c)
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
