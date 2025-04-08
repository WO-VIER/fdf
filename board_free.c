/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:04:28 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/08 15:20:21 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_split(char **split, char *line)
{
	int	i;

	if (!split)
		return (1);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (0);
}

void	clear_board(t_fdf *fdf)
{
	int	i;

	i = 0;
	if (!fdf)
		return ;
	while (fdf->map && i < fdf->hauter)
	{
		free(fdf->map[i]);
		fdf->map[i++] = NULL;
	}
	free(fdf->map);
	fdf->map = NULL;
}
