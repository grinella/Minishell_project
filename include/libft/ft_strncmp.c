/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:38:21 by grinella          #+#    #+#             */
/*   Updated: 2024/03/28 16:16:33 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	e;

	if (n == 0)
		return (0);
	e = 0;
	while ((s1[e]) && (s2[e]) && (e < n - 1) && (s1[e] == s2[e]))
	{
		e++;
	}
	return ((unsigned char)s1[e] - (unsigned char)s2[e]);
}
