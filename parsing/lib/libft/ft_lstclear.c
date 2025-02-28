/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:50:05 by yslami            #+#    #+#             */
/*   Updated: 2024/10/26 12:28:02 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstclear - clear the full linked list
 *
 * @lst: pointer address to the head
 * @del: address of the function that can delete the element's content
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*temp;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		temp = curr->next;
		ft_lstdelone(curr, del);
		curr = temp;
	}
	*lst = NULL;
}

/*
static void del_content(void *content)
{
    if (content)
        free(content);
}

int main()
{
	t_list	*head = NULL;

	ft_lstadd_back(&head, ft_lstnew(ft_strdup("Node 1")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("Node 2")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("Node 3")));

	t_list	*curr = head;
	while (curr)
	{
		ft_putendl_fd(curr->content, 1);
		curr = curr->next;
	}
	ft_putendl_fd("Clearing list...", 1);
	ft_lstclear(&head, del_content);
	if (!head)
	{
		ft_putendl_fd("List cleared successfully", 1);
	}
	return (0);
}
*/
