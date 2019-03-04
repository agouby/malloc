/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 18:10:07 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 19:58:05 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		attach_next(t_chunk *chunk)
{
	chunk->size = chunk->size + chunk->next->size + chunk_ssize();
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
	{
		attach_next(chunk);
	}
}

void		free(void *ptr)
{
	t_chunk	*chunk;
	t_page	*p;

	pthread_mutex_lock(&g_mutex);
	if (!ptr)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	p = fetch_first_page(NULL, 0);
	if ((chunk = search_ptr(ptr, &p)))
	{
		chunk->free = 1;
		combine_free_chunks(chunk);
	}
	else
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (p->beg->free && !p->beg->next)
		del_page(p);
	pthread_mutex_unlock(&g_mutex);
}
