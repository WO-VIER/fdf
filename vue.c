/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vue.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:56:38 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/02 00:25:07 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void bit_rotate(fdf *fdf, float *x, float *x1, float *y, float *y1, int z, int z1)
{
    //bit shift droite revient a diviser par deux et bit shift gauche revient a multiplier par deux (*0.5) >> 1 divise << 1 multiplie 
    /*printf("x = %f, y = %f, x1 = %f, y1 = %f\n", *x, *y, *x1, *y1);
    printf("offsx = %d, offsy = %d\n", fdf->offsx, fdf->offsy);
    */
    //int oldx;

    //oldx = (int)*x;
    *x = (float)(((int)(*x + fdf->offsx) - (int)(*y + fdf->offsy)) >> 1);
    //printf("x = %f, y = %f\n", *x, *y);
    *y = (float)(((int)(*x + fdf->offsx) + (int)(*y + fdf->offsy)) >> 1) - z;
    //oldx = *x1;
    //oldy = *y1;
    //oldx = (int)*x1;
    *x1 = (float)(((int)(*x1 + fdf->offsx) - (int)(*y1+ fdf->offsy)) >> 1);
    *y1 = (float)(((int)(*x+ fdf->offsx) + (int)(*y1 + fdf->offsy)) >> 1) - z1;
    /*printf("x = %f, y = %f, x1 = %f, y1 = %f\n", *x, *y, *x1, *y1);
    exit(1);*/
	*x = *x + fdf->offsx ;
    *x1 = *x1 + fdf->offsx;
    *y = *y + fdf->offsy;
    *y1 = *y1 + fdf->offsy;
}



void fdf_color(fdf *fdf, int z, int z1)
{
    int height = (z > z1) ? z : z1;
    
    // Protection contre la division par zéro
    if (fdf->max_z == fdf->min_z) {
        fdf->couleur = 0xffffff;  // Blanc si carte plate
        return;
    }
    
    // Calcul du ratio (0.0 pour min_z, 1.0 pour max_z)
    float ratio = (float)(height - fdf->min_z) / (fdf->max_z - fdf->min_z);
    
    // Composantes RGB
    int r = 255;                          // Reste à 255
    int g = 255 - (int)(ratio * 110);     // Varie de 255 à 145
    int b = 255;                          // Reste à 255
    
    // Création de la couleur finale
    fdf->couleur = (r << 16) | (g << 8) | b;
}

static void rotate_point(fdf *fdf, float *x, float *y, float *z)
{
    float old_x = *x;
    float old_y = *y;
    float old_z = *z;
    float temp_x, temp_y, temp_z;
    double angle;


    // Rotation X
    temp_y = old_y;
    temp_z = old_z;
    old_y = temp_y * cos(fdf->x_angle) - temp_z * sin(fdf->x_angle);
    old_z = temp_y * sin(fdf->x_angle) + temp_z * cos(fdf->x_angle);
    
    // Rotation Y
    temp_x = old_x;
    temp_z = old_z;
    old_x = temp_x * cos(fdf->y_angle) + temp_z * sin(fdf->y_angle);
    old_z = -temp_x * sin(fdf->y_angle) + temp_z * cos(fdf->y_angle);
    
    // Rotation Z
    temp_x = old_x;
    temp_y = old_y;
    *x = temp_x * cos(fdf->z_angle) - temp_y * sin(fdf->z_angle);
    *y = temp_x * sin(fdf->z_angle) + temp_y * cos(fdf->z_angle);
    
    *z = old_z; // Sauvegarde la nouvelle valeur Z pour l'effet de hauteur
}

void isometric_projection2(fdf *fdf,float *x, float *x1, float *y, float *y1, int z, int z1)
{
    float z_float = z * fdf->z_scale;
    float z1_float = z1 * fdf->z_scale;
    
    // 1. Calcul du centre du modèle
    float center_x = fdf->largeur / 2.0f * fdf->zoom;
    float center_y = fdf->hauter / 2.0f * fdf->zoom;
    
    // 2. Translation pour que le centre soit à (0,0)
    *x = *x * fdf->zoom - center_x;
    *y = *y * fdf->zoom - center_y;
    *x1 = *x1 * fdf->zoom - center_x;
    *y1 = *y1 * fdf->zoom - center_y;

   
    
    int tmp;
	tmp = *x;
    *x = (*x - *y) * cos(fdf->z_angle);//0.8
    *y = (tmp + *y) * sin(fdf->z_angle) - (z * fdf->z_scale);
	tmp = *x1;
	*x1 = (*x1 - *y1) * cos(fdf->z_angle);//0.8
    *y1 = (tmp + *y1) * sin(fdf->z_angle) - (z1 * fdf->z_scale);
    
    *x = *x + fdf->offsx;
    *x1 = *x1 + fdf->offsx;
    *y = *y + fdf->offsy ;
    *y1 = *y1 + fdf->offsy;
}

void isometric_projection(fdf *fdf, float *x, float *x1, float *y, float *y1, int z, int z1)
{
    float z_float = z * fdf->z_scale;
    float z1_float = z1 * fdf->z_scale;
    
    // 1. Calcul du centre du modèle
    float center_x = ((fdf->largeur / 2.0f) * fdf->zoom) * cos(M_PI / 6);
    float center_y = ((fdf->hauter / 2.0f) * fdf->zoom) * sin(M_PI / 6);
    //printf("center_x = %f, center_y = %f\n", center_x, center_y);
    
    // 2. Translation pour que le centre soit à (0,0)
    
    *x = *x * fdf->zoom - center_x;
    *y = *y * fdf->zoom - center_y;
    *x1 = *x1 * fdf->zoom - center_x;
    *y1 = *y1 * fdf->zoom - center_y;
    
    
    // 3. Application des rotations (autour de 0,0)
    float tmp_x = *x, tmp_y = *y, tmp_x1 = *x1, tmp_y1 = *y1;
    rotate_point(fdf, &tmp_x, &tmp_y, &z_float);
    rotate_point(fdf, &tmp_x1, &tmp_y1, &z1_float);
    *x = tmp_x;
    *y = tmp_y;
    *x1 = tmp_x1;
    *y1 = tmp_y1;
    
    // 4. Application des hauteurs
    *y = *y - z_float;
    *y1 = *y1 - z1_float;
    
    // 5. Ajout des décalages
    *x = *x + center_x + fdf->offsx;
    *y = *y + center_y + fdf->offsy;
    *x1 = *x1 + center_x + fdf->offsx;
    *y1 = *y1 + center_y + fdf->offsy;
    printf("x = %f, y = %f, x1 = %f, y1 = %f\n", *x, *y, *x1, *y1);
}

void	mlx_pixel_put_img(fdf *fdf, int x, int y, int color)
{
	char	*addr;
	
	if((x >= 0 && y >= 0) && (x < fdf->win_x && y <fdf->win_y))
	{
		addr = fdf->ptr_image + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
		*(unsigned int*)addr = color;
 	}
}

void bresenham(float x, float y, float x1, float y1, fdf *fdf)
{
    float dx;
    float dy;
    int max;
    int z;
    int z1;

    z = fdf->map[(int)y][(int)x];
    z1 = fdf->map[(int)y1][(int)x1];

    //couleur
    fdf_color(fdf, z, z1);

    // Projection isométrique
    isometric_projection2(fdf,&x,&x1,&y,&y1,z,z1);
    
    dx = x1 - x;
    dy = y1 - y;
    max = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    dx = dx / max;
    dy = dy / max;
    while((int)(x - x1) || (int)(y - y1))
    {
        if(x <= fdf->win_x || y <= fdf->win_y)
			mlx_pixel_put_img(fdf, x, y, fdf->couleur);
		x = x + dx;
		y = y + dy;
    }
}

void draw_center_cross(fdf *fdf)
{
    int center_x = fdf->win_x / 2;
    int center_y = fdf->win_y / 2;
    int size = 10;            // Taille de chaque branche de la croix
    int color = 0xFF0000;     // Rouge pour la croix
    int i;
    
    // Ligne horizontale
    i = center_x - size;
    while (i <= center_x + size)
    {
        mlx_pixel_put_img(fdf, i, center_y, color);
        i++;
    }
    
    // Ligne verticale
    i = center_y - size;
    while (i <= center_y + size)
    {
        mlx_pixel_put_img(fdf, center_x, i, color);
        i++;
    }
}




int affichage(fdf *fdf)
{
	int x;
	int y;
	y = 0;
    
	while(y < fdf->hauter)
	{
		x = 0;
		while(x < fdf -> largeur)
		{
			if(x < fdf->largeur - 1)
				bresenham(x, y, x + 1, y, fdf); // connection des points de x a x + 1
			if(y < fdf->hauter - 1)
				bresenham(x, y, x, y + 1, fdf); // connection des points de y a y + 1
			x++;	
		}
		y++;
    }
    draw_center_cross(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->winmlx_ptr, fdf->mlx_image, 0,0);

    return (0);
}