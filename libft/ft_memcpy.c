/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:42:05 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t size)
{
	unsigned char	*strs;
	unsigned char	*strd;
	size_t			i;

	if (!dest && !source)
		return (NULL);
	if (dest == source)
		return (dest);
	strs = (unsigned char *) source;
	strd = (unsigned char *) dest;
	i = 0;
	while (i < size)
	{
		strd[i] = strs[i];
		i++;
	}
	return (dest);
}
