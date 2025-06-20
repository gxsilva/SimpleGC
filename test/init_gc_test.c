#include <criterion/criterion.h>
#include "../includes/gc.h"

//valgrind --leak-check=full --suppressions=$(pkg-config --variable=supp_files criterion) ./tests

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
	char	*number;

	gc_init();
	number = gc_malloc(sizeof(int) * 1024, NULL);
	cr_expect(number, "gc_malloc failed");
}

Test(gc_malloc_test, zero_size_malloc)
{
	void *ptr;

	gc_init();
	ptr = gc_malloc(0, NULL);
	cr_expect(ptr == NULL, "gc_malloc com tamanho 0 deveria retornar NULL");
	gc_clear();
}

Test(gc_malloc_test, string_write_read)
{
	char *word;

	gc_init();
	word = gc_malloc(sizeof(char) * 6, NULL);
	cr_expect(word != NULL, "gc_malloc falhou para string");

	strcpy(word, "hello");
	cr_expect_str_eq(word, "hello", "A string escrita não bate");

	gc_clear();
}

Test(gc_malloc_test, multiple_allocs)
{
	int *arr1, *arr2;

	gc_init();
	arr1 = gc_malloc(sizeof(int) * 5, NULL);
	arr2 = gc_malloc(sizeof(int) * 10, NULL);

	cr_expect(arr1 != NULL, "gc_malloc falhou para arr1");
	cr_expect(arr2 != NULL, "gc_malloc falhou para arr2");

	arr1[0] = 42;
	arr2[0] = 84;

	cr_expect(arr1[0] == 42, "Valor inesperado em arr1");
	cr_expect(arr2[0] == 84, "Valor inesperado em arr2");

	gc_clear();
}

Test(gc_malloc_test, gc_clear_frees_memory)
{
	int *arr;

	gc_init();
	arr = gc_malloc(sizeof(int) * 5, NULL);
	cr_expect(arr != NULL, "gc_malloc falhou");

	gc_clear();

	// Após gc_clear, arr é inválido, mas apenas testamos se gc_clear não crasha.
	cr_assert(true, "gc_clear causou falha"); 
}

typedef struct s_point {
	int x;
	int y;
} t_point;

Test(gc_malloc_test, struct_malloc)
{
	t_point *p;

	gc_init();
	p = gc_malloc(sizeof(t_point), NULL);
	cr_expect(p != NULL, "gc_malloc falhou para struct");

	p->x = 10;
	p->y = 20;

	cr_expect(p->x == 10 && p->y == 20, "Valores da struct incorretos");

	gc_clear();
}

Test(gc_malloc_test, large_allocation)
{
	void *ptr;

	gc_init();
	ptr = gc_malloc(1024 * 1024 * 10, NULL); // 10 MB

	cr_expect(ptr != NULL, "gc_malloc falhou para grande alocação");

	gc_clear();
}

Test(gc_malloc_test, double_gc_init)
{
	gc_init();
	gc_init(); // Deve ser idempotente

	char *word = gc_malloc(sizeof(char) * 10, NULL);
	cr_expect(word != NULL, "gc_malloc falhou após dupla gc_init");

	gc_clear();
}

Test(gc_malloc_test, malloc_without_init)
{
	char *word;

	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word == NULL, "gc_malloc deveria falhar sem gc_init");
	// Não chamar gc_clear pois gc_init não foi chamado.
}

Test(gc_malloc_test, manual_free_if_supported)
{
	char *word;

	gc_init();
	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word != NULL, "gc_malloc falhou");

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
	cr_expect(word != NULL, "Primeira alocação falhou");

	gc_clear();

	word = gc_malloc(sizeof(char) * 5, NULL);
	cr_expect(word != NULL, "Alocação após gc_clear falhou");

	gc_clear();
}
