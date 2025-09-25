/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:19:06 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:46:50 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;
	size_t			i;

	if (dst == src || (dst == 0 && src == 0))
		return (dst);
	temp_dst = (unsigned char *) dst;
	temp_src = (unsigned char *) src;
	i = 0;
	if (temp_dst > temp_src)
	{
		while (len-- > 0)
			temp_dst[len] = temp_src[len];
	}
	else
	{
		while (i < len)
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}
/*
int main()
{
	char destin[20] = "Let's watch it!";
	char source[20] = "I love basketball";

	ft_memmove(destin, source, 17);
	printf("%s\n", destin);
return (0);	
}*/
