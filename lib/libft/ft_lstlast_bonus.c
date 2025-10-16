/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:54:46 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/18 18:11:13 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	1. Iterar la lista para llegar al final
	2. Retornar el valor al final de la iteración
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

/*int	main(void)
{
	t_list	*test1 = ft_lstnew("Test1");
	t_list	*test2 = ft_lstnew("Test2");

	test1->next = test2;
	t_list	*final = ft_lstlast(test1);
	printf("El contenido de test1: %s\n", (char *)test1->content);
	printf("El contenido del ultimo nodo es: %s\n", (char *)final->content);
	return (0);
}*/
