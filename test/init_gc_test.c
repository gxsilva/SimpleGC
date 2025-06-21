/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gc_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:54:51 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 18:04:06 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "../includes/gc.h"

//valgrind --leak-check=full --suppressions=$(pkg-config --variable=supp_files criterion) ./tests

Test(gc_malloc_test, zero_size_malloc)
{
	void *ptr;

	gc_init();
	ptr = gc_malloc(0, NULL);
	cr_expect(ptr == NULL, "gc_malloc with size 0 must return NULL");
	gc_clear();
}

Test(gc_malloc_test, string_write_read)
{
	char *word;

	gc_init();
	word = gc_malloc(sizeof(char) * 6, NULL);
	cr_expect(word != NULL, "gc_malloc failed with string");

	strcpy(word, "hello");
	cr_expect_str_eq(word, "hello", "String mismatch");

	gc_clear();
}

Test(gc_malloc_test, multiple_allocs)
{
	int *arr1, *arr2;

	gc_init();
	arr1 = gc_malloc(sizeof(int) * 5, NULL);
	arr2 = gc_malloc(sizeof(int) * 10, NULL);

	cr_expect(arr1 != NULL, "gc_malloc failed in arr1");
	cr_expect(arr2 != NULL, "gc_malloc failed in arr2");

	arr1[0] = 42;
	arr2[0] = 84;

	cr_expect(arr1[0] == 42, "Unexpected value arr1");
	cr_expect(arr2[0] == 84, "Unexpected value arr2");

	gc_clear();
}

Test(gc_malloc_test, gc_clear_frees_memory)
{
	int *arr;

	gc_init();
	arr = gc_malloc(sizeof(int) * 5, NULL);
	cr_expect(arr != NULL, "gc_malloc failed");

	gc_clear();

	// Após gc_clear, arr é inválido, mas apenas testamos se gc_clear não crasha.
	cr_assert(true, "gc_clear failed"); 
}



Test(gc_malloc_test, large_allocation)
{
	void *ptr;

	gc_init();
	ptr = gc_malloc(1024 * 1024 * 10, NULL); // 10 MB

	cr_expect(ptr != NULL, "gc_malloc failed in to bigger allocation");

	gc_clear();
}

Test(gc_malloc_test, double_gc_init)
{
	gc_init();
	gc_init(); // Deve ser idempotente

	char *word = gc_malloc(sizeof(char) * 10, NULL);
	cr_expect(word != NULL, "gc_malloc failed in double gc_init call");

	gc_clear();
}

Test(gc_malloc_test, malloc_without_init)
{
	char *word;

	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word == NULL, "gc_malloc must failed without gc_init");
	// Não chamar gc_clear pois gc_init não foi chamado.
}

Test(gc_malloc_test, manual_free_if_supported)
{
	char *word;

	gc_init();
	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word != NULL, "gc_malloc failed");

	// Se manual free for suportado:
	// gc_free(word);
	// cr_assert(true, "gc_free causou falha");

	gc_clear();
}

Test(gc_malloc_test, reuse_after_clear)
{
	char *word;

	gc_init();
	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word != NULL, "First allocation failed");

	gc_clear();

	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word != NULL, "Second allocation failed");

	gc_clear();
}
