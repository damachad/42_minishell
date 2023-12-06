/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:48:10 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:29:20 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*head;

	if (!lst || !f || !del)
		return (0);
	new_node = ft_lstnew(f(lst->content));
	if (!new_node)
		return (0);
	head = new_node;
	lst = lst->next;
	while (lst)
	{
		new_node->next = ft_lstnew(f(lst->content));
		if (!new_node->next)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		new_node = new_node->next;
		lst = lst->next;
	}
	new_node->next = NULL;
	return (head);
}
