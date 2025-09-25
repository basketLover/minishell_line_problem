/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:19:48 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:46:37 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*string1;
	const unsigned char	*string2;
	size_t				i;

	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if ((unsigned char) string1[i] != (unsigned char) string2[i])
			return ((unsigned char) string1[i] - (unsigned char) string2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
    char s1[] = "atoms\0\0\0\0";
    char s2[] = "atoms\0abc";
    char s3[] = "atoms\0\0\0\0";
    char s4[] = "atoms\0abc";
    int result = ft_memcmp(s1, s2, 9);
    int result2 = memcmp(s3, s4, 9);
    printf("%d\n", result);
    printf("%d\n", result2);
    return (0);
}*/
