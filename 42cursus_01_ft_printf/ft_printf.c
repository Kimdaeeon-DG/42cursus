/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:27:42 by daeekim           #+#    #+#             */
/*   Updated: 2024/04/04 19:42:08 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conversion(char f_specifier, va_list args)
{
	if (f_specifier == '%')
		return (write(1, "%", 1));
	else if (f_specifier == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	else if (f_specifier == 's')
		return (prt_str(va_arg(args, char *)));
	else if (f_specifier == 'p')
		return (prt_ptr(va_arg(args, void *)));
	else if (f_specifier == 'd' || f_specifier == 'i')
		return (prt_int(va_arg(args, int)));
	else if (f_specifier == 'u')
		return (prt_unsigned(va_arg(args, unsigned int)));
	else if (f_specifier == 'x')
		return (prt_hexa(va_arg(args, ssize_t), false));
	else if (f_specifier == 'X')
		return (prt_hexa(va_arg(args, ssize_t), true));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!format)
		return (0);
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += conversion(format[i], args);
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
