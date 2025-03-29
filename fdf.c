/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:35 by vwautier          #+#    #+#             */
/*   Updated: 2025/02/07 16:16:42 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//#include "minilibx-linux/libmlx_Linux.a"
/*
** -------------------- recourses ----------------------------
** -------------- 3D -----------------------------------------
**  x` = (x - y) * cos(angle);
**  y` = (x + y) * sin(angle) - z;
** -------------------------------------------------------------
**  ------ mlx_function ---------------------------------------
**  void *mlx_ptr;
**  void *win_ptr;
**
**  mlx_ptr = mlx_init();
**  win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");
**
**  mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)y, #color);
**
**  mlx_key_hook(win_ptr, deal_key, NULL);
**  mlx_loop(mlx_ptr);
** --------------------------------------------------------------
** ------ deal_key prototype ----------------------------------
**  int  deal_key(int key, void *data);
** --------------------------------------------------------------
** colors:
**  white = 0xffffff
**  red = 0xe80c0c
** ----------------------------
** frameworks:
**  -framework OpenGL -framework AppKit
-----------------------------------------------------------------------------------------

** -------------- program structure ----------------------
** 1. read file
**          - get height(how many lines) of text
**          - get width(how many numbers in line)
**          - allocate memory for **int by using width and height (look your ft_strsplit() )
**          - read file and write number into **int matrix by using ft_strsplit() and atoi()
**          - ps: ft_wdcounter(line, ' ');  is a function witch count words in line look your ft_strsplit( )

** -------------------------------------
** 2. drawing line function (google Bresenham algorithm)
**             - find by how much we need to increase x and by how much we need to increase y
**                          by using float. Example:
**                                                       x = 2;           x1 = 4;
**                                                       y = 2;           y1 = 6;
**                                                       steps for x: 2
**                                                       steps for y: 4
**                          that means that y should grow 2 times faster than x
**                          every loop step: y += 1 and x += 0.5
**                          after 4 steps x and y will be equal with x1, y1
**                                             real x:y                   x:y                      pixels:    
**                    start:               2.0 : 2.0                  2:2                          .
**                    step1:             2.5 : 3.0                  2:3                          .
**                    step2:             3.0 : 4.0                  3:4                           .
**                    step3:             3.5 : 5.0                  3:5                           . 
**                    step4:             4.0 : 6.0                  4:6                            .
**
**                        that works because (float)2.5 turns to (int)2 in func. mlx_pixel_put()
** ------------------------------------------
** 3. function which draws lines between every dot
**                     - example:
**                                   0--      0--      0--      0
**                                    |         |         |          |
**                                   0--     10--   10--     0
**                                    |         |         |          |
**                                   0--     10--   10--     0
**                                    |         |         |          |
**                                   0--      0--     0--       0
**                                '--' and '|' are lines between dots 
**                              every dot has two lines (right and down):             0--
**                                                                                                                    |
** ----------------
** 4. adding 3D
**        - change coordinates by using isometric formulas:
**              x` = (x - y) * cos(angle)
**              y` = (x + y) * sin(angle) - z
**        - x` and y` are coordinates in 3D format (default angle 0.8)
** ----------------
** 5. adding bonuses (move, rotation, zoom)
**        - when you press button on keyboard the func. mlx_key_hook(win_ptr, deal_key, NULL);
**                   call the func. deal_key.
**        - In the deal key func. you have to change some parameters, clear the window with
**                   mlx_clear_window(mlx_ptr, win_ptr); and redraw the picture
** ----------------
** 6. error handling
**          - check if argc == 2
**          - check if file exists: fd = open(file_name, O_RDONLY)
**                         fd should be more than 0
** ----------------
** 7. fix leaks
**         - type leaks a.out or leaks fdf in your shell
*/
/*
int hauter(char *file)
{
    int		fd;
    char	*line;
    int		i;

    fd = open(file, O_RDONLY);
	i = 0;


	while(1)
	{
		line = get_next_line(fd);
		if (line)
		{
			free(line);
			i++;
		}
		else
			break;
	}

	return (i);
}

int largeur(char *file)
{
    int		fd;
    char	*line;
    int		i;
	int		largeur;
    int     first;

    fd = open(file, O_RDONLY);
	i = 0;
	largeur = 0;
	line = get_next_line(fd);
    if(line)
	{
		while (line[i])
		{
			if(line[i] != ' ' && line[i] != '\n')
				largeur++;
			i++;	
		}
		free(line);
	}
    return (largeur);
}
*/
void test_fdf(fdf *fdf)
{	//fdf = malloc(sizeof(fdf));

    fdf->mlx_ptr = mlx_init();
    fdf->winmlx_ptr = mlx_new_window(fdf->mlx_ptr,900,600,"FDF");
    /*
    int i = 0;
    int j = 0;
    while (i < 900)
    {
        while(j < 600)
        {
            mlx_pixel_put(fdf->mlx_ptr,fdf->winmlx_ptr,i,j++,0xFFFFFF);
            j++;
        }
        j = 0;
        i++;
    }*/
   bresenham(0,0,900,600,fdf);
    mlx_loop(fdf->mlx_ptr);
}

	

int main()
{
    int i = 0 ;
    fdf *fdf;

    fdf = malloc(sizeof(*fdf));
    setup_fdf(fdf, "test_maps/42.fdf");

   /*
    if (!fdf)
    {
        printf("malloc error\n");
        return 0;
    }
    
    setup_fdf(fdf, "test_maps/42.fdf");
    
    if(fdf->map)
    {
        while (fdf->map[i] && i < fdf->hauter)
        {
            free(fdf->map[i]);
            i++;
        }
    }
    free(fdf->map);
    free(fdf);
    */ 
   // 450 - ( 47 )
    fdf->win_x = 900;
    fdf->win_y = 600;
    fdf->zoom = 20;
    fdf->angle = 0.523599;
	//fdf->z = 0;
	//fdf->offsx = (fdf->win_x / 2) * fdf->zoom; 
	//fdf->offsy = (fdf->win_y / 2) * fdf->zoom;
	//printf("Win x : %d Win y : %d \n", fdf->win_x /2, fdf->win_y/2);
    fdf->offsx = ((fdf->win_x / 2) - ((fdf -> largeur * fdf->zoom) / 2));
    fdf->offsy =  ((fdf->win_y / 2) - ((fdf -> hauter * fdf->zoom) / 2));
   	printf("OFFx : %d OFFy y : %d \n", fdf->offsx, fdf->offsy);
	fdf->mlx_ptr = mlx_init();
    fdf->winmlx_ptr = mlx_new_window(fdf->mlx_ptr,fdf->win_x,fdf->win_y,"FDF");
    fdf->mlx_image = mlx_new_image(fdf->mlx_ptr, fdf->win_x, fdf->win_y);
	//fdf->bits_per_pixel = 32;
	fdf->ptr_image = mlx_get_data_addr(fdf->mlx_image,&fdf->bits_per_pixel,&fdf->line_length,&fdf->endian);
	//printf("Bit per pixel :%d", fdf->bits_per_pixel);
	// 900 largeur 19 600 hauter 11

    //test_fdf(fdf);
    //affichage(fdf);
    mlx_key_hook(fdf->winmlx_ptr,key_handler,fdf);
	mlx_hook(fdf->winmlx_ptr, 17, 0,clear_game,fdf);
	mlx_hook(fdf->winmlx_ptr, 17, 0,clear_game,fdf);
	//mlx_hook(fdf->winmlx_ptr, 12, 0,affichage,fdf);
    //mlx_clear_window(fdf->mlx_ptr,fdf->winmlx_ptr);
    //affichage(fdf);
    mlx_loop(fdf->mlx_ptr);
    
    return 0;
}