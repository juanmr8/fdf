/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:47:39 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/21 09:21:53 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr;
	char	*source;
	size_t	i;

	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	ptr = dest;
	source = (char *)src;
	i = 0;
	while (i < n)
	{
		ptr[i] = source[i];
		i++;
	}
	return (dest);
}
