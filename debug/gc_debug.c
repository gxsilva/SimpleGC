/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:26:17 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/20 16:08:03 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	gc_status(void)
{
	t_gc_block *gc_block_tmp;
	t_gc_state *gc_state;
	
	gc_state = gc_get_h();
	if (!gc_state)
	{
		printf ("gc was not initialize\n");
		return ;
	}
	gc_block_tmp = gc_state->allocations;
	printf("\t-----------\t\n");
	printf ("Number of allocations:\t%ld\n", gc_state->num_allocations);
	printf ("Size of allocations:\t%ldB\n", gc_state->total_size);
	while (gc_block_tmp)
	{
		printf("\t-----------\t\n");
		printf ("Pointer addrres:\t%p\n",gc_block_tmp->ptr);
		printf ("Size of block memory:\t%ld\n",gc_block_tmp->size);
		printf ("Tag of block memory:\t%s\n", gc_block_tmp->tag);
		gc_block_tmp = gc_block_tmp->next;
	}
	return ;
}	