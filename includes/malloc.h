/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouby <agouby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:36:43 by agouby            #+#    #+#             */
/*   Updated: 2018/03/10 16:55:08 by agouby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include "sizes.h"

# include <stdio.h>

# define U(X) (void)(X)

# define PROTS	PROT_READ | PROT_WRITE
# define FLAGS	MAP_PRIVATE | MAP_ANON

# define CHUNK_SSIZE (align_16(sizeof(t_chunk)))
# define PAGE_SSIZE (align_16(sizeof(t_page)))

typedef struct	s_chunk
{
	int				free;
	size_t			size;
	void			*ptr;
	struct s_chunk	*prev;
	struct s_chunk	*next;
}				t_chunk;

typedef struct	s_page
{
	int				format;
	size_t			size;
	t_chunk			*beg;
	struct s_page	*prev;
	struct s_page	*next;
}				t_page;

struct s_page	*page;

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);

size_t			align_page(int format, size_t size);
size_t			align_16(size_t size);

void			*create_page(int format, size_t size);
t_page			*fetch_first_page(t_page *new_first, int force);
void			del_page(t_page *p);

void			set_chunk(t_chunk *chunk, size_t size, int free);
void			connect_chunk(t_chunk *chunk, t_chunk *prev, t_chunk *next);
void			split_chunk(t_chunk *chunk, size_t size);
void			*search_free_chunk(int format, size_t size);

t_chunk			*search_ptr(void *ptr, t_page **page);

void     		show_alloc_mem(void);
void			print_hex(size_t size);
void			print_dec(size_t size);
void			ft_putstr(const char *str);

void			free_all(void);

#endif
