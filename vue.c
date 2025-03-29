/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vue.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:56:38 by vwautier          #+#    #+#             */
/*   Updated: 2025/02/07 21:53:24 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <time.h>
#include "fdf.h"
#define ISO_ANGLE 0.785398 // 45 degrés
#define ISO_COS 0.707107  // cos(45°)
#define ISO_SIN 0.707107  // sin(45°)

void fdf_color(fdf *fdf, int z, int z1)
{
    if (z || z1)
    	fdf->couleur = 0xe80c0c;
	else
    fdf->couleur = 0xFFFFFF;
}

void isometric_projection(fdf *fdf,float *x, float *x1, float *y, float *y1, int z, int z1)
{
	int tmp;
	
	tmp = *x;
    *x = (*x - *y) * cos(fdf->angle );//0.8
    *y = (tmp + *y) * sin(fdf->angle) - z;
	tmp = *x1;
	*x1 = (*x1 - *y1) * cos(fdf->angle);//0.8
    *y1 = (tmp + *y1) * sin(fdf->angle) - z1;

	*x = *x + fdf->offsx;
    *x1 = *x1 + fdf->offsx;
    *y = *y + fdf->offsy;
    *y1 = *y1 + fdf->offsy;
}
void rotate(fdf *fdf,float *x, float *x1, float *y, float *y1, int z, int z1)
{ 

    *x = (*x - *y) * 0.5;//0.8
    *y = (*x + *y) * 0.5 - z;
    *x1 = (*x1 - *y1) * 0.5;//0.8
    *y1 = (*x1 + *y1) * 0.5 - z1;

	
	*x = *x + fdf->offsx ;
    *x1 = *x1 + fdf->offsx;
    *y = *y + fdf->offsy;
    *y1 = *y1 + fdf->offsy;
}

void no_projection(fdf *fdf, float *x, float *x1, float *y, float *y1)
{
    *x = *x + fdf->offsx ;
    *x1 = *x1 + fdf->offsx;
    *y = *y + fdf->offsy;
    *y1 = *y1 + fdf->offsy;
}

void bit_rotate(fdf *fdf, float *x, float *x1, float *y, float *y1, int z, int z1)
{
    //bit shift droite revient a diviser par deux et bit shift gauche revient a multiplier par deux (*0.5) >> 1 divise << 1 multiplie 
    /*printf("x = %f, y = %f, x1 = %f, y1 = %f\n", *x, *y, *x1, *y1);
    printf("offsx = %d, offsy = %d\n", fdf->offsx, fdf->offsy);
    */
    *x = (float)(((int)(*x + fdf->offsx) - (int)(*y + fdf->offsy)) >> 1);
    //printf("x = %f, y = %f\n", *x, *y);
    *y = (float)(((int)(*x + fdf->offsx) + (int)(*y + fdf->offsy)) >> 1) - z;
    //oldx = *x1;
    //oldy = *y1;
    *x1 = (float)(((int)(*x1 + fdf->offsx) - (int)(*y1+ fdf->offsy)) >> 1);
    *y1 = (float)(((int)(*x1+ fdf->offsx) + (int)(*y1 + fdf->offsy)) >> 1) - z1;
    /*printf("x = %f, y = %f, x1 = %f, y1 = %f\n", *x, *y, *x1, *y1);
    exit(1);*/
	*x = *x + fdf->offsx ;
    *x1 = *x1 + fdf->offsx;
    *y = *y + fdf->offsy;
    *y1 = *y1 + fdf->offsy;
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

    //zoom
    
    x = x * fdf->zoom;
    x1 = x1 * fdf->zoom;
    y = y * fdf->zoom;
    y1 = y1 * fdf->zoom;
    
    //couleur
    fdf_color(fdf, z, z1);

	/*
    x = x + fdf->offsx;
    x1 = x1 + fdf->offsx;
    y = y + fdf->offsy;
    y1 = y1 + fdf->offsy;
	*/
    // Projection isometrique
	/*   
    x = x + fdf->offsx ;
    x1 = x1 + fdf->offsx;
    y = y + fdf->offsy;
    y1 = y1 + fdf->offsy;
  	*/  
    //isometric_projection(&x,&y,z);
    isometric_projection(fdf,&x,&x1,&y,&y1,z,z1);
    //bit_rotate(fdf,&x,&x1,&y,&y1,z,z1);
    //rotate(fdf,&x,&x1,&y,&y1,z,z1);
    //no_projection(fdf, &x,&x1,&y,&y1);
    //printf("x = %f, x1 = %f, y = %f, y1 = %f\n", x, x1, y, y1);
    //pente delta x et delta y

    
    dx = x1 - x;
    dy = y1 - y;
    //printf("dx = %f, dy = %f\n", dx, dy);
    max = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    dx = dx / max; // si dx plus grand ligne horizontale
    dy = dy / max;  // si dy plus grand ligne verticale
    while((int)(x - x1) || (int)(y - y1))
    {
		//prit l'evoution de x et de x1 ainsi que de y et y1
        //printf("x = %f, x1 = %f, y = %f, y1 = %f\n", x, x1, y, y1);
        if(x <= fdf->win_x || y <= fdf->win_y)
			mlx_pixel_put_img(fdf, x, y, fdf->couleur);
		//mlx_pixel_put(fdf->mlx_ptr, fdf->winmlx_ptr, x, y, fdf->couleur);
		x = x + dx;
		y = y + dy;

    }
    
}

int affichage(fdf *fdf)
{
	int x;
	int y;

    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    
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

	mlx_put_image_to_window(fdf->mlx_ptr, fdf->winmlx_ptr, fdf->mlx_image, 0,0);

       end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution: %f millisecondes\n", cpu_time_used);
    return (0);
}