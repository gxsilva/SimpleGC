/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:29:58 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 22:48:09 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_STRUCTS_H
# define GC_STRUCTS_H

# include "gc.h"

struct gc_node_track;
struct gc_table;
struct gc_state;

typedef struct gc_node_track
{
	void			*ptr;
	unsigned long	size;
	char			*tag;
	struct gc_node_track		*next;
	struct gc_node_track		*prev;
	struct gc_table		*table_h;
}	t_gc_node;

typedef struct gc_table
{
	char			*tag;
	struct gc_node_track	*gc_head_node;
	unsigned int	group_node_cnt;
	struct gc_table		*gc_next;
	struct gc_table		*gc_prev;
}	t_gc_group;

typedef struct gc_state
{
	t_gc_group		*gc_head_group;
	unsigned int	group_cnt;
	unsigned int	node_cnt;
	unsigned long	memory_allocated;
}	t_gc_state;

#endif