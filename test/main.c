/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:21:36 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/01 23:39:20 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/gc.h"

int	main(int argc, char **argv, char **env)
{
	char	*name;
	int		*numbers;
	double	*values;
	int		i;

	gc_init();

	// Allocate memory for a string
	name = gc_malloc(sizeof(char) * 100, "name");
	if (!name)
		return (perror("malloc @var name failure\n"), EXIT_FAILURE);

	// Allocate memory for an array of integers
	numbers = gc_malloc(sizeof(int) * 50, "numbers");
	if (!numbers)
		return (perror("malloc @var numbers failure\n"), EXIT_FAILURE);

	// Allocate memory for an array of doubles
	values = gc_malloc(sizeof(double) * 20, "values");
	if (!values)
		return (perror("malloc @var values failure\n"), EXIT_FAILURE);

	// Fill the allocated memory with some data
	for (i = 0; i < 50; i++)
		numbers[i] = i * 2;

	for (i = 0; i < 20; i++)
		values[i] = i * 1.5;

	// Print the allocated memory list
	gc_print_list();

	// Perform garbage collection
	gc_collect();

	// Uncomment to print the list after collection
	// gc_print_list();

	return (EXIT_SUCCESS);
}