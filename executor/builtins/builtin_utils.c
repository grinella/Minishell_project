/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:33:46 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 02:34:37 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_substrchr(const char *s, char c, int pre_or_post)
{
	int		i;
	int		s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (pre_or_post == -1)
				return (ft_substr(s, 0, i));
			else if (pre_or_post == 0)
				return (ft_substr(s, 0, i + 1));
			else if (pre_or_post == 1)
				return (ft_substr(s, i + 1, s_len));
		}
		i++;
	}
	return (NULL);
}

void	ft_print_env_export(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i] != NULL)
	{
		if (ft_search_char(mini->env[i], '=') == 1
			|| ft_search_char(mini->env[i], '=') == 2)
			printf("declare -x %s\"%s\"\n",
				ft_substrchr(mini->env[i], '=', 0),
				ft_substrchr(mini->env[i], '=', 1));
		else
			printf("declare -x %s\n", mini->env[i]);
		i++;
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
