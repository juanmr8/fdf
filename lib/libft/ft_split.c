/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:31:45 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/21 13:36:47 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	count_words(char const *s, char c)
{
	int	inside_word;
	int	i;
	int	word_count;

	i = 0;
	inside_word = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && inside_word == 0)
		{
			inside_word = 1;
			word_count++;
		}
		else if (s[i] == c && inside_word == 1)
			inside_word = 0;
		i++;
	}
	return (word_count);
}

static size_t	modified_ft_strlen(const char *s, char c, int start)
{
	size_t	len;

	len = 0;
	while (s[start + len] != c && s[start + len])
		len++;
	return (len);
}

static int	fill_array(char **arr, char const *s, char c, int *j)
{
	int	i;
	int	inside_word;

	i = 0;
	inside_word = 0;
	while (s[i])
	{
		if (inside_word == 0 && s[i] != c)
		{
			inside_word = 1;
			arr[*j] = ft_substr(s, i, modified_ft_strlen(s, c, i));
			if (!arr[*j])
				return (-1);
		}
		if (inside_word == 1 && s[i] == c)
		{
			inside_word = 0;
			(*j)++;
		}
		i++;
	}
	if (inside_word == 1)
		(*j)++;
	return (0);
}

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;
	int		j;

	j = 0;
	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (fill_array(arr, s, c, &j) == -1)
	{
		free_array(arr);
		return (NULL);
	}
	arr[j] = NULL;
	return (arr);
}
