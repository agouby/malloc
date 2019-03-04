/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 06:38:47 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 21:10:50 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_page_allocs(t_chunk *beg, size_t *size)
{
	while (beg)
	{
		if (beg->free == 0)
		{
			print_hex((size_t)beg->ptr);
			ft_putstr(" - ");
			print_hex((size_t)((void *)beg->ptr + beg->size));
			ft_putstr(" : ");
			print_dec(beg->size);
			ft_putstr(" octets");
			*size += beg->size;
			ft_putstr("\n");
		}
		beg = beg->next;
	}
}

static void	print_page(t_page *page, int format, const char *s, size_t *size)
{
	ft_putstr(s);
	ft_putstr(" : ");
	while (page && page->format != format)
		page = page->next;
	print_hex((size_t)page);
	ft_putstr("\n");
	if (!page)
		return ;
	while (page)
	{
		if (page->format == format)
			print_page_allocs(page->beg, size);
		page = page->next;
	}
}

void		show_alloc_mem(void)
{
	t_page	*cur_page;
	size_t	size;

	pthread_mutex_lock(&g_mutex);
	size = 0;
	if (!(cur_page = fetch_first_page(NULL, 0)))
	{
		ft_putstr("No allocation found.\n");
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	print_page(cur_page, TINY, "TINY", &size);
	print_page(cur_page, SMALL, "SMALL", &size);
	print_page(cur_page, LARGE, "LARGE", &size);
	ft_putstr("Total : ");
	print_dec(size);
	ft_putstr(" octets\n");
	pthread_mutex_unlock(&g_mutex);
}
