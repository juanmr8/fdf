/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:21:00 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/18 18:39:17 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!temp)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

/*int main(void)
{
    t_list *list = NULL;

    t_list *node1 = ft_lstnew("Node1");
    t_list *node2 = ft_lstnew("Node2");
    t_list *node3 = ft_lstnew("Node3");

    ft_lstadd_back(&list, node1);
    printf("First node: %s\n", (char *)list->content);

    ft_lstadd_back(&list, node2);

    ft_lstadd_back(&list, node3);

    t_list *current = list;
    int i = 1;
    while (current)
    {
        printf("Node %d: %s\n", i, (char *)current->content);
        current = current->next;
        i++;
    }

    return (0);
}*/
