/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:29:58 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/01 23:08:31 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_STRUCTS_H
# define GC_STRUCTS_H

# include "gc.h"

/**
 * @struct gc_block
 * @brief Represents a block of memory managed by the garbage collector.
 *
 * This structure is used to track individual memory allocations, their sizes,
 * and additional metadata required for garbage collection.
 *
 * @var gc_block::ptr
 * Pointer to the actual allocated memory.
 *
 * @var gc_block::size
 * Size of the allocated memory in bytes.
 *
 * @var gc_block::tag
 * Optional tag for grouping or identifying allocations. Can be NULL.
 *
 * @var gc_block::next
 * Pointer to the next gc_block in the linked list.
 *
 * @var gc_block::marked
 * Boolean flag used in mark-and-sweep garbage collection to indicate
 * whether this block has been marked as reachable.
 */
typedef struct gc_block
{
	void				*ptr;
	unsigned long		size;
	char				*tag;
	struct gc_block		*next;
}	t_gc_block;

/**
 * @struct t_gc_state
 * @brief Represents the state of the garbage collector.
 *
 * This structure is used to track the memory allocations managed by the
 * garbage collector. It maintains a linked list of all active allocations,
 * the total size of allocated memory, and the number of active allocations.
 *
 * @var t_gc_state::allocations
 * A pointer to the head of a linked list containing all
 * active memory allocations.
 *
 * @var t_gc_state::total_size
 * The total size of memory currently allocated, in bytes.
 *
 * @var t_gc_state::num_allocations
 * The number of active memory allocations being tracked.
 */
typedef struct gc_state
{
	t_gc_block		*allocations;
	unsigned long	total_size;
	unsigned long	num_allocations;
}	t_gc_state;

#endif