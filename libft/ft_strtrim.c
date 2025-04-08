/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:33:21 by vwautier          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:27 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	boolset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	strlentrimed(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (0);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && boolset(s1[start], set))
		start++;
	while (end > start && boolset(s1[end - 1], set))
		end--;
	return (end - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	size;
	size_t	start;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	size = strlentrimed(s1, set);
	str = malloc(size + 1 * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	start = 0;
	while (s1[start] && boolset(s1[start], set))
		start++;
	i = 0;
	while (i < size)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}

/*
int main(void)
{
    char *result;

    result = ft_strtrim("  Hello, World!  ", " ");
    printf("Result: '%s'\n", result); 
    free(result);

    result = ft_strtrim("xxHello, World!xx", "Hello World");
    printf("Result: '%s'\n", result); 
    free(result);

    result = ft_strtrim("  Hello, World!  ", " ");
    printf("Result: '%s'\n", result); 
    free(result);

    result = ft_strtrim("Hello, World!", " ");
    printf("Result: '%s'\n", result); 
    free(result);

    return 0;
}
*/