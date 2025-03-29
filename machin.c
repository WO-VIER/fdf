/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:15:49 by vwautier          #+#    #+#             */
/*   Updated: 2024/12/23 18:23:54 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"


int main()
{
    fdf *fdf;
    int i = 0;
    int j = 0;
    
    fdf = malloc(sizeof(fdf) * 1);
    setup_fdf(fdf, "test_maps/42.fdf");

    while(i < fdf->hauter)
    {
        while(j < fdf->largeur)
        {
            printf("%3d",fdf->map[i][j++]);
        }
        j = 0;
        printf("\n");
        i++;
    }
    while (i< fdf->hauter)
    {
        free(fdf->map[i]);
        i++;
    }
    free(fdf->map);
    free(fdf);
    return (0);
}