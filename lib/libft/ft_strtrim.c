/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:17:45 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/21 13:38:35 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	match(const char *set, const char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && match(set, s1[start]))
		start++;
	end = (ft_strlen(s1) - 1);
	while (end > start && match(set, s1[end]))
		end--;
	return (ft_substr(s1, start, ((end - start) + 1)));
}

/*int	main(void)
{
	char	*trimmed = ft_strtrim("oiouioi", "oi");
	write(1, trimmed, 20);
	return(0);
}*/
