/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 18:10:07 by agouby            #+#    #+#             */
/*   Updated: 2018/03/11 18:09:58 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	attach_next(t_chunk *chunk)
{
	chunk->size = chunk->size + chunk->next->size + CHUNK_SSIZE;
	chunk->next = chunk->next->next;
	if (chunk->next)
		chunk->next->prev = chunk;
}

static void	combine_free_chunks(t_chunk *chunk)
{
	if (chunk->prev && chunk->prev->free)
	{
		chunk = chunk->prev;
		attach_next(chunk);
	}
	if (chunk->next && chunk->next->free)
		attach_next(chunk);
}

void		free(void *ptr)
{
	t_chunk	*chunk;
	t_page	*p;

	if (!ptr)
		return ;
	p = fetch_first_page(NULL, 0);
	if ((chunk = search_ptr(ptr, &p)))
	{
		chunk->free = 1;
		combine_free_chunks(chunk);
	}
	else
		return ;
	if (p->beg->free && !p->beg->next)
		del_page(p);
}
