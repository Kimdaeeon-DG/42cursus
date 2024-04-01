/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:27:58 by daeekim           #+#    #+#             */
/*   Updated: 2024/02/28 17:51:04 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*new_ptr;
	unsigned char	src;
	size_t			i;

	new_ptr = ptr;
	src = value;
	i = 0;
	while (i++ < num)
		*new_ptr++ = src;
	return (ptr);
}
