/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:58:28 by yslami            #+#    #+#             */
/*   Updated: 2024/10/27 14:07:55 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstnew - create a new list node element
 *
 * @content: The content of the new element
 *
 * Description: create a new list node element,
 * 				initialize its content with @content
 *
 * Return: The new node
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*
static void del_content(void *content)
{
    if (content)
        free(content);
}

int main(void)
{
    t_list *node;
    char *content = "Hello";

    node = ft_lstnew(ft_strdup(content));
    if (node)
    {
        ft_putendl_fd(node->content, 1);
        ft_lstdelone(node, del_content);
    }
    return (0);
}
*/
