/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:58:59 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/05 17:45:53 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	clear_game(t_fdf *fdf)
{
	if (!fdf)
		return (1);
	if (fdf->map)
		clear_board(fdf);
	if (fdf->mlx_image)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_image);
		fdf->mlx_image = NULL;
	}
	if (fdf->winmlx_ptr)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->winmlx_ptr);
		fdf->winmlx_ptr = NULL;
	}
	if (fdf->mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		fdf->mlx_ptr = NULL;
	}
	free(fdf);
	fdf = NULL;
	exit(0);
}

static int	verif_path(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error: file not found\n", 22);
		return (1);
	}
	close(fd);
	return (0);
}

static void	calculate_zoom_80_percent(t_fdf *fdf)
{
	float	zoom_x;
	float	zoom_y;

	zoom_x = (fdf->win_x * 0.8f) / fdf->largeur;
	zoom_y = (fdf->win_y * 0.8f) / fdf->hauter;
	if (zoom_x > zoom_y)
		fdf->zoom = (int)(zoom_y);
	else
		fdf->zoom = (int)(zoom_x);
	if (fdf->zoom < 2)
		fdf->zoom = 2;
	else if (fdf->zoom > 50)
		fdf->zoom = 50;
	fdf->z_scale = 1.0f;
	if (fdf->max_z != fdf->min_z)
	{
		if (fdf->max_z - fdf->min_z > 50)
			fdf->z_scale = 0.1f;
		else if (fdf->max_z - fdf->min_z > 20)
			fdf->z_scale = 0.2f;
		else if (fdf->max_z - fdf->min_z > 5)
			fdf->z_scale = 0.3f;
		else
			fdf->z_scale = 0.6f;
	}
}

int	setup_struct(t_fdf *fdf)
{
	fdf->hauter = 0;
	fdf->largeur = 0;
	fdf->zoom = 0;
	fdf->z_angle = 0.0f;
	fdf->x_angle = 0.0f;
	fdf->y_angle = 0.0f;
	fdf->offsx = 0;
	fdf->offsy = 0;
	fdf->max_z = 0;
	fdf->min_z = 0;
	fdf->z_scale = 0.0f;
	fdf->couleur = 0;
	fdf->win_x = 800;
	fdf->win_y = 600;
	fdf->map = NULL;
	fdf->mlx_ptr = NULL;
	fdf->winmlx_ptr = NULL;
	fdf->mlx_image = NULL;
	fdf->ptr_image = NULL;
	fdf->bits_per_pixel = 0;
	fdf->line_length = 0;
	fdf->endian = 0;
	return (0);
}

int	setup_fdf(t_fdf *fdf, char *file)
{
	if (!fdf || verif_path(file))
		return (1);
	if (hauter(fdf, file) == -1 || largeur(fdf, file) == -1 || setup_map(fdf,
			file) == 1)
		return (1);
	set_z(fdf);
	calculate_zoom_80_percent(fdf);
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		return (1);
	fdf->winmlx_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_x, fdf->win_y,
			"FDF");
	if (!fdf->winmlx_ptr)
		return (1);
	fdf->mlx_image = mlx_new_image(fdf->mlx_ptr, fdf->win_x, fdf->win_y);
	if (!fdf->mlx_image)
		return (1);
	fdf->ptr_image = mlx_get_data_addr(fdf->mlx_image, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	if (!fdf->ptr_image)
		return (1);
	return (0);
}
