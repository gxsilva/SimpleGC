/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:21:36 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/01 23:20:15 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/gc.h"

int	main(int argc, char **argv, char **env)
{
	char	*name;
	
	gc_init();
	name = gc_malloc(sizeof(char) * 100, NULL);
	if (!name)
		return (perror("malloc @var name failure\n"), EXIT_FAILURE);
	gc_print_list();
	gc_collect();
	// gc_print_list();
	return (EXIT_SUCCESS);
}