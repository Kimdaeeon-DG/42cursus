/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:29:22 by daeekim           #+#    #+#             */
/*   Updated: 2024/03/10 16:18:18 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big && !len)
		return (0);
	if (small[0] == '\0' || small == big)
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == small[j] && (i + j) < len)
		{
			if (big[i + j] == '\0' && small[j] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		if (small[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
