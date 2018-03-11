/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:15:52 by agouby            #+#    #+#             */
/*   Updated: 2018/03/11 19:25:09 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		get_format(size_t size)
{
	if (size <= TINY_LIMIT)
		return (TINY);
	if (size <= SMALL_LIMIT)
		return (SMALL);
	return (LARGE);
}

void	*valloc(size_t size)
{
	void	*ptr;
	int		format;

	size = align_page(LARGE, size);
	format = get_format(size);
	if (!page || format == LARGE)
		return (create_page(format, size));
	ptr = search_free_chunk(format, size);
	return (ptr);
}

void	*calloc(size_t count, size_t size)
{
	size_t	full_size;
	void	*new_alloc;

	full_size = count * size;
	new_alloc = malloc(full_size);
	if (full_size)
		ft_bzero(new_alloc, full_size);
	return (new_alloc);
}

void	*malloc(size_t size)
{
	void	*ptr;
	int		format;

	size = align_16(size);
	format = get_format(size);
	if (!page || format == LARGE)
		return (create_page(format, size));
	ptr = search_free_chunk(format, size);
	return (ptr);
}
