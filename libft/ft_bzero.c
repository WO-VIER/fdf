/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:25:31 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:13:15 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *pointer, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)pointer;
	i = 0;
	while (i < size)
	{
		ptr[i++] = 0;
	}
}

/*
if (pointer == NULL)
		return ;
int main()
{
    char buffer[10];
    strcpy(buffer, "Hello");
    printf("Before bzero: %s\n", buffer);
    ft_bzero(buffer, 10);
    printf("After bzero: %s\n", buffer);
    return 0;
}*/