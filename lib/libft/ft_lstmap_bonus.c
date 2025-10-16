/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:04:50 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/04/21 12:50:45 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *))
{
	t_list	*final_list;
	t_list	*temp;
	t_list	*new_node;
	void	*content;

	if (!lst)
		return (NULL);
	temp = lst;
	final_list = NULL;
	while (temp)
	{
		content = f(temp->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&final_list, del);
			return (NULL);
		}
		ft_lstadd_back(&final_list, new_node);
		temp = temp->next;
	}
	return (final_list);
}

/*void	delete_content(void *content)
{
	free(content);
}

void	*add_content(void *content)
{
    char *original = (char *)content;
    char *new_content = ft_strdup(original);

	int i = 0;
	while (new_content[i])
	{
		new_content[i] = 'a';
		i++;
	}
	return (new_content);
}

int	main(void)
{
    t_list *list = NULL;

    t_list *node1 = ft_lstnew("Node1");
    t_list *node2 = ft_lstnew("Node2");
    t_list *node3 = ft_lstnew("Node3");

	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);

	t_list	*temp;

	temp = list;

	while (temp)
	{
		printf("Node's content: %s\n", (char *)temp->content);
		temp = temp->next;
	}

	t_list	*new_list = ft_lstmap(list, add_content, delete_content);

	while (new_list)
	{
		printf("Node's content: %s\n", (char *)new_list->content);
		new_list = new_list->next;
	}
	return (0);
}*/
