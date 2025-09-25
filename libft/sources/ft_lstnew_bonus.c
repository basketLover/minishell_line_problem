/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:42:09 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:46:19 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
int main()
{
    // Test the ft_lstnew function
    int *data = (int *)malloc(sizeof(int));
    *data = 42;

    t_list *new_node = ft_lstnew((void *)data);

    // Check if the result is not NULL
    if (new_node != NULL)
    {
        // Print the content of the new node
        printf("Content of the new node: %d\n", *((int *)new_node->content));

        // Don't forget to free the allocated memory for data and the new_node
        free(data);
        free(new_node);
    }
    else
    {
        // Handle the case where memory allocation fails
        printf("Memory allocation failed in ft_lstnew.\n");
    }

    return 0;
}*/
