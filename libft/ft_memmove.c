/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:27:07 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char		*strd;
	const unsigned char	*strs;

	strd = (unsigned char *)dest;
	strs = (const unsigned char *)src;
	if (dest < src)
		return (ft_memcpy(dest, src, size));
	if (dest > src)
		while (size--)
			strd[size] = strs[size];
	return (dest);
}

/*
if (dest == NULL || src == NULL)
		return (0);*/