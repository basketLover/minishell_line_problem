/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:33:08 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:47:48 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	dest = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		dest[j++] = s2[i++];
	}
	j = 0;
	return (dest);
}
/*
int main()
{
	char s1[] = "I love basketball! ";
	char s2[] = "Let's go play!";
	char *dest = ft_strjoin(s1, s2);
	printf("%s\n", dest);
	free(dest);
	return (0);
}*/
