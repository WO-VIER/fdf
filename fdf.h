/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:41:36 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/05 17:31:52 by vwautier         ###   ########.fr       */
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

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_fdf
{
	int		hauter;
	int		largeur;
	int		zoom;
	float	z_angle;
	float	x_angle;
	float	y_angle;
	int		offsx;
	int		offsy;
	int		max_z;
	int		min_z;
	float	z_scale;
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
}			t_fdf;

//rotate.c
void		rotate_x(t_fdf *fdf, float *x, float *y, float *z);
void		rotate_y(t_fdf *fdf, float *x, float *y, float *z);
void		rotate_z(t_fdf *fdf, float *x, float *y, float *z);
void		rotate_point(t_fdf *fdf, float *x, float *y, float *z);
void		classic_isometric(float *x, float *y, float z);

//vue.c
//static void     improved_isometric_projection(fdf *fdf, float *x, float *y,
//static void	mlx_pixel_put_img(fdf *fdf, int x, int y, int color);
int			affichage(t_fdf *fdf);

//static void	draw_line(t_point p, t_point p1, fdf *fdf);

//util_vue.c
void		clear_image(t_fdf *fdf);
int			max_dx_dy(float dx, float dy);
void		fdf_color(t_fdf *fdf, int z, int z1);

//board_util.c
int			largeur(t_fdf *fdf, char *file);
int			hauter(t_fdf *fdf, char *file);
void		set_z(t_fdf *fdf);

//board_free.c
int			free_split(char **split, char *line);
void		clear_board(t_fdf *fdf);
//board.c
int			setup_map(t_fdf *fdf, char *file);

//control.c
int			key_handler(int key, t_fdf *fdf);

//setup.c
int			clear_game(t_fdf *fdf);
int			setup_struct(t_fdf *fdf);
int			setup_fdf(t_fdf *fdf, char *file);

// Nouvelle fonction pour une projection isométrique standard de 42

#endif