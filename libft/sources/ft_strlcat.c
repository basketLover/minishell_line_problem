/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:07:02 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 17:04:14 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len == dstsize || dst_len > dstsize)
		return (dstsize + src_len);
	if (src_len < dstsize - dst_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, dstsize - dst_len - 1);
		dst[dstsize -1] = '\0';
	}
	return (dst_len + src_len);
}
/*
int main() {
    char destination[20] = "Hello, ";
    const char source[] = "World!";

    size_t result = ft_strlcat(destination, source, sizeof(destination));

    printf("Result after ft_strlcat: %s\n", destination);
    printf("Total length: %zu\n", result);

    return 0;
}*/
