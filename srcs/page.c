/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:25:18 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 21:02:36 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page	*fetch_first_page(t_page *new_first, int force)
{
	static t_page	*g_first = NULL;

	if (new_first || force)
	{
		g_first = new_first;
		if (g_first)
			g_first->prev = NULL;
	}
	return (g_first);
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
	page->beg = (t_chunk *)((void *)page + page_ssize());
	page->prev = prev;
	if (prev)
		prev->next = page;
	page->next = NULL;
}

void	*create_page(int format, size_t p_size)
{
	size_t	size;
	size_t	new_chunk_size;
	t_page	*prev;

	size = align_page(format, p_size + page_ssize() + chunk_ssize());
	page = fetch_first_page(NULL, 0);
	prev = NULL;
	goto_last_page(&prev);
	page = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!page)
		return (NULL);
	init_page(format, size, prev);
	if (!prev)
		fetch_first_page(page, 0);
	set_chunk(page->beg, p_size, 0);
	connect_chunk(page->beg, NULL, NULL);
	new_chunk_size = page->size - (page_ssize() + chunk_ssize() * 2 + p_size);
	if (format != LARGE)
		split_chunk(page->beg, new_chunk_size);
	return (page->beg->ptr);
}
