/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:26:17 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 22:50:08 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	gc_status(void)
{
	t_gc_group	*gc_group_tmp;
	t_gc_node	*gc_node_tmp;
	t_gc_state	*gc_state;

	gc_state = gc_get_h();
	if (!gc_state)
	{
		printf("GC was not initialized\n");
		return;
	}
	gc_group_tmp = gc_state->gc_head_group;
	printf("\t-----------\t\n");
	printf("Number of groups:\t%u\n", gc_state->group_cnt);
	printf("Number of nodes:\t%u\n", gc_state->node_cnt);
	printf("Total memory allocated:\t%luB\n", gc_state->memory_allocated);

	while (gc_group_tmp)
	{
		printf("\t-----------\t\n");
		printf("Group tag:\t%s\n", gc_group_tmp->tag);
		printf("Number of nodes in group:\t%u\n", gc_group_tmp->group_node_cnt);

		gc_node_tmp = gc_group_tmp->gc_head_node;
		while (gc_node_tmp)
		{
			printf("\t\t-----------\t\t\n");
			printf("Pointer address:\t%p\n", gc_node_tmp->ptr);
			printf("Size of block memory:\t%lu\n", gc_node_tmp->size);
			printf("Tag of block memory:\t%s\n", gc_node_tmp->tag);
			gc_node_tmp = gc_node_tmp->next;
		}
		gc_group_tmp = gc_group_tmp->gc_next;
	}
	return;
}
