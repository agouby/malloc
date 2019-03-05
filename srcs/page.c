/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:25:18 by agouby            #+#    #+#             */
/*   Updated: 2019/03/05 15:31:10 by agouby           ###   ########.fr       */
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
		g_page = p->next;
		fetch_first_page(g_page, 1);
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
	if (!g_page)
		return ;
	while (g_page->next)
		g_page = g_page->next;
	*prev = g_page;
	g_page = g_page->next;
}

void	init_page(int format, size_t size, t_page *prev)
{
	g_page->format = format;
	g_page->size = size;
	g_page->beg = (t_chunk *)((void *)g_page + page_ssize());
	g_page->prev = prev;
	if (prev)
		prev->next = g_page;
	g_page->next = NULL;
}

void	*create_page(int format, size_t p_size)
{
	size_t	sz;
	size_t	new_chunk_size;
	t_page	*prev;

	sz = align_page(format, p_size + page_ssize() + chunk_ssize());
	g_page = fetch_first_page(NULL, 0);
	prev = NULL;
	goto_last_page(&prev);
	g_page = mmap(0, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!g_page)
		return (NULL);
	init_page(format, sz, prev);
	if (!prev)
		fetch_first_page(g_page, 0);
	set_chunk(g_page->beg, p_size, 0);
	connect_chunk(g_page->beg, NULL, NULL);
	new_chunk_size = g_page->size - (page_ssize() + chunk_ssize() * 2 + p_size);
	if (format != LARGE)
		split_chunk(g_page->beg, new_chunk_size);
	return (g_page->beg->ptr);
}
