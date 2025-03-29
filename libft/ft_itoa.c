/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:43:03 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizenb(int nb)
{
	int	i;

	if (nb == -2147483648)
		return (11);
	if (nb == 0)
		return (1);
	i = 0;
	while (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static char	*initmalloc(int nb, int size)
{
	char	*str;

	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	return (str);
}

char	*ft_itoa(int nb)
{
	int		size;
	char	*str;

	size = sizenb(nb);
	str = initmalloc(nb, size);
	if (!str)
		return (NULL);
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	while (nb > 0)
	{
		size--;
		str[size] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}
/*
int main ()
{
	// Est ce que je peux utiliser mon ft_strdup.c
	//printf("%d\n", sizeNb(-2147483648));
	char * str = ft_itoa(-2147483648);
	// -2147483648

	printf("%s\n",str);

	return 0;
}*/