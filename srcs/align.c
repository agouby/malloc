/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 23:06:49 by agouby            #+#    #+#             */
/*   Updated: 2018/03/11 21:24:20 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		log_page(size_t n)
{
	int	cnt;

	cnt = 0x0;
	while (n > 0x8)
	{
		n >>= 0x4;
		cnt += 0x4;
	}
	while (n != 0x1)
	{
		n >>= 0x1;
		cnt++;
	}
	return (cnt);
}

size_t			align_page(const int format, const size_t size)
{
	int     log;
	size_t  page_size;

	if (format == TINY)
		page_size = TINY_FAC * getpagesize();
	else if (format == SMALL)
		page_size = SMALL_FAC * getpagesize();
	else
		page_size = getpagesize();
	log = log_page(page_size);
	return ((((size - 0x1) >> log) << log) + page_size);
}

size_t			align_16(const size_t size)
{
	if (!size)
		return (16);
	return ((((size - 0x1) >> 0x4) << 0x4) + 0x10);
}
