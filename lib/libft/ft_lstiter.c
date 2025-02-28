/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:17:14 by yslami            #+#    #+#             */
/*   Updated: 2024/10/27 14:04:24 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstiter - iterate the list and applies the function f to each node
 *
 * @lst: the head of the list
 * @f: the functions that will be applied to each node
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*curr;

	if (!lst || !f)
		return ;
	curr = lst;
	while (curr)
	{
		f(curr->content);
		curr = curr->next;
	}
}

/*
static void del(void *content)
{
    if (content)
        free(content);
}

static void	f(void *content)
{
    char *str = (char *)content;
    int i = 0;

    while (str[i])
    {
        str[i] = ft_toupper(str[i]);
        i++;
	}
}

int main(void)
{
    t_list *lst = NULL;

    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("first")));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("second")));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("third")));

    // Print original list
    t_list *current = lst;
    while (current)
    {
        ft_putendl_fd(current->content, 1);
        current = current->next;
    }

    ft_putendl_fd("After ft_lstiter:", 1);
    ft_lstiter(lst, f);

    // Print modified list
    current = lst;
    while (current)
    {
        ft_putendl_fd(current->content, 1);
        current = current->next;
    }

    // Cleanup
    ft_lstclear(&lst, del);
    return (0);
}
*/
