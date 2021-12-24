/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:36:27 by amalecki          #+#    #+#             */
/*   Updated: 2021/11/23 10:43:09 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result)
		ft_memset(result, '\0', count * size);
	return (result);
}

void	*ft_memset(void *s, int c, size_t n)
{
	while (n && s)
		*((char *)s + --n) = (unsigned char)c;
	return (s);
}

char	*ft_strdup(const char *c)
{
	size_t		i;
	char		*result;

	result = (char *)malloc(ft_strlen(c) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i <= ft_strlen(c))
	{
		*(result + i) = *(c + i);
		i++;
	}
	return (result);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (i);
	while (*(c + i++))
		;
	return (i - 1);
}
