/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:26:35 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/05 16:54:37 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_fdf *fdf, float *x, float *y, float *z)
{
	float	temp_y;
	float	temp_z;

	temp_y = *y;
	temp_z = *z;
	*y = temp_y * cos(fdf->x_angle) - temp_z * sin(fdf->x_angle);
	*z = temp_y * sin(fdf->x_angle) + temp_z * cos(fdf->x_angle);
}

void	rotate_y(t_fdf *fdf, float *x, float *y, float *z)
{
	float	temp_x;
	float	temp_z;

	temp_x = *x;
	temp_z = *z;
	*x = temp_x * cos(fdf->y_angle) + temp_z * sin(fdf->y_angle);
	*z = -temp_x * sin(fdf->y_angle) + temp_z * cos(fdf->y_angle);
}

void	rotate_z(t_fdf *fdf, float *x, float *y, float *z)
{
	float	temp_x;
	float	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = temp_x * cos(fdf->z_angle) - temp_y * sin(fdf->z_angle);
	*y = temp_x * sin(fdf->z_angle) + temp_y * cos(fdf->z_angle);
}

void	classic_isometric(float *x, float *y, float z)
{
	float	old_x;
	float	old_y;

	old_x = *x;
	old_y = *y;
	*x = (old_x - old_y) * cos(M_PI / 6);
	*y = (old_x + old_y) * sin(M_PI / 6) - z;
}

void	rotate_point(t_fdf *fdf, float *x, float *y, float *z)
{
	if (fdf->x_angle != 0)
		rotate_x(fdf, x, y, z);
	if (fdf->y_angle != 0)
		rotate_y(fdf, x, y, z);
	if (fdf->z_angle != 0)
		rotate_z(fdf, x, y, z);
}
