/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:40:05 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 18:57:27 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

t_gc_state	*gc_get_h(void)
{
	static t_gc_state	gc;

	return (&gc);
}

int	gc_init(void)
{
	t_gc_state	*gc;
	static int	initialized = 0;

	if (!initialized)
	{
		gc = gc_get_h();
		gc->allocations = NULL;
		gc->total_size = 0;
		gc->num_allocations = 0;
		initialized = 1;
		return (0);
	}
	return (initialized);
}

void	*gc_malloc(unsigned long size, const char *tag)
{
	const char	*d_tag;
	void		*gc_ptr;

	if (!gc_init() || !gc_get_h())
	{
		if (DEBUG_FLAG)
			perror ("GC: GC was not initialize\n");
		return (NULL);
	}
	d_tag = tag;
	gc_ptr = NULL;
	if (size == 0)
		return (NULL);
	if (!tag || gc_strcmp(tag, "") == 0)
		d_tag = "__void";
	gc_ptr = (void *)malloc(size);
	if (!gc_ptr)
	{
		if (DEBUG_FLAG)
			perror ("GC: GC was not able to malloc {return:NULL}\n");
		return (NULL);
	}
	if (!gc_track_ptr(gc_ptr, size, d_tag))
		return (free (gc_ptr), NULL);
	return (gc_ptr);
}

int	gc_clear(void)
{
	t_gc_state	*gc_state;
	t_gc_block	*gc_block;
	t_gc_block	*gc_tmp_block;

	gc_state = gc_get_h();
	if (!gc_state)
	{
		if (DEBUG_FLAG)
			perror("GC: Invalid operation\n");
		return (0);
	}
	gc_block = gc_state->allocations;
	while (gc_block)
	{
		gc_tmp_block = gc_block->next;
		if (gc_block->ptr)
			free(gc_block->ptr);
		free(gc_block);
		gc_block = gc_tmp_block;
	}
	gc_state->allocations = NULL;
	gc_state->total_size = 0;
	gc_state->num_allocations = 0;
	return (1);
}
