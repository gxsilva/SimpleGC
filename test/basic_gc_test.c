/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_gc_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:54:45 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 17:56:49 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "../includes/gc.h"

//Basic teste with primitive types in C

Test (gc_malloc_test, char_malloc)
{
	char	*word;

	gc_init();
	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, int_malloc)
{
	int	*number;

	gc_init();
	number = gc_malloc(sizeof(int) * 1024, NULL);
	cr_expect(number, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, float_malloc)
{
	float	*values;

	gc_init();
	values = gc_malloc(sizeof(float) * 100, NULL);
	cr_expect(values, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, double_malloc)
{
	double	*values;

	gc_init();
	values = gc_malloc(sizeof(double) * 50, NULL);
	cr_expect(values, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, long_malloc)
{
	long	*values;

	gc_init();
	values = gc_malloc(sizeof(long) * 20, NULL);
	cr_expect(values, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, short_malloc)
{
	short	*values;

	gc_init();
	values = gc_malloc(sizeof(short) * 10, NULL);
	cr_expect(values, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, unsigned_int_malloc)
{
	unsigned int	*values;

	gc_init();
	values = gc_malloc(sizeof(unsigned int) * 30, NULL);
	cr_expect(values, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, unsigned_char_malloc)
{
	unsigned char	*values;

	gc_init();
	values = gc_malloc(sizeof(unsigned char) * 15, NULL);
	cr_expect(values, "gc_malloc failed");
	gc_clear();
}

Test (gc_malloc_test, unsigned_long_malloc)
{
	unsigned long	*values;

	gc_init();
	values = gc_malloc(sizeof(unsigned long) * 25, NULL);
	cr_expect(values, "gc_malloc failed");
	gc_clear();
}
