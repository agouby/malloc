/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dump_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:05:26 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 21:06:30 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int		ft_isprintable(unsigned char c)
{
	return (c >= ' ' && c <= '~');
}

void	print_bytes_ascii(const char *ptr)
{
	int i;

	i = 0;
	ft_putstr(" |");
	while (i < 16)
	{
		if (ft_isprintable(*ptr))
			ft_putchar(*ptr);
		else
			ft_putchar('.');
		ptr++;
		if (i == 15)
			ft_putchar('|');
		i++;
	}
}

void	print_bytes_hex(const char *ptr)
{
	int i;

	i = 0;
	while (i < 16)
	{
		print_hex_char(((unsigned char *)ptr)[i]);
		ft_putchar(' ');
		if (i == 7)
			ft_putchar(' ');
		i++;
	}
	print_bytes_ascii(ptr);
}

int		is_filled_zeros(void *ptr, size_t size)
{
	if (size >= 16 && *(size_t *)ptr == 0 && *((size_t *)(ptr + 8)) == 0)
		return (1);
	return (0);
}

void	skip_zeros(void **ptr, size_t *size)
{
	ft_putstr("\n*");
	while (*size && is_filled_zeros(*ptr, *size))
	{
		*ptr += 16;
		*size -= 16;
	}
}
