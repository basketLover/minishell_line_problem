/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:35:07 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:46:43 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (dst == 0 && src == 0)
		return (NULL);
	temp_dst = (unsigned char *) dst;
	temp_src = (unsigned char *) src;
	while (n > 0)
	{
		*(temp_dst++) = *(temp_src++);
		n--;
	}
	return (dst);
}
/*
int main()
{
	char source[] = "I love basketball";
	char destin[20] = "";

	ft_memcpy(destin, source, sizeof(destin));
	printf("%s\n", destin);
	return (0);
}*/
