/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:48:16 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:48:13 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char	*new_str;
	int		i;
	int		s_len;

	i = 0;
	s_len = ft_strlen(s);
	new_str = (char *) malloc ((s_len + 1) * sizeof (char));
	if (!s || !new_str)
		return (NULL);
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
/*
char add_one(unsigned int index, char c)
{
    (void)index; // Avoid unused parameter warning
    return c + 1;
}

int main()
{
    // Test string
    const char *input_str = "Hello, World!";

    // Test the ft_strmapi function with the add_one function
    char *result_str = ft_strmapi(input_str, add_one);

    // Check if the result is not NULL
    if (result_str)
    {
        // Print the original and modified strings
        printf("Original string: %s\n", input_str);
        printf("Modified string: %s\n", result_str);

        // Don't forget to free the allocated memory
        free(result_str);
    }
    else
    {
        // Handle the case where memory allocation fails
        printf("Memory allocation failed.\n");
    }

    return 0;
}*/
