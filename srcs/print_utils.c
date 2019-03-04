/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:09:45 by agouby            #+#    #+#             */
/*   Updated: 2019/03/04 21:16:05 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	print_hex_char(unsigned char n)
{
	char			*base;
	char			buf[3];

	base = "0123456789abcdef";
	buf[2] = 0;
	buf[1] = base[n % 16];
	buf[0] = base[(n >> 4) % 16];
	ft_putstr(buf);
}

void	ft_putchar(unsigned char c)
{
	write(1, &c, 1);
}

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
