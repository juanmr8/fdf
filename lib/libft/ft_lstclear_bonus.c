/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:21:22 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/20 12:19:50 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	del(void *content)
{
	free(content);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	temp = *lst;
	if (temp == NULL)
		return ;
	while (temp)
	{
		temp2 = temp->next;
		del(temp->content);
		free(temp);
		temp = temp2;
	}
	*lst = NULL;
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

    ft_lstclear(&list, del);

    printf("\nList after clearing:\n");
    if (list == NULL)
        printf("List is empty!\n");
    else
        printf("List is not empty - something went wrong.\n");

    return (0);
    return (0);
}*/
