/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:50:31 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	mot[2];

	mot[1] = '\0';
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	mot[0] = (n % 10) + '0';
	ft_putchar_fd(mot[0], fd);
}

/*
int main() 
{
	int fd = 1;
	ft_putnbr_fd(12345, fd);
    ft_putnbr_fd(-12345, fd);
    ft_putnbr_fd(-2147483648, fd);
    return 0;
}
*/
/*void	ft_putnbr_fd(int n, int fd)
{
	char mot[1];
	if(n == -2147483648)
		ft_putstr_fd("-2147483648",fd);

	if(n > 9)
	{	
		ft_putnbr_fd(n/10,fd);
		mot[0] = (n % 10 ) + '0';
		ft_putstr_fd(mot, fd);
	}
	else
	{
		mot[0] = (n % 10 ) + '0';
		ft_putstr_fd(mot, fd);
	}

}*/