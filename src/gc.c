/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:40:05 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/01 23:27:57 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

t_gc_state	*gc_get_h(void)
{
	static t_gc_state	gc;
	
	return (&gc);
}

void	gc_init(void)
{
	t_gc_state	*gc;

	gc = gc_get_h();
	gc->allocations = NULL;
	gc->total_size = 0;
	gc->num_allocations = 0;
	printf ("GC: GC initialize\n");
}

static void	init_t_gc_block(t_gc_block *block, void *ptr, unsigned long size, const char *tag)
{
	block->next = gc_get_h()->allocations;
	block->ptr = ptr;
	block->size = size;
	block->tag = (char *)tag;
}

static	void	update_gc_state(t_gc_state	*gc_state, t_gc_block	*block_ptr)
{
	gc_state->allocations = block_ptr;
	gc_state->num_allocations++;
	gc_state->total_size += block_ptr->size;
}

static bool	gc_track_ptr(void *ptr, unsigned long size, const char *tag)
{
	t_gc_block	*block_ptr;
	t_gc_state	*gc_state;

	gc_state = gc_get_h();
	block_ptr = (t_gc_block *)malloc(sizeof(t_gc_block));
	if (!block_ptr)
		return (perror("GC: Malloc t_gc_block error\n"), false);
	init_t_gc_block(block_ptr, ptr, size, tag);
	update_gc_state(gc_state, block_ptr);
	return (true);
}

void	*gc_malloc(unsigned long size, const char *tag)
{
	const char	*d_tag;
	void		*gc_ptr;
	
	if (!gc_get_h())
		return (perror ("GC: GC was not initialize\n"), NULL);
	d_tag = tag;
	gc_ptr = NULL;
	if (size == 0)
		return (NULL);
	if (!tag || gc_strcmp(tag, "") == 0)
		d_tag = "__void";
	gc_ptr = (void *)malloc(size);
	if (!gc_ptr)
		return (NULL);
	if(!gc_track_ptr(gc_ptr, size, d_tag))
		return (free (gc_ptr), NULL);
	return (gc_ptr);
}

bool	gc_collect(void)
{
	t_gc_state	*gc_state;
	t_gc_block	*gc_block;
	t_gc_block	*gc_tmp_block;
	
	gc_state = gc_get_h();
	if (!gc_state)
		return (perror("GC: Invalid operation\n"), false);
	gc_block = gc_state->allocations;
	gc_tmp_block = NULL;
	while (gc_block)
	{
		free (gc_block->ptr);
		gc_block->ptr = NULL;
		gc_tmp_block = gc_tmp_block;
		gc_block = gc_block->next;
	}
	printf ("GC: Clean memory\n");
	return (true);
}