/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_block_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:44:02 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/22 00:33:37 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	gc_group_kickoff (t_gc_group *head_group)
{
	head_group->tag = gc_strdup("__void");
	head_group->gc_head_node = NULL;
	head_group->group_node_cnt = 0;
	head_group->gc_next = NULL;
	head_group->gc_prev = NULL;
}

int	gc_group_init (t_gc_state *gc)
{
	if (gc->gc_head_group == NULL)
	{
		gc->gc_head_group = (t_gc_group *)malloc(sizeof(t_gc_group));
		if (!gc->gc_head_group)
		{
			if (DEBUG_FLAG)
				perror ("GC: GC was unable to initialize head groups\n");
			return (1);
		}
		gc_group_kickoff(gc->gc_head_group);
		if (DEBUG_FLAG)
			printf ("GC: GC __void table initialize\n");
		return (0);
	}
	return (1);
}

t_gc_group	*gc_creation_group(t_gc_group *last_group, const char *tag)
{
	t_gc_group	*new_group;

	new_group = (t_gc_group *)malloc(sizeof(t_gc_group));
	if (!new_group)
	{
		if (DEBUG_FLAG)
			perror("GC: Failed to create a new group\n");
		return (NULL);
	}
	new_group->gc_head_node = NULL;
	new_group->gc_next = NULL;
	new_group->gc_prev = last_group;
	new_group->group_node_cnt = 0;
	new_group->tag = gc_strdup(tag); // !MAKE MY OWN BEFORE
	if (!new_group->tag)
	{
		if (DEBUG_FLAG)
			perror("GC: Failed to allocate memory for group tag\n");
		free(new_group);
		return (NULL);
	}
	if (last_group)
		last_group->gc_next = new_group;
	gc_get_h()->group_cnt++;
	return (new_group);
}

t_gc_group	*gc_search_group(const char *tag)
{
	t_gc_group	*group_ptr;

	gc_group_init(gc_get_h());
	group_ptr = gc_get_h()->gc_head_group;
	if (gc_strcmp(tag, "__void") == 0)
		return (group_ptr);
	if (group_ptr->gc_next != NULL)
		group_ptr = group_ptr->gc_next;
	while (group_ptr)
	{
		if(gc_strcmp(group_ptr->tag, tag) == 0)
			return (group_ptr);
		if (group_ptr->gc_next == NULL)
			break;
		group_ptr = group_ptr->gc_next;
	}
	if (DEBUG_FLAG)
		printf ("GC: GC Create a new group %s\n", tag);
	return (gc_creation_group(group_ptr, tag));
}

void	gc_node_track(t_gc_node *block, void *ptr, long size, const char *tag)
{
	t_gc_group	*head_group;

	head_group = gc_search_group(tag);
	if (DEBUG_FLAG)
		printf ("GC: GC Malloc %ldB with tag '%s' in group '%s'\n", size, tag, head_group->tag);
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
