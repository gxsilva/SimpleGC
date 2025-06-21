/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_gc_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:02:17 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 18:17:49 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "../includes/gc.h"

typedef struct s_point {
	int x;
	int y;
} t_point;

Test(gc_malloc_test, struct_malloc_multiple)
{
	t_point *p1, *p2;

	gc_init();
	p1 = gc_malloc(sizeof(t_point), NULL);
	p2 = gc_malloc(sizeof(t_point), NULL);

	cr_expect(p1 != NULL && p2 != NULL, "gc_malloc failed to allocate structs");

	p1->x = 5;
	p1->y = 15;
	p2->x = 25;
	p2->y = 35;

	cr_expect(p1->x == 5 && p1->y == 15, "First struct values are incorrect");
	cr_expect(p2->x == 25 && p2->y == 35, "Second struct values are incorrect");

	gc_clear();
}

Test(gc_malloc_test, struct_malloc_null)
{
	t_point *p;

	gc_init();
	p = gc_malloc(0, NULL);

	cr_expect(p == NULL, "gc_malloc should return NULL for zero size allocation");

	gc_clear();
}

Test(gc_malloc_test, struct_malloc_free)
{
	t_point *p;

	gc_init();
	p = gc_malloc(sizeof(t_point), NULL);
	cr_expect(p != NULL, "gc_malloc failed to allocate struct");

	p->x = 50;
	p->y = 60;

	cr_expect(p->x == 50 && p->y == 60, "Struct values are incorrect");

	cr_expect(p, "gc_free failed to deallocate struct");

	gc_clear();
}