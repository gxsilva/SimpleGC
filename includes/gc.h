/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:29:26 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/20 16:58:35 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

#include "gc_structs.h"

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>

//common function(s)
int			gc_strcmp(const char *s1, const char *s2);
//GC function(s)
t_gc_state	*gc_get_h(void);
int			gc_init(void);
void		*gc_malloc(unsigned long size, const char *tag);
int			gc_clear(void);
//Debug function(s)
void		gc_status(void);

#endif //GC_H