/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:39:36 by agouby            #+#    #+#             */
/*   Updated: 2018/03/11 19:56:47 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			ft_bzero(void *s, size_t n)
{
	while (n >= 8)
	{
		*(long *)s = 0;
		s += 8;
		n -= 8;
	}
	while (n >= 4)
	{
		*(int *)s = 0;
		s = (char *)s + 4;
		n -= 4;
	}
	while (n)
	{
		*(char *)s = 0;
		s++;
		n--;
	}
}

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	while (n)
	{
		if (n > 7)
		{
			n -= 8;
			*((long*)(dst + n)) = *((long*)(src + n));
		}
		if (n > 3)
		{
			n -= 4;
			*((int*)(dst + n)) = *((int*)(src + n));
		}
		if (n)
		{
			n--;
			*((char*)(dst + n)) = *((char*)(src + n));
		}
	}
	return (dst);
}

static size_t	ft_strlen(const char *str)
{
	int     *addr;
	size_t  i;

	addr = (int *)str;
	i = 0;
	while (1)
	{
		if (!(*addr & 0xFF))
			return (i);
		if (!(*addr & 0xFF00))
			return (i + 1);
		if (!(*addr & 0xFF0000))
			return (i + 2);
		if (!(*addr & 0xFF000000))
			return (i + 3);
		addr++;
		i += 4;
	}
	return (i);
}

void			ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}
