/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:23:41 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:13:15 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*pointer;
	size_t			total_size;
	size_t			i;

	total_size = count * size;
	if (count != 0 && total_size / count != size)
		return (NULL);
	pointer = (unsigned char *)malloc(total_size);
	if (pointer == NULL)
		return (NULL);
	i = 0;
	while (i < total_size)
		pointer[i++] = 0;
	return ((void *) pointer);
}
