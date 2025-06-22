/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_node_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:44:02 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/22 01:21:54 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	gc_node_track(t_gc_node *block, void *ptr, long size, const char *tag)
{
	t_gc_group	*head_group;

	head_group = gc_search_group(tag);
	if (DEBUG_FLAG)
		printf ("GC: [Malloc] \033[1;33m%ldB\033[0m with tag \033[1;33m'%s'\033[0m in group \033[1;33m'%s'\033[0m\n", size, tag, head_group->tag);
	if (head_group->gc_head_node != NULL)
		head_group->gc_head_node->next = block;
	block->prev = head_group->gc_head_node;
	block->next = NULL;
	block->ptr = ptr;
	block->size = size;
	block->tag = gc_strdup(tag);
	block->table_h = head_group;
	head_group->gc_head_node = block;
	head_group->group_node_cnt++;
}

void	update_gc_state(t_gc_state	*gc_state, t_gc_node	*block_ptr)
{
	gc_state->node_cnt += 1;
	gc_state->memory_allocated += block_ptr->size;
}

int	gc_track_ptr(void *ptr, unsigned long size, const char *tag)
{
	t_gc_node	*node_ptr;
	t_gc_state	*gc_state;

	gc_state = gc_get_h();
	node_ptr = (t_gc_node *)malloc(sizeof(t_gc_node));
	if (!node_ptr)
	{
		if (DEBUG_FLAG)
			perror("GC: Malloc t_gc_node failed\n");
		return (0);
	}
	gc_node_track(node_ptr, ptr, size, tag);
	update_gc_state(gc_state, node_ptr);
	return (1);
}
