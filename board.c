/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:03:01 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/08 15:20:14 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	make_tab(t_fdf *fdf)
{
	int	i;

	fdf->map = (int **)malloc(sizeof(int *) * (fdf->hauter + 1));
	if (!fdf->map)
		return (1);
	fdf->map[fdf->hauter] = NULL;
	i = 0;
	while (i < fdf->hauter)
	{
		fdf->map[i] = malloc(sizeof(int) * fdf->largeur);
		if (!fdf->map[i])
		{
			while (i > 0)
			{
				i--;
				free(fdf->map[i]);
				fdf->map[i] = NULL;
			}
			free(fdf->map);
			fdf->map = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	populate_map(t_fdf *fdf, int fd)
{
	char	**split;
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (i < fdf->hauter)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		split = ft_split(line, ' ');
		if (!split)
			return (1);
		j = 0;
		while (split[j] && split[j][0] != '\n' && j < fdf->largeur)
		{
			fdf->map[i][j] = ft_atoi(split[j]);
			j++;
		}
		free_split(split, line);
		i++;
	}
	return (0);
}

int	setup_map(t_fdf *fdf, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (!fdf || fd == -1)
		return (1);
	if (make_tab(fdf) || populate_map(fdf, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
