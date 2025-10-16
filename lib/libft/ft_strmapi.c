/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:59:49 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/20 11:32:30 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

/*static char	ft_toggle_case(unsigned int n, char c)
{
	(void)n;
	if (c >= 'a' && c <= 'z')
		return ((char)(c - 'a' + 'A'));
	if (c >= 'A' && c <= 'Z')
		return ((char)(c - 'A' + 'a'));
	return (c);
}*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*int	main(void)
{
	char const	*s = "abcdefghijklmnñopqrstuvwxyz,ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
	char	*result;

	result = ft_strmapi(s, ft_toggle_case);

	if (result != NULL)
	{
		printf("Resultado: %s\n", result);
		free(result);
	}
	else
		printf("Fallo en la reserva de memoria\n");
	return (0);
}*/
