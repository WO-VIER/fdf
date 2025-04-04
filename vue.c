/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vue.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:56:38 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/04 16:55:13 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void bit_rotate(fdf *fdf, float *x, float *x1, float *y, float *y1, int z, int z1)
{
    *x = (float)(((int)(*x + fdf->offsx) - (int)(*y + fdf->offsy)) >> 1);
    *y = (float)(((int)(*x + fdf->offsx) + (int)(*y + fdf->offsy)) >> 1) - z;
    *x1 = (float)(((int)(*x1 + fdf->offsx) - (int)(*y1 + fdf->offsy)) >> 1);
    *y1 = (float)(((int)(*x + fdf->offsx) + (int)(*y1 + fdf->offsy)) >> 1) - z1;
    *x = *x + fdf->offsx;
    *x1 = *x1 + fdf->offsx;
    *y = *y + fdf->offsy;
    *y1 = *y1 + fdf->offsy;
}


static void rotate_x(fdf *fdf, float *x, float *y, float *z)
{
    float temp_y = *y;
    float temp_z = *z;
    *y = temp_y * cos(fdf->x_angle) - temp_z * sin(fdf->x_angle);
    *z = temp_y * sin(fdf->x_angle) + temp_z * cos(fdf->x_angle);
}

static void rotate_y(fdf *fdf, float *x, float *y, float *z)
{
    float temp_x = *x;
    float temp_z = *z;
    *x = temp_x * cos(fdf->y_angle) + temp_z * sin(fdf->y_angle);
    *z = -temp_x * sin(fdf->y_angle) + temp_z * cos(fdf->y_angle);
}

static void rotate_z(fdf *fdf, float *x, float *y, float *z)
{
    float temp_x = *x;
    float temp_y = *y;
    *x = temp_x * cos(fdf->z_angle) - temp_y * sin(fdf->z_angle);
    *y = temp_x * sin(fdf->z_angle) + temp_y * cos(fdf->z_angle);
}

static void rotate_point(fdf *fdf, float *x, float *y, float *z)
{
    if (fdf->x_angle != 0)
        rotate_x(fdf, x, y, z);
    if(fdf->y_angle != 0)
        rotate_y(fdf, x, y, z);
    if(fdf->z_angle != 0)
       rotate_z(fdf, x, y, z);
}

void improved_isometric_projection(fdf *fdf, float *x, float *x1, float *y, float *y1, int z, int z1)
{
    float z_scaled = (z * (fdf->zoom * fdf->z_scale)); // z * fdf->z_scale
    float z1_scaled = (z1 * (fdf->zoom * fdf->z_scale)); // z1 * fdf->z_scale

    //z *fdf->z_scale;
    //z1 * fdf->z_scale;
    *x *= fdf->zoom;
    *y *= fdf->zoom;
    *x1 *= fdf->zoom;
    *y1 *= fdf->zoom;

    float center_x = (fdf->largeur * fdf->zoom) / 2.0f;
    float center_y = (fdf->hauter * fdf->zoom) / 2.0f;

    *x -= center_x;
    *y -= center_y;
    *x1 -= center_x;
    *y1 -= center_y;

    rotate_point(fdf, x, y, &z_scaled);
    rotate_point(fdf, x1, y1, &z1_scaled);

    float old_x = *x;
    float old_y = *y;
    //float old_x1 = *x1;
    //float old_y1 = *y1;

    
    *x = (old_x - old_y) * cos(M_PI / 6);
    *y = (old_x + old_y) * sin(M_PI /6) - z_scaled;

    old_x = *x1;
    old_y = *y1;
    *x1 = (old_x - old_y) * cos(M_PI /6);
    *y1 = (old_x + old_y) * sin(M_PI /6) - z1_scaled;
    
    *x += fdf->win_x / 2 + fdf->offsx;
    *y += fdf->win_y / 2 + fdf->offsy;
    *x1 += fdf->win_x / 2 + fdf->offsx;
    *y1 += fdf->win_y / 2 + fdf->offsy;

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

static void extract_rgb(int color, int *r, int *g, int *b)
{
    *r = (color >> 16) & 0xFF;
    *g = (color >> 8) & 0xFF;
    *b = color & 0xFF;
}

static float interpolate(float start, float end, float percentage)
{
    return start + (end - start) * percentage;
}

// Fonction pour créer une couleur à partir des composantes RGB
static int create_rgb(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}



// Fonction pour interpoler une couleur entre deux couleurs
static int interpolate_color(int color1, int color2, float percentage)
{
    int r1, g1, b1;
    int r2, g2, b2;
    int r, g, b;

    extract_rgb(color1, &r1, &g1, &b1);
    extract_rgb(color2, &r2, &g2, &b2);

    r = r1 + (int)((r2 - r1) * percentage);
    g = g1 + (int)((g2 - g1) * percentage);
    b = b1 + (int)((b2 - b1) * percentage);

    return create_rgb(r, g, b);
}

// Fonction pour obtenir la couleur correspondant à une hauteur
int get_color_for_height(fdf *fdf, float height)
{
    float percentage;
    int color_low = 0xEEAECA;  // Rose: rgb(238,174,202)
    int color_high = 0x94BBE9; // Bleu: rgb(148,187,233)
    
    // Cas particulier: si min_z = max_z (carte plate)
    if (fdf->min_z == fdf->max_z)
        return color_low;
    
    // Calculer le pourcentage entre min_z et max_z
    percentage = (height - fdf->min_z) / (float)(fdf->max_z - fdf->min_z);
    
    // S'assurer que le pourcentage est entre 0 et 1
    if (percentage < 0)
        percentage = 0;
    if (percentage > 1)
        percentage = 1;
    
    // Interpoler entre les deux couleurs
    return interpolate_color(color_low, color_high, percentage);
}


void fdf_color(fdf *fdf, int z, int z1)
{
    // Utiliser le gradient pour les hauteurs non nulles
    if (z || z1)
        fdf->couleur = get_color_for_height(fdf, z > z1 ? z : z1);
    else
        fdf->couleur = 0xFFFFFF; // Blanc pour les hauteurs nulles
}


void fdf_color2(fdf *fdf, int z, int z1)
{
    if (z || z1)
        fdf->couleur = get_color_for_height(fdf, z > z1 ? z : z1);
    else
        fdf->couleur = 0xFFFFFF;
}


void isometric_projection(fdf *fdf, float *x, float *x1, float *y, float *y1, int z, int z1)
{
    float temp; 

    
    *x *= fdf->zoom;
    *y *= fdf->zoom;
    *x1 *= fdf->zoom;
    *y1 *= fdf->zoom;

        
    
    
    temp = *x;
    // Formule standard de projection isométrique avec angle de 30 degrés (PI/6)
    *x = (temp - *y) * cos(M_PI / 6);

    *y = (temp + *y) * sin(M_PI / 6) - (z * (fdf->zoom * fdf->z_scale));

    temp = *x1;
    *x1 = (temp - *y1) * cos(M_PI / 6);

    *y1 = (temp + *y1) * sin(M_PI / 6) - (z1 * (fdf->zoom * fdf->z_scale));
}

int max_dx_dy(int dx, int dy)
{
    if (dx > dy)
        return dx;
    return dy;
}



void bresenham(float x, float y, float x1, float y1, fdf *fdf)
{
    float dx = 0;
    float dy = 0;
    int max = 0;
    int z = 0;
    int z1 = 0;
    
    z = fdf->map[(int)y][(int)x];
    z1 = fdf->map[(int)y1][(int)x1];

    //fdf_color(fdf, z, z1);

    improved_isometric_projection(fdf, &x, &x1, &y, &y1, z, z1);
    //isometric_projection(fdf, &x, &x1, &y, &y1, z, z1);
    dx = x1 - x;
    dy = y1 - y;
   // max = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    max = max_dx_dy(fabs(dx), fabs(dy));
    //if (max == 0)
        //max = 1;

    dx = dx / max;
    dy = dy / max;

    int i;
    i = 0;
   //printf(); 
    while((int)(x - x1) || (int)(y - y1))
    {
        float percentage = (float)i / max;
        float current_height = interpolate(z, z1, percentage);
        
        // Obtenir la couleur pour la hauteur actuelle
        int color = get_color_for_height(fdf, current_height);;
        if((int)x <= fdf->win_x || (int)y <= fdf->win_y)
        {
			mlx_pixel_put_img(fdf, (int)x, (int)y, color);
        }
		x = x + dx;
		y = y + dy;
        
        i++;
        if (i > max + 1)
            break;
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
				bresenham(x, y, x + 1, y, fdf);
			if(y < fdf->hauter - 1)
				bresenham(x, y, x, y + 1, fdf);
			x++;	
		}
		y++;
    }
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->winmlx_ptr, fdf->mlx_image, 0,0);
    return (0);
}