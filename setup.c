/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:58:59 by vwautier          #+#    #+#             */
/*   Updated: 2025/02/06 15:16:16 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int hauter(char *file)
{
    int		fd;
    char	*line;
    int		i;

    fd = open(file, O_RDONLY);
	i = 0;


	while(1)
	{
		line = get_next_line(fd);
		if (line)
		{
			free(line);
			i++;
		}
		else
			break;
	}
	close(fd);
	return (i);
}

int largeur(char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		largeur;
	int     first;

	fd = open(file, O_RDONLY);
	if(fd == -1)
		return (0);
	i = 0;
	largeur = 0;
	while(1)
	{
		line = get_next_line(fd);
		if (line)
		{
			if(i == 0)
			{
				while(line[i])
				{
					if (line[i] != ' ' && line[i] != '\n')
						largeur++;
					i++;
				}
			}
			free(line);
		}
		else
			break;
	}
	close(fd);
	return (largeur);
}

void setup_map(fdf *fdf, char *file)
{
    int fd;
    char *line;
    char **split;
    int i;
    int j;

    fdf->map = (int **)malloc(sizeof(int *) * (fdf->hauter+1));
    fd = open(file, O_RDONLY);

    i = 0;
    while (1)
    {
        line = get_next_line(fd);
        if(line)
        {
            split = ft_split(line, ' ');
            
            fdf->map[i] = malloc(sizeof(int) * fdf->largeur);
            j = 0;
            while(split[j] && split[j] != "\n")
            {
                fdf->map[i][j] = ft_atoi(split[j]);
				printf("%3d",fdf->map[i][j]);
                free(split[j]);
                j++;
            }
			printf("\n");
            free(split[j]);
            free(split);
            free(line);
            i++;
        }
        else
            break;
    }
    close(fd);
}

int clear_game(fdf *fdf)
{
	int i;

	i = 0;
	// 19 0 - 18
	while(i < fdf->hauter)
	{
		free(fdf->map[i]);
		//fdf->map[i] = NULL;
		i++;
	}
	free(fdf->map);
	fdf->map = NULL;

	mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_image);
	mlx_destroy_window(fdf->mlx_ptr, fdf->winmlx_ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	//free(fdf->ptr_image);
	//fdf->ptr_image = NULL;
	//free(fdf->mlx_image);
	fdf->mlx_image = NULL;
	//free(fdf->mlx_ptr);
	fdf->mlx_ptr = NULL;
	free(fdf);
	fdf = NULL;

	exit(0);
}


void setup_fdf(fdf *fdf, char *file)
{
    fdf->hauter = hauter(file);
    fdf->largeur = largeur(file);
    printf("hauter: %d\n", fdf->hauter);
    printf("largeur: %d\n", fdf->largeur);
    setup_map(fdf, file);
}