/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:46:08 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/21 13:36:13 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_iterate_pos(char	*dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
	{
		dest[i] = src[i];
		i++;
	}
}

static void	ft_iterate_neg(char	*dest, char *src, size_t n)
{
	while (n > 0)
	{
		n--;
		dest[n] = src[n];
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destino;
	char	*source;

	destino = (char *)dest;
	source = (char *)src;
	if (src == dest)
		return (dest);
	if (destino < source)
		ft_iterate_pos(destino, source, n);
	else if (destino > source)
		ft_iterate_neg(destino, source, n);
	return (dest);
}
