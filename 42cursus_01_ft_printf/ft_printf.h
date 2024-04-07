/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:25:10 by nnuno-ca          #+#    #+#             */
/*   Updated: 2024/04/07 14:05:32 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		prt_str(char const *str);
int		prt_ptr(void *ptr_addr);
int		prt_int(int n);
int		prt_unsigned(unsigned int nbr);
int		prt_hexa(unsigned int nbr, bool upper_case);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *c);

#endif
