/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 06:38:47 by agouby            #+#    #+#             */
/*   Updated: 2019/02/17 20:20:08 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_hex(size_t n)
{
	char	*base;
	size_t	i;
	size_t	tmp;
	char	buf[32];

	base = "0123456789ABCDEF";
	tmp = n;
	i = 3;
	while ((tmp >>= 4))
		i++;
	buf[i] = 0;
	while (i--)
	{
		buf[i] = base[(n % 16)];
		n >>= 4;
	}
	buf[0] = '0';
	buf[1] = 'x';
	ft_putstr(buf);
}

void	print_dec(size_t n)
{
	size_t	i;
	size_t	tmp;
	char	buf[32];

	i = 1;
	tmp = n;
	while ((tmp /= 10))
		i++;
	buf[i] = 0;
	while (i--)
	{
		buf[i] = n % 10 + 48;
		n /= 10;
	}
	ft_putstr(buf);
}

void	print_page_allocs(t_chunk *beg, size_t *size)
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
		}
		else
		{
			print_hex((size_t)beg->ptr);
			ft_putstr(" - ");
			print_hex((size_t)((void *)beg->ptr + beg->size));
			ft_putstr(" : ");
			print_dec(beg->size);
			ft_putstr(" octets ");
			ft_putstr("FREE");
		}
		beg = beg->next;
		ft_putstr("\n");
	}
}

void	print_allocs(t_page *cur_page, size_t *size)
{
	if (cur_page->format == TINY)
		ft_putstr("TINY : ");
	else if (cur_page->format == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	print_hex((size_t)cur_page);
	ft_putstr("\n");
	print_page_allocs(cur_page->beg, size);
}

void	show_alloc_mem(void)
{
	t_page	*cur_page;
	size_t	size;

	pthread_mutex_lock(&g_mutex);
	ft_putstr("\n");
	size = 0;
	if (!(cur_page = fetch_first_page(NULL, 0)))
	{
		ft_putstr("No allocation found.\n");
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	while (cur_page)
	{
		print_allocs(cur_page, &size);
		cur_page = cur_page->next;
	}
	ft_putstr("Total : ");
	print_dec(size);
	ft_putstr(" octets\n");
	ft_putstr("\n");
	pthread_mutex_unlock(&g_mutex);
}
