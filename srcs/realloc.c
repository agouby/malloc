/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 20:11:32 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 19:10:17 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

	if (!chunk->next || !chunk->next->free
			|| (chunk->size + chunk->next->size + chunk_ssize() < size))
		return (NULL);
	full_size = chunk->size + chunk->next->size + chunk_ssize();
	attach_next(chunk);
	set_chunk(chunk, size, 0);
	if (full_size - size > chunk_ssize())
		split_chunk(chunk, full_size - size - chunk_ssize());
	return (chunk->ptr);
}

t_chunk	*reduce_chunk(t_chunk *chunk, size_t size)
{
	size_t old_size;

	old_size = chunk->size;
	if (old_size - size > chunk_ssize())
	{
		chunk->size = size;
		split_chunk(chunk, old_size - size - chunk_ssize());
	}
	return (chunk->ptr);
}

void	*reallocf(void *ptr, size_t size)
{
	void *new_alloc;

	new_alloc = realloc(ptr, size);
	if (!new_alloc)
		free(ptr);
	return (new_alloc);
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
		return (NULL);
	if (chunk->size > size)
		ptr = reduce_chunk(chunk, size);
	else
	{
		if (chunk->size != size && !(ptr = extend_chunk(chunk, size)))
			return (reallocate(chunk, size));
	}
	return (ptr);
}
