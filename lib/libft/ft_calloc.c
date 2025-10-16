/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:19:13 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/21 16:39:11 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			total_size;

	if (nmemb > 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return ((void *)ptr);
}

/*int main(void)
{
    void *std_ptr1 = calloc(0, 10);
    void *std_ptr2 = calloc(10, 0);

    void *ft_ptr1 = ft_calloc(0, 10);
    void *ft_ptr2 = ft_calloc(0, 0);

    printf("Standard calloc(0, 10): %p\n", std_ptr1);
    printf("Standard calloc(10, 0): %p\n", std_ptr2);
    printf("ft_calloc(0, 10): %p\n", ft_ptr1);
    printf("ft_calloc(0, 0): %p\n", ft_ptr2);

    // Free all pointers
    free(std_ptr1);
    free(std_ptr2);
    free(ft_ptr1);
    free(ft_ptr2);

    return 0;
}*/
