/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:37:54 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 16:37:56 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	char		*str;
	int			i;

	i = ft_nbrlen(n, 10);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if ((!str))
		return (NULL);
	str[i--] = '\0';
	while (n)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int	ft_print_unsigned(unsigned int n, t_flags *flags)
{
	int		len;
	char	*nbr;

	len = 0;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else
	{
		if (flags->zero)
			len += ft_print_zero(n, flags, 0);
		else if (flags->dot)
			len += ft_precision_others(n, flags, 0);
		nbr = ft_uitoa(n);
		len += ft_print_str(nbr, flags);
		free(nbr);
	}
	return (len);
}
