/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:52:48 by daeekim           #+#    #+#             */
/*   Updated: 2024/03/10 17:53:55 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_number(unsigned int num, int fd)
{
	char	c;

	if (num <= 0)
		return ;
	print_number(num / 10, fd);
	c = num % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (fd < 0)
		return ;
	if (n < 0)
		write(fd, "-", 1);
	else if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n == -2147483648)
		num = 2147483648;
	else
	{
		if (n < 0)
			n *= -1;
		num = (unsigned int)n;
	}
	print_number(num, fd);
}
