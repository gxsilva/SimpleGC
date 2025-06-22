/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clear_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 01:01:46 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/22 01:16:25 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	gc_clear_node_chain(t_gc_group *gc_group)
{
	t_gc_node	*node;
	t_gc_node	*tmp_node;

	if (!gc_group || !gc_group->gc_head_node)
	{
		if (DEBUG_FLAG)
			printf("GC: No nodes to clear in the group\n");
		return;
	}
	node = gc_group->gc_head_node;
	while (node)
	{
		tmp_node = node->prev;
		if (DEBUG_FLAG)
			printf("GC: [Free] node with tag '%s' and size %lu\n", node->tag, node->size);
		if (node->ptr)
			free(node->ptr);
		if (node->tag)
			free(node->tag);
		free(node);
		node = tmp_node;
	}
}