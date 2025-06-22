/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:40:05 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/22 01:18:28 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

int		gc_init(void);
void	*gc_malloc(unsigned long size, const char *tag);
int		gc_clear(void);

int	gc_init(void)
{
	t_gc_state	*gc;
	static int	initialized = 0;

	if (!initialized)
	{
		if (DEBUG_FLAG)
			printf ("GC: [initialize] 'gc_init'\n");
		gc = gc_get_h();
		gc->gc_head_group = NULL;
		gc->group_cnt = 1; //standard __void = 1
		gc->node_cnt = 0;
		gc->memory_allocated = 0;
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
			perror ("GC: Was not initialize\n");
		return (NULL);
	}
	d_tag = tag;
	gc_ptr = NULL;
	if (size == 0)
	{
		if (DEBUG_FLAG)
			printf("GC: Cannot allocate a ptr with size of 0\n");
		return (NULL);
	}
	if (!tag || gc_strcmp(tag, "") == 0)
		d_tag = "__void";
	gc_ptr = (void *)malloc(size);
	if (!gc_ptr)
	{
		if (DEBUG_FLAG)
			perror ("GC: Was not able to malloc {return:NULL}\n");
		return (NULL);
	}
	if (!gc_track_ptr(gc_ptr, size, d_tag))
		return (free (gc_ptr), NULL);
	return (gc_ptr);
}

int	gc_clear(void)
{
	t_gc_state	*gc_state;
	t_gc_group	*gc_group;
	t_gc_group	*tmp_group;

	gc_state = gc_get_h();
	if (!gc_state)
	{
		if (DEBUG_FLAG)
			perror("GC: Invalid operation\n");
		return (0);
	}
	gc_group = gc_state->gc_head_group;
	while (gc_group)
	{
		tmp_group = gc_group->gc_next;
		gc_clear_node_chain(gc_group);
		if (DEBUG_FLAG)
			printf("GC: [Free] group with tag '%s' and %d nodes\n", gc_group->tag, gc_group->group_node_cnt);
		if (gc_group->tag)
			free (gc_group->tag);
		free(gc_group);
		gc_group = tmp_group;
	}
	gc_state->gc_head_group = NULL;
	gc_state->group_cnt = 0;
	gc_state->node_cnt = 0;
	gc_state->memory_allocated = 0;
	return (1);
}
