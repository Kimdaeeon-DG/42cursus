/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:59:17 by daeekim           #+#    #+#             */
/*   Updated: 2024/03/10 16:07:43 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cur;

	new = ft_lstnew(f(lst->content));
	cur = new;
	lst = lst -> next;
	while (lst)
	{
		cur -> next = ft_lstnew(f(lst->content));
		cur = cur-> next;
		if (cur == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		lst = lst -> next;
	}
	return (new);
}
