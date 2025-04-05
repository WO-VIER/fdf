/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:59:54 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/05 18:14:39 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	largeur_ligne(char *line)
{
	char	**split;
	int		largeur;

	if (!line)
		return (-1);
	largeur = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	while (split[largeur] && split[largeur][0] != '\n')
		largeur++;
	free_split(split, NULL);
	return (largeur);
}

int	largeur(t_fdf *fdf, char *file)
{
	int		fd;
	char	*line;
	int		largeur;

	fd = open(file, O_RDONLY);
	if (fd == -1 || !fdf)
		return (-1);
	line = get_next_line(fd);
	largeur = 0;
	fdf->largeur = largeur_ligne(line);
	free(line);
	while (largeur != -1 && fdf->largeur != -1)
	{
		//free(line);
		line = get_next_line(fd);
		if(!line)
			break;
		largeur = largeur_ligne(line);
		if (largeur != fdf->largeur)
			fdf->largeur = -1;
		free(line);
	}
	close(fd);
	if (fdf->largeur == -1)
		write(2, "Error: parsing\n", 15);
	return (fdf->largeur);
}

int	hauter(t_fdf *fdf, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1 || !fdf)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	fdf->hauter = i;
	if (fdf->hauter == 0)
	{
		close(fd);
		write(2, "Error: height parsing\n", 22);
		return (-1);
	}
	close(fd);
	return (i);
}

void	set_z(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->max_z = INT_MIN;
	fdf->min_z = INT_MAX;
	i = 0;
	while (i < fdf->hauter)
	{
		j = 0;
		while (j < fdf->largeur)
		{
			if (fdf->map[i][j] < fdf->min_z)
				fdf->min_z = fdf->map[i][j];
			if (fdf->map[i][j] > fdf->max_z)
				fdf->max_z = fdf->map[i][j];
			j++;
		}
		i++;
	}
}
