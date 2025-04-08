/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:41:29 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int main()
{
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Ajoute le deuxième nœud à la fin de la liste
	ft_lstadd_back(&node1, node2);

	// Ajoute le troisième nœud à la fin de la liste
	ft_lstadd_back(&node1, node3);

	// Affiche la liste pour vérifier
	t_list *current = node1;
	while (current != NULL)
	{
		printf("Node content: %s\n", (char *)current->content);
		current = current->next;
	}

	free(node1);
	free(node2);
	free(node3);

	return 0;
}*/