/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_block_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:44:02 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 18:55:40 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	gc_block(t_gc_block *block, void *ptr, long size, const char *tag)
{
	block->next = gc_get_h()->allocations;
	block->ptr = ptr;
	block->size = size;
	block->tag = (char *)tag;
}

void	update_gc_state(t_gc_state	*gc_state, t_gc_block	*block_ptr)
{
	gc_state->allocations = block_ptr;
	gc_state->num_allocations++;
	gc_state->total_size += block_ptr->size;
}

int	gc_track_ptr(void *ptr, unsigned long size, const char *tag)
{
	t_gc_block	*block_ptr;
	t_gc_state	*gc_state;

	gc_state = gc_get_h();
	block_ptr = (t_gc_block *)malloc(sizeof(t_gc_block));
	if (!block_ptr)
	{
		if (DEBUG_FLAG)
			perror("GC: Malloc t_gc_block failed\n");
		return (0);
	}
	gc_block(block_ptr, ptr, size, tag);
	update_gc_state(gc_state, block_ptr);
	return (1);
}
