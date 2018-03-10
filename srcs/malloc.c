/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:15:52 by agouby            #+#    #+#             */
/*   Updated: 2018/03/10 17:14:06 by agouby           ###   ########.fr       */
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
