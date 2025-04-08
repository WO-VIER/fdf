/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:35 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/08 15:20:06 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(*fdf));
	if (!fdf)
		exit(1);
	setup_struct(fdf);
	if (argc == 2)
	{
		if (setup_fdf(fdf, argv[1]))
			clear_game(fdf);
	}
	else
	{
		write(2, "Error : number of arguments\n", 28);
		write(2, "Usage : ./fdf <filename>\n", 25);
		free(fdf);
		exit(1);
	}
	mlx_key_hook(fdf->winmlx_ptr, key_handler, fdf);
	mlx_hook(fdf->winmlx_ptr, 17, 0, clear_game, fdf);
	affichage(fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
