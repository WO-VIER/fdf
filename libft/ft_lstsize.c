/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:36:57 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*pointer;

	if (!lst)
		return (0);
	i = 1;
	pointer = lst;
	while (pointer->next != NULL)
	{
		i++;
		pointer = pointer->next;
	}
	return (i);
}

/*
int main()
{
    // Crée manuellement une liste chaînée avec quelques nœuds
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    // Lie les nœuds entre eux
    node1->next = node2;
    node2->next = node3;

    // Teste la fonction ft_lstsize
    int size = ft_lstsize(node1);
    printf("List size: %d\n", size); // Devrait afficher 3

    // Libère la mémoire allouée
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/