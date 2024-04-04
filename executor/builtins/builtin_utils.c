/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:33:46 by grinella          #+#    #+#             */
/*   Updated: 2024/04/04 15:04:37 by grinella         ###   ########.fr       */
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
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
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

void	ft_print_env_export(t_mini *mini)
{
	int		i;
	char	*tmp0;
	char	*tmp1;

	i = 0;
	while (mini->env[i] != NULL)
	{
		tmp0 = ft_substrchr(mini->env[i], '=', 0);
		tmp1 = ft_substrchr(mini->env[i], '=', 1);
		if (ft_search_char(mini->env[i], '=') == 1
			|| ft_search_char(mini->env[i], '=') == 2)
			printf("declare -x %s\"%s\"\n", tmp0, tmp1);
		else
			printf("declare -x %s\n", mini->env[i]);
		i++;
		free(tmp0);
		free(tmp1);
	}
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
