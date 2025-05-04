/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_initialize_section.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:28:40 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/04 14:35:30 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/gc.h"

int	main(void)
{
	char	*name;

	// name = gc_malloc(sizeof(char) * 100, NULL);
	// if (name)
	// {
	// 	strcpy(name, "hello");
	// 	printf ("STR NAME: %s\n", name);
	// }
	// else
	// 	;
	gc_collect();
		return (0);
}