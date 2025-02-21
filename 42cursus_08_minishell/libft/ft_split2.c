/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:39:00 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 16:39:03 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_separator(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i]) // sep에 c가 있는지 찾는거임.
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char *str, char *sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (!is_separator(str[i], sep))
		{
			words++;
			while (str[i] && !is_separator(str[i], sep))
				i++;
		}
		else
			i++;
	}
	return (words);
}

static	char	*word_splitter(char *str, char *sep)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !is_separator(str[i], sep)) // str[i]가 있는 곳까지 i 증가
		i++;
	word = (char *) malloc(sizeof(char *) * (i + 1)); // i + 1만큼 동적할당
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && !is_separator(str[i], sep)) //str[i]가 없는 곳까지 복사함
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split2(char *str, char *charset) // 공백 단위로 단어 자를려고 만듬
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	j = 0;
	words = (char **) malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (words == NULL || str == NULL || charset == NULL)
		return (NULL);
	while (str[i])
	{
		if (!is_separator(str[i], charset)) // charset에 str[i](공백)가 있냐?
		{
			words[j] = word_splitter(&str[i], charset); // 공백 전까지 저장
			while (str[i] && !is_separator(str[i], charset)) // 공백 이후까지 i 증가
				i++;
			j++; 
		}
		else
			i++;
	}
	words[j] = 0;
	return (words);
}
