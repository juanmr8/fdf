/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:53 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/19 15:48:27 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst -> next;
	}
	return (size);
}
/*int	main(void)
{
	t_list	*list_1 = ft_lstnew("Holis 1");
	t_list	*list_2 = ft_lstnew("Holis 2");
	t_list	*list_3 = ft_lstnew("Holis 3");
	t_list	*list_4 = ft_lstnew("Holis 4");

	list_1 -> next = list_2;
	list_2 -> next = list_3;
	list_3 -> next = list_4;
	int	list_size = ft_lstsize(list_1);
	printf("Tamaño de la lista %d\n", list_size);
	return (0);
}*/
