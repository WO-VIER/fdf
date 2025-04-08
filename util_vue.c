/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_vue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:50:17 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/08 15:19:32 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_fdf *fdf)
{
	ft_memset(fdf->ptr_image, 0, fdf->line_length * fdf->win_y);
	mlx_clear_window(fdf->mlx_ptr, fdf->winmlx_ptr);
	affichage(fdf);
}

void	fdf_color(t_fdf *fdf, int z, int z1)
{
	if (z || z1)
		fdf->couleur = 0xEEAECA;
	else
		fdf->couleur = 0xFFFFFF;
}

int	max_dx_dy(float dx, float dy)
{
	if (dx > dy)
		return (dx);
	return (dy);
}
