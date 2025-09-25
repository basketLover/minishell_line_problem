/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:38:48 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:48:00 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize > src_len +1)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize -1);
		dst[dstsize -1] = '\0';
	}
	return (src_len);
}
/*
int main()
{
	char destin[] = "Let's watch it!";
	char source[] = "I love basketball";
	size_t dstsize = sizeof(destin);;

	ft_strlcpy(destin, source, dstsize);
	printf("%s\n", destin);
	return (0);
}*/
