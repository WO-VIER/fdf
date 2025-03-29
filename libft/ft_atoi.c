/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:34:31 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:13:15 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *string)
{
	int	csigne;
	int	number;
	int	i;

	i = 0;
	number = 0;
	csigne = 1;
	while ((string[i] == ' ' || (string[i] >= '\t' && string[i] <= '\r')))
		i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i++] == '-')
			csigne = -1;
	}
	while (string[i] >= '0' && string[i] <= '9')
		number = (number * 10) + (string[i++] - '0');
	return (number * csigne);
}

/*
int main()
{
	printf("ft_atoi(\"   --42\"): %d\n", ft_atoi("   --42")); 
    printf("atoi(\"   --42\"): %d\n", atoi("   --42"));       
	printf("ft_atoi(\"42\"): %d\n", ft_atoi("42"));            
    printf("atoi(\"42\"): %d\n", atoi("42"));                 
    printf("ft_atoi(\"   +456\"): %d\n", ft_atoi("   +456")); 
    printf("atoi(\"   +456\"): %d\n", atoi("   +456"));       
    printf("ft_atoi(\"789abc\"): %d\n", ft_atoi("789abc"));   
    printf("atoi(\"789abc\"): %d\n", atoi("789abc"));         
    printf("ft_atoi(\"abc123\"): %d\n", ft_atoi("abc123"));   
    printf("atoi(\"abc123\"): %d\n", atoi("abc123"));        
    return 0;
}
*/