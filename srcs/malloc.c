/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:15:52 by agouby            #+#    #+#             */
/*   Updated: 2019/03/05 15:27:17 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

int		get_format(size_t size)
{
	if (size <= TINY_LIMIT)
		return (TINY);
	if (size <= SMALL_LIMIT)
		return (SMALL);
	return (LARGE);
}

void	*valloc(size_t size)
{
	void	*ptr;
	int		format;
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	size = align_page(LARGE, size);
	format = get_format(size);
	if (!g_page || format == LARGE)
	{
		ret = create_page(format, size);
		pthread_mutex_unlock(&g_mutex);
		return (ret);
	}
	ptr = search_free_chunk(format, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void	*calloc(size_t count, size_t size)
{
	size_t	full_size;
	void	*new_alloc;

	full_size = count * size;
	new_alloc = malloc(full_size);
	if (!new_alloc)
		return (NULL);
	if (full_size)
		ft_bzero(new_alloc, full_size);
	return (new_alloc);
}

void	*malloc(size_t size)
{
	void	*ptr;
	void	*ret;
	int		format;

	pthread_mutex_lock(&g_mutex);
	size = align_16(size);
	format = get_format(size);
	if (!g_page || format == LARGE)
	{
		ret = create_page(format, size);
		pthread_mutex_unlock(&g_mutex);
		return (ret);
	}
	ptr = search_free_chunk(format, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
