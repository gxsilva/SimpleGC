/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:52:22 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/06/21 23:13:50 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

int	gc_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char *gc_strdup(const char *s)
{
	size_t len = 0;
	char *dup;

	while (s[len])
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return NULL;
	for (size_t i = 0; i < len; i++)
		dup[i] = s[i];
	dup[len] = '\0';
	return dup;
}