/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:20:00 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/01 21:43:04 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ROT_SPEED_NORMAL  (M_PI / 36.0)  // ~5° par pression
#define ROT_SPEED_FINE    (M_PI / 72.0)  // ~2.5° pour un contrôle fin

void clear_image(fdf *fdf)
{
	ft_memset(fdf->ptr_image, 0, fdf->line_length * fdf->win_y);
	mlx_clear_window(fdf->mlx_ptr, fdf->winmlx_ptr);
	affichage(fdf);
}

void z_scale(int key, fdf *fdf)
{
    if(key == 49)
        fdf->z_scale = fdf->z_scale + 1;
    if(key == 50)
        fdf->z_scale = fdf->z_scale - 1;
    printf("z_scale = %d\n", fdf->z_scale);
}

void zoom(int key, fdf *fdf)
{
    if (key == 93 || key == 61)
    {
        fdf->zoom = fdf->zoom + 1;
         z_scale(49, fdf);
    }
    if(key == 47 || key == 45)
    {
        fdf->zoom = fdf-> zoom - 1;
        z_scale(50, fdf);
    }

        printf("zoom = %d\n", fdf->zoom);
        printf("z_scale = %d\n", fdf->z_scale);
}

int key_release(int key, fdf *fdf)
{
    if (key >= 0 && key < 256)
        fdf->key[key] = 0;
    return (0);
}

int loop_handler(fdf *fdf)
{
    int redraw = 0;
    
    // Rotations
    if (fdf->key[119] )     // w ou flèche haut
    {
        fdf->x_angle += 0.05;
        redraw = 1;
    }
    if (fdf->key[115])     // s ou flèche bas
    {
        fdf->x_angle -= 0.05;
        redraw = 1;
    }
    if (fdf->key[113])                       // q
    {
        fdf->y_angle += 0.05;
        redraw = 1;
    }
    if (fdf->key[101])                       // e
    {
        fdf->y_angle -= 0.05;
        redraw = 1;
    }
    if (fdf->key[109])                       // m
    {
        fdf->z_angle += 0.05;
        redraw = 1;
    }
    if (fdf->key[110])                       // n
    {
        fdf->z_angle -= 0.05;
        redraw = 1;
    }
    
    // Déplacements
    if (fdf->key[100])    // d ou flèche droite
    {
        fdf->offsx += 10;
        redraw = 1;
    }
    if (fdf->key[97] )     // a ou flèche gauche
    {
        fdf->offsx -= 10;
        redraw = 1;
    }
    if (fdf->key[115])    // s ou flèche bas
    {
        fdf->offsy += 10;
        redraw = 1;
    }
    if (fdf->key[119] )    // w ou flèche haut
    {
        fdf->offsy -= 10;
        redraw = 1;
    }
    
    // Zoom et échelle Z
    if (fdf->key[93] || fdf->key[61])        // ] ou +
    {
        fdf->zoom += 1;
        fdf->z_scale += 1;
        redraw = 1;
    }
    if (fdf->key[47] || fdf->key[45])        // / ou -
    {
        fdf->zoom = (fdf->zoom > 1) ? fdf->zoom - 1 : 1;
        fdf->z_scale = (fdf->z_scale > 0) ? fdf->z_scale - 1 : 0;
        redraw = 1;
    }
    if (fdf->key[49])                        // 1
    {
        fdf->z_scale += 1;
        redraw = 1;
    }
    if (fdf->key[50])                        // 2
    {
        fdf->z_scale = (fdf->z_scale > 0) ? fdf->z_scale - 1 : 0;
        redraw = 1;
    }
    
    // Redessine si nécessaire
    if (redraw)
    {
        clear_image(fdf);
    }
    
    return (0);
}

int key_handler(int key,fdf *fdf)
{
    printf("Key pressed: %d\n", key);
   if (key >= 0 && key < 256)
         fdf->key[key] = 1;
    if (key == 49 || key == 50)
       z_scale(key, fdf);    
    if (key == 93 || key == 61)
       zoom(key, fdf);
    if(key == 47 || key == 45)
       zoom(key, fdf);
    if(key == 100 || key == 65363)
        fdf -> offsx = fdf -> offsx + 10;
    if(key == 97 || key == 65361)
        fdf -> offsx = fdf -> offsx - 10;
    if(key == 115 || key == 65364)   
        fdf -> offsy = fdf -> offsy + 10;
    if(key == 119 || key == 65362)
        fdf -> offsy = fdf -> offsy - 10;
    if(key == 109)
    {
        fdf->z_angle = fdf->z_angle + ROT_SPEED_NORMAL;
    }
    if(key == 110)
    {
        fdf->z_angle = fdf->z_angle - ROT_SPEED_NORMAL;
    }
    if(key ==  65366)
        fdf->x_angle = fdf->x_angle + ROT_SPEED_NORMAL;
    if(key ==  65365)
        fdf->x_angle = fdf->x_angle - ROT_SPEED_NORMAL;
    if(key == 44)
        fdf->y_angle = fdf->y_angle - ROT_SPEED_NORMAL;
    if(key ==  46)
        fdf->y_angle = fdf->y_angle + ROT_SPEED_NORMAL;
    if(key == 65307)
        clear_game(fdf);

    //esc 65307
	
    //mlx_clear_window(fdf->mlx_ptr,fdf->winmlx_ptr);
    //affichage(fdf);
    printf("x_angle = %f y_angle = %f z_angle = %f\n", fdf->x_angle, fdf->y_angle, fdf->z_angle);
	clear_image(fdf);
    return(0);
}