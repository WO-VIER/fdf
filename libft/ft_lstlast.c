/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:30:21 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*pointer;

	if (!lst)
		return (NULL);
	pointer = lst;
	while (pointer->next != NULL)
		pointer = pointer->next;
	return (pointer);
}
/*
int main()
{
	
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    // Lie les nœuds entre eux
    node1->next = node2;
    node2->next = node3;

    // Teste la fonction ft_lstlast
    t_list *last = ft_lstlast(node1);
    if (last)
        printf("Last node content: %s\n", (char *)last->content); 

    
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/