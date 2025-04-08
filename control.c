/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:20:00 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/08 15:20:09 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* (M_PI / 36.0) = 5 deg */

static void	z_scale(int key, t_fdf *fdf)
{
	if (key == 49)
		fdf->z_scale = fdf->z_scale - 0.1;
	if (key == 50)
		fdf->z_scale = fdf->z_scale + 0.1;
}

static void	zoom(int key, t_fdf *fdf)
{
	if (key == 93 || key == 61)
	{
		fdf->zoom = fdf->zoom + 1;
	}
	if (key == 47 || key == 45)
	{
		if (fdf->zoom != 2)
			fdf->zoom = fdf->zoom - 1;
	}
}

static void	offset(int key, t_fdf *fdf)
{
	if (key == 100 || key == 65363)
		fdf->offsx = fdf->offsx + 10;
	if (key == 97 || key == 65361)
		fdf->offsx = fdf->offsx - 10;
	if (key == 115 || key == 65364)
		fdf->offsy = fdf->offsy + 10;
	if (key == 119 || key == 65362)
		fdf->offsy = fdf->offsy - 10;
}

static void	rotation(int key, t_fdf *fdf)
{
	if (key == 109)
		fdf->z_angle = fdf->z_angle + (M_PI / 36.0);
	if (key == 110)
		fdf->z_angle = fdf->z_angle - (M_PI / 36.0);
	if (key == 65365)
		fdf->x_angle = fdf->x_angle + (M_PI / 36.0);
	if (key == 65366)
		fdf->x_angle = fdf->x_angle - (M_PI / 36.0);
	if (key == 44)
		fdf->y_angle = fdf->y_angle - (M_PI / 36.0);
	if (key == 46)
		fdf->y_angle = fdf->y_angle + (M_PI / 36.0);
}

int	key_handler(int key, t_fdf *fdf)
{
	z_scale(key, fdf);
	zoom(key, fdf);
	offset(key, fdf);
	rotation(key, fdf);
	if (key == 65307)
		clear_game(fdf);
	clear_image(fdf);
	return (0);
}
