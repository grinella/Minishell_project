/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:06:30 by grinella          #+#    #+#             */
/*   Updated: 2024/04/05 16:52:15 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)src;
	if (!dest && !size)
		return (size);
	i = ft_strlen(dest);
	if (i >= size)
		return (size + ft_strlen(str));
	j = 0;
	while (str[j] && i < size - 1)
	{
		dest[i] = str[j];
		i++;
		j++;
	}
	dest[i] = 0;
	return (i + ft_strlen(&str[j]));
}
