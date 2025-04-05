/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vue.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:56:38 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/05 16:37:09 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	improved_isometric_projection(t_fdf *fdf, float *x, float *y, int z)
{
	float	z_scaled;
	float	center_x;
	float	center_y;

	z_scaled = (z * (fdf->zoom * fdf->z_scale));
	*x *= fdf->zoom;
	*y *= fdf->zoom;
	center_x = (fdf->largeur * fdf->zoom) / 2.0f;
	center_y = (fdf->hauter * fdf->zoom) / 2.0f;
	*x -= center_x;
	*y -= center_y;
	rotate_point(fdf, x, y, &z_scaled);
	classic_isometric(x, y, z_scaled);
	*x += fdf->win_x / 2 + fdf->offsx;
	*y += fdf->win_y / 2 + fdf->offsy;
}

static void	mlx_pixel_put_img(t_fdf *fdf, int x, int y, int color)
{
	char	*addr;

	if ((x >= 0 && y >= 0) && (x < fdf->win_x && y < fdf->win_y))
	{
		addr = fdf->ptr_image + (y * fdf->line_length + x * (fdf->bits_per_pixel
					/ 8));
		*(unsigned int *)addr = color;
	}
}

static void	draw_line(t_point p, t_point p1, t_fdf *fdf)
{
	float	dx;
	float	dy;
	int		max;
	int		z;
	int		z1;

	z = fdf->map[(int)p.y][(int)p.x];
	z1 = fdf->map[(int)p1.y][(int)p1.x];
	fdf_color(fdf, z, z1);
	improved_isometric_projection(fdf, &p.x, &p.y, z);
	improved_isometric_projection(fdf, &p1.x, &p1.y, z1);
	dx = p1.x - p.x;
	dy = p1.y - p.y;
	max = max_dx_dy(fabs(dx), fabs(dy));
	dx = dx / max;
	dy = dy / max;
	while ((int)(p.x - p1.x) || (int)(p.y - p1.y))
	{
		if ((int)p.x <= fdf->win_x || (int)p.y <= fdf->win_y)
			mlx_pixel_put_img(fdf, (int)p.x, (int)p.y, fdf->couleur);
		p.x = p.x + dx;
		p.y = p.y + dy;
	}
}

static void	process_point(int x, int y, t_fdf *fdf)
{
	t_point	start;
	t_point	end;

	if (x < fdf->largeur - 1)
	{
		start.x = x;
		start.y = y;
		end.x = x + 1;
		end.y = y;
		draw_line(start, end, fdf);
	}
	if (y < fdf->hauter - 1)
	{
		start.x = x;
		start.y = y;
		end.x = x;
		end.y = y + 1;
		draw_line(start, end, fdf);
	}
}

int	affichage(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->hauter)
	{
		x = 0;
		while (x < fdf->largeur)
		{
			process_point(x, y, fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->winmlx_ptr,
		fdf->mlx_image, 0, 0);
	return (0);
}
