/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:29:26 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/22 01:11:08 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "gc_structs.h"
# include "gc_macros.h"

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>

//common function(s)
int			gc_strcmp(const char *s1, const char *s2);
char		*gc_strdup(const char *s);

//GC Main Functions(s)
t_gc_state	*gc_get_h(void);
int			gc_init(void);
void		*gc_malloc(unsigned long size, const char *tag);
int			gc_clear(void);

//GC block ptr handler
void		gc_node_track(t_gc_node *block, void *ptr, long size, const char *tag);
void		update_gc_state(t_gc_state	*gc_state, t_gc_node	*block_ptr);
int			gc_track_ptr(void *ptr, unsigned long size, const char *tag);

//GC Group handler functions
void		gc_group_kickoff (t_gc_group *head_group);
int			gc_group_init (t_gc_state *gc);
t_gc_group	*gc_creation_group(t_gc_group *last_group, const char *tag);
t_gc_group	*gc_search_group(const char *tag);

//GC Clear functions
void	gc_clear_node_chain(t_gc_group *gc_group);

//Debug function(s)
void		gc_status(void);

#endif //GC_H