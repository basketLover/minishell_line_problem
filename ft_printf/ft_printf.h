/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:49:52 by mariserr          #+#    #+#             */
/*   Updated: 2025/06/03 18:03:20 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>

int	ft_printf(const char *string, ...);
int	ft_get_type(char type, va_list args);
int	ft_put_char(int c);
int	ft_put_str(char *str);
int	ft_put_nbr(int n);
int	ft_put_u(long n);
int	ft_put_x(unsigned int n, int type);
int	ft_put_hexa(unsigned long n, char *letter);
int	ft_put_p(void *arg);

#endif
