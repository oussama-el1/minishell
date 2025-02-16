/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:10 by yslami            #+#    #+#             */
/*   Updated: 2024/10/25 20:42:43 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstlast - get the last element of the list
 *
 * @lst: the start of the list
 *
 * Return: return a pointer of the last node of the list
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	curr = lst;
	if (curr == NULL)
		return (NULL);
	while (curr->next)
	{
		curr = curr->next;
	}
	return (curr);
}

/*
static void del_content(void *content)
{
    if (content)
        free(content);
}

int main()
{
	t_list *lst = NULL;
    t_list *last;

    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Node 1")));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Node 2")));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Node 3")));

    last = ft_lstlast(lst);
    if (last)
        ft_putendl_fd(last->content, 1);
	ft_lstclear(&lst, del_content);
	return (0);
}
*/
