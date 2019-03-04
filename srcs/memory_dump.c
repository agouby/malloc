/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:09:27 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 21:10:23 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	dump_chunk(t_chunk *chunk)
{
	size_t	size;
	void	*ptr;

	ptr = chunk->ptr;
	size = chunk->size;
	ft_putstr("||| BLOCK ||| ");
	print_dec(size);
	ft_putstr(" octets |||");
	while (size)
	{
		ft_putchar('\n');
		print_hex((size_t)ptr);
		ft_putstr("  ");
		print_bytes_hex((const char *)ptr);
		size -= 16;
		ptr += 16;
		if (is_filled_zeros(ptr - 16, 16) && is_filled_zeros(ptr, size))
			skip_zeros(&ptr, &size);
	}
}

void		do_memory_dump(t_page *cur_page, t_chunk *cur_chunk)
{
	while (cur_page)
	{
		cur_chunk = cur_page->beg;
		ft_putstr("::: PAGE ::: ");
		if (cur_page->format == TINY)
			ft_putstr("TINY ::: ");
		else if (cur_page->format == SMALL)
			ft_putstr("SMALL ::: ");
		else
			ft_putstr("LARGE ::: ");
		print_hex((size_t)cur_page);
		ft_putchar('\n');
		while (cur_chunk)
		{
			if (!cur_chunk->free)
			{
				ft_putchar('\n');
				dump_chunk(cur_chunk);
				ft_putchar('\n');
			}
			cur_chunk = cur_chunk->next;
		}
		cur_page = cur_page->next;
	}
}

void		memory_dump(void)
{
	t_page	*cur_page;
	t_chunk *cur_chunk;

	cur_chunk = NULL;
	pthread_mutex_lock(&g_mutex);
	if (!(cur_page = fetch_first_page(NULL, 0)))
	{
		ft_putstr("No allocation found.\n");
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	do_memory_dump(cur_page, cur_chunk);
	ft_putstr("\nEnd of allocations.\n");
	pthread_mutex_unlock(&g_mutex);
}
