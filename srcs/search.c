/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:49:37 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 19:14:09 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk	*search_ptr_in_page(t_page *p, void *ptr)
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

static t_chunk	*search_free_chunk_in_page(t_page *p, size_t size)
{
	t_chunk *search;

	search = p->beg;
	while (search && (!search->free || search->size < size))
		search = search->next;
	return (search);
}

t_chunk			*search_ptr(void *ptr, t_page **p)
{
	t_chunk	*search;

	search = NULL;
	while (*p)
	{
		if (ptr > (void *)*p && (ptr < ((void *)*p + (*p)->size)))
		{
			search = search_ptr_in_page(*p, ptr);
			break ;
		}
		*p = (*p)->next;
	}
	return (search);
}

void			*search_free_chunk(int format, size_t size)
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
		if (old_size - search->size > chunk_ssize())
			split_chunk(search, old_size - search->size - chunk_ssize());
		return (search->ptr);
	}
	else
		return (create_page(format, size));
}
