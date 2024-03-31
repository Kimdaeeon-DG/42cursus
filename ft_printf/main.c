/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:28:28 by daeekim           #+#    #+#             */
/*   Updated: 2024/03/31 17:28:30 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <limits.h>

int main(void)
{
	char c = 'A';
	char *str = "Hello world!";
	int num = 42;
	unsigned int num2 = 422;
	
	printf("%c %s %p %d %i %u %x %X \n", c, str, str, num, num, num2, num2, num2);
	ft_printf("%c %s %p %d %i %u %x %X \n", c, str, str, num, num, num2, num2, num2);
	return (0);

}
