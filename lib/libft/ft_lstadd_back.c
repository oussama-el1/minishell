/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:55:17 by yslami            #+#    #+#             */
/*   Updated: 2024/10/28 15:28:25 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstadd_back - Adds a new element at the end of the list
 *
 * @lst: pointer address to the first element of the list
 * @new: pointer address of the new element to add to the list
 *
 * Description: Add the 'new' element at the end of the list
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (!lst || !new)
		return ;
	if (lst && *lst)
	{
		curr = *lst;
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = new;
	}
	else if (lst)
	{
		*lst = new;
		return ;
	}
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
    t_list *new1, *new2;

	new1 = ft_lstnew(ft_strdup("Node 1"));
    new2 = ft_lstnew(ft_strdup("Node 2"));

    ft_lstadd_back(&lst, new1);
    ft_lstadd_back(&lst, new2);

	t_list	*curr = lst;
    while (curr)
    {
        ft_putendl_fd(curr->content, 1);
		curr = curr->next;
	}
	ft_lstclear(&lst, del_content);
    return (0);
}
*/
