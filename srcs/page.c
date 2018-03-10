/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:25:18 by agouby            #+#    #+#             */
/*   Updated: 2018/03/10 17:17:55 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page	*fetch_first_page(t_page *new_first, int force)
{
	static t_page	*first = NULL;

	if (new_first || force)
	{
		first = new_first;
		if (first)
			first->prev = NULL;
	}
	return (first);
}

void	del_page(t_page *p)
{
	if (!p->prev)
	{
		page = p->next;
		fetch_first_page(page, 1);
	}
	else if (!p->next)
		p->prev->next = NULL;
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	munmap(p, p->size);
}

void	goto_last_page(t_page **prev)
{
	if (!page)
		return ;
	while (page->next)
		page = page->next;
	*prev = page;
	page = page->next;
}

void	init_page(int format, size_t size, t_page *prev)
{
	page->format = format;
	page->size = size;
	page->beg = (t_chunk *)((void *)page + PAGE_SSIZE);
	page->prev = prev;
	if (prev)
		prev->next = page;
	page->next = NULL;
}

void	*create_page(int format, size_t size)
{
	size_t	page_size;
	size_t	new_chunk_size;
	t_page	*prev;

	page_size = align_page(format, size + PAGE_SSIZE + CHUNK_SSIZE);
	page = fetch_first_page(NULL, 0);
	prev = NULL;
	goto_last_page(&prev);
	if (!(page = mmap(0, page_size, PROTS, FLAGS, -1, 0)))
		return (NULL);
	init_page(format, page_size, prev);
	if (!prev)
		fetch_first_page(page, 0);
	set_chunk(page->beg, size, 0);
	connect_chunk(page->beg, NULL, NULL);
	new_chunk_size = page->size - (PAGE_SSIZE + CHUNK_SSIZE * 2 + size);
	if (format != LARGE)
		split_chunk(page->beg, new_chunk_size);
	return (page->beg->ptr);
}
