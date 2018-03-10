/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 15:31:29 by agouby            #+#    #+#             */
/*   Updated: 2018/03/10 17:17:11 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	connect_chunk(t_chunk *chunk, t_chunk *prev, t_chunk *next)
{
	chunk->next = next;
	chunk->prev = prev;
	if (next)
		next->prev = chunk;
	if (prev)
		prev->next = chunk;
}

void	set_chunk(t_chunk *chunk, size_t size, int free)
{
	chunk->size = size;
	chunk->free = free;
	chunk->ptr = (void *)chunk + CHUNK_SSIZE;
}

void	split_chunk(t_chunk *chunk, size_t size)
{
	t_chunk	*new_chunk;
	t_chunk	*next;

	if (size <= CHUNK_SSIZE)
		return ;
	new_chunk = (t_chunk *)(chunk->ptr + chunk->size);
	set_chunk(new_chunk, size, 1);
	next = (chunk->next) ? chunk->next : NULL;
	connect_chunk(new_chunk, chunk, next);
}

t_chunk	*search_free_chunk_in_page(t_page *p, size_t size)
{
	t_chunk *search;

	search = p->beg;
	while (search && (!search->free || search->size < size))
		search = search->next;
	return (search);
}

void	*search_free_chunk(int format, size_t size)
{
	t_page	*p;
	t_chunk	*search;
	size_t	old_size;

	p = fetch_first_page(NULL, 0);
	search = NULL;
	while (p)
	{
		if (p->format == format)
			if ((search = search_free_chunk_in_page(p, size)))
				break ;
		p = p->next;
	}
	if (search)
	{
		old_size = search->size;
		set_chunk(search, size, 0);
		if (old_size - search->size > CHUNK_SSIZE)
			split_chunk(search, old_size - search->size - CHUNK_SSIZE);
		return (search->ptr);
	}
	else
		return (create_page(format, size));
}
