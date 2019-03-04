/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 15:31:29 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 19:09:44 by agouby           ###   ########.fr       */
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
	chunk->ptr = (void *)chunk + chunk_ssize();
}

void	split_chunk(t_chunk *chunk, size_t size)
{
	t_chunk	*new_chunk;
	t_chunk	*next;

	if (size <= chunk_ssize())
		return ;
	new_chunk = (t_chunk *)(chunk->ptr + chunk->size);
	set_chunk(new_chunk, size, 1);
	next = (chunk->next) ? chunk->next : NULL;
	connect_chunk(new_chunk, chunk, next);
}
