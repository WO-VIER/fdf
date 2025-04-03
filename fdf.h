/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:41:36 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/03 23:49:04 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_fdf
{
	int		key[256];
	int		hauter;
	int		largeur;
	int		zoom;
	double	z_angle;
	double	x_angle;
	double	y_angle;
	int		offsx;
	int		offsy;
	int		max_z;
	int		min_z;
	double	z_scale;
	int		couleur;
	int		win_x;
	int		win_y;
	int		**map;
	void	*mlx_ptr;
	void	*winmlx_ptr;
	void	*mlx_image;
	char	*ptr_image;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			fdf;

// Nouvelle fonction pour une projection isométrique standard de 42
void		isometric_projection_42(fdf *fdf, float *x, float *x1, float *y,
				float *y1, int z, int z1);

void		iso_normal(fdf *fdf, float *x, float *x1, float *y, float *y1,
				int z, int z1);
void		draw_center_cross(fdf *fdf);
void		isometric_projection2(fdf *fdf, float *x, float *x1, float *y,
				float *y1, int z, int z1);
void		print_tab(fdf *fdf);
int			verif_path(char *file);
int			free_split(char **spli, char *line);
int			key_release(int key, fdf *fdf);
int			loop_handler(fdf *fdf);
void		z_scale(int key, fdf *fdf);
int			hauter(fdf *fdf, char *file);
int			largeur(fdf *fdf, char *file);
int			setup_map(fdf *fdf, char *file);
int			setup_fdf(fdf *fdf, char *file);
void		test_fdf(fdf *fdf);
void		bresenham(float x, float y, float x1, float y1, fdf *fdf);
void		bresenham2(int x, int y, int x1, int y1, fdf *fdf);
void		isometric_projection(fdf *fdf, float *x, float *x1, float *y,
				float *y1, int z, int z1);

int			affichage(fdf *fdf);
int			key_handler(int key, fdf *fdf);
int			clear_game(fdf *fdf);
void		no_projection(fdf *fdf, float *x, float *x1, float *y, float *y1);
void		fdf_color(fdf *fdf, int z, int z1);
void		mlx_pixel_put_img(fdf *fdf, int x, int y, int color);

#endif