/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:08:51 by daeekim           #+#    #+#             */
/*   Updated: 2024/03/05 18:11:42 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	int		len;
	int		i;
	char	*new_string;

	len = 0;
	while (*(string + len))
		len++;
	new_string = (char *)malloc(sizeof(char) * (len + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (string[i])
	{
		new_string[i] = string[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
