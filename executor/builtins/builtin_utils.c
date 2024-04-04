/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:33:46 by grinella          #+#    #+#             */
/*   Updated: 2024/04/04 22:35:59 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*pre_post(const char *s, int pre_or_post, int i, int s_len)
{
	char	*tmp;

	if (pre_or_post == -1)
	{
		tmp = (ft_substr(s, 0, i));
		return (tmp);
	}
	else if (pre_or_post == 0)
	{
		tmp = (ft_substr(s, 0, i + 1));
		return (tmp);
	}
	else if (pre_or_post == 1)
	{
		tmp = ((ft_substr(s, i + 1, s_len)));
		return (tmp);
	}
	return (NULL);
}

char	*ft_substrchr(const char *s, char c, int pre_or_post)
{
	int		i;
	int		s_len;
	char	*tmp;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			tmp = pre_post(s, pre_or_post, i, s_len);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

static char	**env_export_alpha(char **mt, int i, int i2, int len)
{
	char	*temp;

	while (i < len - 1)
	{
		i2 = 0;
		while (i2 < len - i - 1)
		{
			if (ft_strncmp(mt[i2], mt[i2 + 1], ft_strlen(mt[i2 + 1])) > 0)
			{
				temp = mt[i2];
				mt[i2] = mt[i2 + 1];
				mt[i2 + 1] = temp;
			}
			i2++;
		}
		i++;
	}
	return (mt);
}

void	ft_print_env_export(t_mini *mini)
{
	int		i;
	char	*tmp0;
	char	*tmp1;
	char	**mtr;
	
	i = 0;
	mtr = env_export_alpha(ft_mtr_copy(mini), 0, 0, ft_count_mtr(mini->env));
	while (mtr[i] != NULL)
	{
		tmp0 = ft_substrchr(mtr[i], '=', 0);
		tmp1 = ft_substrchr(mtr[i], '=', 1);
		if (ft_search_char(mtr[i], '=') == 1
			|| ft_search_char(mtr[i], '=') == 2)
			printf("declare -x %s\"%s\"\n", tmp0, tmp1);
		else
			printf("declare -x %s\n", mtr[i]);
		i++;
		free(tmp0);
		free(tmp1);
	}
	free_matrix(mtr);
	return ;
}

int	ft_check_export(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '\0') && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
	{
		i++;
		if (str[i] == '\0')
			return (1);
	}
	printf("export: `%s': not a valid identifier\n", str);
	g_exit_status = 1;
	return (0);
}
