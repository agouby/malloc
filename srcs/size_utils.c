/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 18:26:19 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 19:13:35 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t	chunk_ssize(void)
{
	return (align_16(sizeof(t_chunk)));
}

size_t	page_ssize(void)
{
	return (align_16(sizeof(t_page)));
}
