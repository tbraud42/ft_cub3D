/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:09:45 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/22 22:45:41 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src == 0 && dest == 0)
		return (NULL);
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char				*array;

	if (nmemb != 0 && size != 0 && (nmemb * size) / size != nmemb)
		return (0);
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	array = malloc(size * nmemb);
	if (array == 0)
		return (0);
	ft_bzero(array, nmemb * size);
	return (array);
}

void	*ft_realloc(void *ptr, size_t newsize, size_t old_size)
{
	char	*newptr;
	size_t	cursize;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = old_size;
	if (newsize <= cursize)
		return (ptr);
	newptr = ft_calloc(newsize, sizeof(ptr));
	if (!newptr)
	{
		ft_putstr_fd("Error\n malloc error\n", 2);
		return (0);
	}
	ft_memcpy(newptr, ptr, cursize);
	free(ptr);
	return (newptr);
}
