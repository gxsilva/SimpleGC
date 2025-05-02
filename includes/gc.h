/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:29:26 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/01 23:20:12 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

#include "gc_structs.h"

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <stddef.h>

//Libft function(s)
int		gc_strcmp(const char *s1, const char *s2);

//GC function(s)
t_gc_state	*gc_get_h(void);
void	gc_init(void);
void	*gc_malloc(unsigned long size, const char *tag);
bool	gc_collect(void);

//Debug function(s)
void	gc_print_list(void);



#endif