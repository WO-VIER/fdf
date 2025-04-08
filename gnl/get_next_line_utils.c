/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:36:36 by vwautier          #+#    #+#             */
/*   Updated: 2024/12/02 12:42:11 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*pointer;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	pointer = *lst;
	while (pointer->next != NULL)
		pointer = pointer->next;
	pointer->next = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*pointer;
	t_list	*temp;

	if (lst == NULL)
		return ;
	pointer = *lst;
	while (pointer != NULL)
	{
		temp = pointer->next;
		free(pointer->content);
		free(pointer);
		pointer = temp;
	}
	*lst = NULL;
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len = 0;
	while (*s)
		str[len++] = *s++;
	return (str);
}

size_t	size_content(t_list *list)
{
	size_t	size;
	t_list	*current;
	char	*content;

	if (!list)
		return (0);
	size = 0;
	current = list;
	while (current)
	{
		content = (char *)current->content;
		while (*content != '\0' && *content != '\n')
		{
			size++;
			content++;
		}
		if (*content == '\n')
		{
			size++;
			break ;
		}
		current = current->next;
	}
	return (size);
}
