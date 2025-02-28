/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:38:11 by yslami            #+#    #+#             */
/*   Updated: 2024/10/27 14:13:02 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstdelone - removes one element from the list
 *
 * @lst: the node to be deleted
 * @del: address of the function that can delete the element's content
 *
 * Description: Free the memory of the node passed as parameter
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

/*
static void del_content(void *content)
{
    if (content)
        free(content);
}

int main(void)
{
	 t_list *lst = NULL;

    // Create new nodes
    t_list *node1 = ft_lstnew(ft_strdup("Node 1"));
    t_list *node2 = ft_lstnew(ft_strdup("Node 2"));

    if (!node1 || !node2) {
        // Handle allocation failure
        return 1;
    }

    ft_lstadd_back(&lst, node1);
    ft_lstadd_back(&lst, node2);

    // Print current list
    ft_putendl_fd("List before deletion:", 1);
    t_list *curr = lst;
    while (curr)
    {
        ft_putendl_fd(curr->content, 1);
        curr = curr->next;
    }

    // Delete the last node
    t_list *last = ft_lstlast(lst);
    if (last)
    {
        ft_lstdelone(last, del_content);
		lst->next = curr;// or lst->next = NULL;
    }

    // Print list after deletion
    ft_putendl_fd("List after deleting the last node:", 1);
    curr = lst;
    while (curr)
    {
        ft_putendl_fd(curr->content, 1);
        curr = curr->next;
    }
    // Clean up the remaining list
    ft_lstclear(&lst, del_content);
    return (0);
}
*/
