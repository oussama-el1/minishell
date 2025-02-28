/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:21:41 by yslami            #+#    #+#             */
/*   Updated: 2024/10/31 20:56:33 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstsize - returns the number of element in the list
 *
 * @lst: the head of the list
 *
 * Description:  Count the number of nodes of the list
 *
 * Return: return the length of the list
*/

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		count;

	count = 0;
	if (lst == NULL)
		return (count);
	curr = lst;
	while (curr)
	{
		curr = curr->next;
		count++;
	}
	return (count);
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
    int size;

    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("One")));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Two")));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Three")));

	t_list *curr;

	curr = lst;
	while (curr)
	{
		ft_putendl_fd(curr->content, 1);
		curr = curr->next;
	}
	size = ft_lstsize(lst);
	ft_putstr_fd("size = ", 1);
    ft_putnbr_fd(size, 1);
    ft_putchar_fd('\n', 1);

    ft_lstclear(&lst, del_content);
    return (0);
}
*/
