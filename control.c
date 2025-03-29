/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:20:00 by vwautier          #+#    #+#             */
/*   Updated: 2025/02/07 16:13:08 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void clear_image(fdf *fdf)
{
	ft_memset(fdf->ptr_image, 0, fdf->line_length * fdf->win_y);
	mlx_clear_window(fdf->mlx_ptr, fdf->winmlx_ptr);

	affichage(fdf);
}

int key_handler(int key,fdf *fdf)
{
    printf("%d\n",key);
    if (key == 93 || key == 61)
        fdf->zoom = fdf->zoom + 1;
    if(key == 47 || key == 45)
        fdf->zoom = fdf->zoom - 1;
    if(key == 100 || key == 65363)
        fdf -> offsx = fdf -> offsx + 10;
    if(key == 97 || key == 65361)
        fdf -> offsx = fdf -> offsx - 10;
    if(key == 115 || key == 65364)   
        fdf -> offsy = fdf -> offsy + 10;
    if(key == 119 || key == 65362)
        fdf -> offsy = fdf -> offsy - 10;
    if(key == 109)
        fdf->angle = fdf->angle + 0.1;
    if(key == 110)
        fdf->angle = fdf->angle - 0.1;
    if(key == 65307)
        clear_game(fdf);

    //esc 65307
	
    //mlx_clear_window(fdf->mlx_ptr,fdf->winmlx_ptr);
    //affichage(fdf);
	clear_image(fdf);
    return(0);
}