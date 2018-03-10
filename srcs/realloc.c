/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 20:11:32 by agouby            #+#    #+#             */
/*   Updated: 2018/03/10 18:04:36 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
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

void	*reallocate(t_chunk *chunk, size_t size)
{
	void	*new_alloc;

	if (!(new_alloc = malloc(size)))
		return (NULL);
	if (chunk)
	{
		ft_memcpy(new_alloc, chunk->ptr, chunk->size);
		free(chunk->ptr);
	}
	return (new_alloc);
}

void	*extend_chunk(t_chunk *chunk, size_t size)
{
	size_t full_size;

	if (!chunk->next || !chunk->next->free ||
			(chunk->size + chunk->next->size + CHUNK_SSIZE < size))
		return (NULL);
	full_size = chunk->size + chunk->next->size + CHUNK_SSIZE;
	chunk->next = chunk->next->next;
	set_chunk(chunk, size, 0);
	if (full_size - size > CHUNK_SSIZE)
		split_chunk(chunk, full_size - size - CHUNK_SSIZE);
	return (chunk->ptr);
}

t_chunk	*reduce_chunk(t_chunk *chunk, size_t size)
{
	size_t old_size;

	old_size = chunk->size;
	if (old_size - size > CHUNK_SSIZE)
	{
		chunk->size = size;
		split_chunk(chunk, old_size - size - CHUNK_SSIZE);
	}
	return (chunk->ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_chunk *chunk;
	t_page	*p;

	size = align_16(size);
	if (!ptr || !size)
		return (reallocate(ptr, size));
	p = fetch_first_page(NULL, 0);
	if (!(chunk = search_ptr(ptr, &p)))
		return (reallocate(NULL, size));
	if (chunk->size > size)
		ptr = reduce_chunk(chunk, size);
	else
	{
		if (chunk->size != size && !(ptr = extend_chunk(chunk, size)))
			return (reallocate(chunk, size));
	}
	return (ptr);
}
