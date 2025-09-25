/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:02:20 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:46:58 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *) b;
	while (len > 0)
	{
		*(temp++) = (unsigned char) c;
		len --;
	}
	return (b);
}
/*
int	main()
{
	char string[5];

	printf("%s\n", ft_memset(string, '@', sizeof(string)));
	return (0);
}*/
