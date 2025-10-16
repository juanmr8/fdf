/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:57:45 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/16 10:45:26 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	index;

	if (n == 0)
		return (0);
	index = 0;
	while (index < n - 1 && s1[index] == s2[index] && s1[index])
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
