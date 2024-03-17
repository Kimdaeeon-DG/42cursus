/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:42:21 by daeekim           #+#    #+#             */
/*   Updated: 2024/03/15 16:20:40 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t			index;
	unsigned char	*new_str1;
	unsigned char	*new_str2;

	new_str1 = (unsigned char *)str1;
	new_str2 = (unsigned char *)str2;
	index = 0;
	while (new_str1[index] != '\0' && index < num)
	{
		if (new_str1[index] != new_str2[index])
			return (new_str1[index] - new_str2[index]);
		index++;
	}
	if (new_str1[index] == '\0' && index < num)
		return (new_str1[index] - new_str2[index]);
	return (0);
}
