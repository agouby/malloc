/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 18:10:07 by agouby            #+#    #+#             */
/*   Updated: 2018/03/10 17:17:37 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk	*search_ptr_in_page(t_page *p, void *ptr)
{
	t_chunk	*chunk;

	chunk = p->beg;
	while (chunk)
	{
		if (chunk->ptr == ptr && !chunk->free)
			return (chunk);
		chunk = chunk->next;
	}
	return (NULL);
}

t_chunk	*search_ptr(void *ptr, t_page **p)
{
	t_chunk	*search;

	search = NULL;
	while (*p)
	{
		if ((search = search_ptr_in_page(*p, ptr)))
			break ;
		*p = (*p)->next;
	}
	return (search);
}

void	attach_next(t_chunk *chunk)
{
	chunk->size = chunk->size + chunk->next->size + CHUNK_SSIZE;
	chunk->next = chunk->next->next;
	if (chunk->next)
		chunk->next->prev = chunk;
}

void	combine_free_chunks(t_chunk *chunk)
{
	if (chunk->prev && chunk->prev->free)
	{
		chunk = chunk->prev;
		attach_next(chunk);
	}
	if (chunk->next && chunk->next->free)
		attach_next(chunk);
}

void	free(void *ptr)
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
