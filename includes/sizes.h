/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:38:22 by agouby            #+#    #+#             */
/*   Updated: 2018/03/05 00:12:24 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIZES_H
# define SIZES_H

enum {
	TINY,
	SMALL,
	LARGE
};

# define TINY_FAC		0x2
# define SMALL_FAC		0x8

# define TINY_LIMIT		0x80
# define SMALL_LIMIT	0x400

#endif
