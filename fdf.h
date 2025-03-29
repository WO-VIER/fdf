/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:41:36 by vwautier          #+#    #+#             */
/*   Updated: 2025/02/07 21:53:44 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx_int.h"
#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_fdf
{
    int     hauter;
    int     largeur;
    int     zoom;
    double  angle;
    int     offsx;
    int     offsy;
    int     couleur;
    int     win_x;
    int     win_y;
    int     **map;
    void    *mlx_ptr;
    void    *winmlx_ptr;
	void	*mlx_image;
	char	*ptr_image;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} fdf;

int hauter(char *file);
int largeur(char *file);
void setup_map(fdf *fdf, char *file);
void setup_fdf(fdf *fdf, char *file);
void test_fdf(fdf *fdf);
void bresenham(float x, float y, float x1, float y1, fdf *fdf);
void isometric_projection(fdf *fdf,float *x, float *x1, float *y, float *y1, int z, int z1);
int	affichage(fdf *fdf);
int key_handler(int key,fdf *fdf);
int clear_game(fdf *fdf);
void no_projection(fdf *fdf, float *x, float *x1, float *y, float *y1);
void fdf_color(fdf *fdf, int z, int z1);