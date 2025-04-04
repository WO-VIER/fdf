/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:58:59 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/04 13:00:00 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
int largeur(char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		largeur;
	int  	max;

	fd = open(file, O_RDONLY);
	if(fd == -1)
		return (0);
	i = 0;
	largeur = 0;
	line = get_next_line(fd);
	while(line)
	{
		line = get_next_line(fd);
		printf("%s\n",line);
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
*/

int free_split(char **split,char *line)
{
	int i;

	if(!split)	
		return (1);
	i = 0;
	while(split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
	if(line)
	{
		free(line);
		line = NULL;
	}
	return (0);
}
int largeur_ligne(char *line)
{
	char **split;
	int largeur;
	
	if(!line)
		return (-1);
	largeur = 0;
	split = ft_split(line, ' ');
	if(!split)
		return (-1);
	while(split[largeur] && split[largeur][0] != '\n')
		largeur++;
	free_split(split,line);
	return (largeur);
}

int hauter(fdf *fdf, char *file)
{
    int		fd;
    char	*line;
    int		i;

    fd = open(file, O_RDONLY);
	if(fd == -1 || !fdf)
		return (-1);
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
	fdf->hauter = i;
	if(fdf->hauter == 0)
	{
		close(fd);
		write(2,"Error: number parsing\n",22);
		return (-1);
	}
	close(fd);
	return (i);
}

int largeur(fdf *fdf,char *file)
{
	int fd;
	char *line;
	int largeur;

	fd = open(file, O_RDONLY);
	if(fd == -1 || !fdf)
		return (-1);
	line = get_next_line(fd); 
	largeur = 0;
	fdf->largeur = largeur_ligne(line); //si pas line retourn -1 free(le split dedan et line)
	while(line && largeur!= -1 && fdf->largeur != -1)
	{
		//free(line);
		line = get_next_line(fd);
		if(line)
		{
			largeur = largeur_ligne(line);
			if(fdf->largeur != largeur)
				fdf->largeur = -1;
		}
	}
	close(fd);
	if(fdf->largeur == -1)
		write(2,"Error: parsing\n",15);
	return (fdf->largeur);
}


int make_tab(fdf *fdf)
{
	int i;
	fdf->map = (int **)malloc(sizeof(int *) * (fdf->hauter + 1));
	if(!fdf->map)
		return (1);
	fdf->map[fdf->hauter] = NULL;
	i = 0;	
	while (i < fdf->hauter)
	{
		fdf->map[i] = malloc(sizeof(int) * fdf->largeur);
		if(!fdf->map[i])
		{
			while(i > 0)
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
int error_map(int fd)
{
	close(fd);
	return (1);
}
int populate_map(fdf *fdf, char *file, int fd)
{
	char **split;
	char*line;
	int i;
	int j;

	i = 0;
	while(i < fdf->hauter)
	{
		line = get_next_line(fd);
		if(!line)
			return (1);
		split = ft_split(line, ' ');
		if(!split)
			return(1);
		j = 0;
		while(split[j] && split[j][0] != '\n' && j < fdf->largeur)
		{
			fdf->map[i][j] = ft_atoi(split[j]);
			j++;
		}
		free_split(split,line);
		i++;
	}
	return (0);
}

void print_tab(fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while(i < fdf->hauter)
	{
		j = 0;
		while(j < fdf->largeur)
			printf("%3d",fdf->map[i][j++]);
		printf("\n");
		i++;
	}
}
void clear_board(fdf *fdf)
{
	int i;
	
	i = 0;
	if(!fdf )
		return;
	
	while(fdf->map && i < fdf->hauter)
	{
		free(fdf->map[i]);
		fdf->map[i++] = NULL;
	}

	free(fdf->map);
	fdf->map = NULL;
	
}

int clear_game(fdf *fdf)
{
	if(!fdf)
		return (1);
	if(fdf->map)
		clear_board(fdf);
	if(fdf->mlx_image)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_image);
		fdf->mlx_image = NULL;
	}
	if(fdf->winmlx_ptr)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->winmlx_ptr);
		fdf->winmlx_ptr = NULL;
	}
	if(fdf->mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		fdf->mlx_ptr = NULL;
	}
	free(fdf);
	fdf = NULL;
	exit(1);
}

int verif_path(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if(fd == -1)
	{
		write(2,"Error: file not found\n",22);
		return (1);
	}
	close(fd);
	return (0);
}

void set_z(fdf *fdf)
{
	int i;
	int j;

	fdf->max_z = INT_MIN;
	fdf->min_z = INT_MAX;

	i = 0;
	while(i < fdf->hauter)
	{
		j = 0;
		while(j < fdf->largeur)
		{
			if(fdf->map[i][j] < fdf->min_z)
				fdf->min_z = fdf->map[i][j];
			if(fdf->map[i][j] > fdf->max_z)
				fdf->max_z = fdf->map[i][j];
			j++;
		}
		i++;
	}
}
int setup_map(fdf *fdf, char *file)
{
	int fd;
	fd = open(file, O_RDONLY);
	
	if(!fdf || fd == -1)
		return (1);
	if(make_tab(fdf) || populate_map(fdf, file, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);

}

void calculate_zoom(fdf *fdf)
{
    int zoom_x;
    int zoom_y;
    int margin = 100; // Marge en pixels autour de la carte
    
    // Initialisation par défaut pour garantir une valeur définie
    fdf->z_scale = 1.0f;
    
    // Calcul initial - combien de fois la carte peut tenir dans la fenêtre
    zoom_x = (fdf->win_x - margin * 2) / fdf->largeur;
    zoom_y = (fdf->win_y - margin * 2) / fdf->hauter;
    
    // Utiliser la plus petite valeur pour s'assurer que tout est visible
    fdf->zoom = (zoom_x < zoom_y) ? zoom_x : zoom_y;
    
    // Assurer un zoom minimum
    if (fdf->zoom < 2)
        fdf->zoom = 2;
    
    // Ajuster le facteur z_scale en fonction du zoom
    if (fdf->max_z != fdf->min_z)
    {
        int height_range = fdf->max_z - fdf->min_z;
        
        // Déterminer le facteur d'échelle vertical optimal
        fdf->z_scale = fdf->zoom * 0.4f;
        
        // Limiter la hauteur maximale pour éviter la distorsion excessive
        if (fdf->z_scale * height_range > fdf->win_y / 2)
            fdf->z_scale = (fdf->win_y / 2) / (float)height_range;
    }
    // else - la valeur par défaut 1.0f est déjà définie
    
    printf("Zoom calculé: %d, Z-scale: %.2f\n", fdf->zoom, fdf->z_scale);
}

void set_zoom(fdf *fdf)
{
	int total;

	if(!fdf)
		return;
	
	total = fdf->hauter * fdf->largeur;
	if (total > 100000)
        fdf->zoom = 2;
    else if (total > 5000)
        fdf->zoom = 3;
    else if (total > 500)
        fdf->zoom = 20;
    else
        fdf->zoom = 20;
	
	printf("Zoom = %d\n", fdf->zoom);
	
}

void calculate_zoom_80_percent(fdf *fdf)
{
	int range;
    float zoom_x;
    float zoom_y;
	
	zoom_x = (fdf->win_x * 0.8f) / fdf->largeur;
	zoom_y = (fdf->win_y * 0.8f) / fdf->hauter;
	if(zoom_x > zoom_y)
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
        range = fdf->max_z - fdf->min_z;
        if (range > 50)
            fdf->z_scale = 0.1f;
        else if (range > 20)
            fdf->z_scale =  0.2f;
        else if (range > 5)
            fdf->z_scale = 0.3f;
		else
			fdf->z_scale =  0.6f;
    }
	printf("z-scale = %f Zoom = %d\n",fdf->z_scale, fdf->zoom);
}

int setup_struct(fdf *fdf)
{
	ft_memset(fdf->key, 0, sizeof(fdf->key));
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

int setup_fdf(fdf *fdf, char *file)
{
	
	if(!fdf || verif_path(file)) //ok si les  deux a 1 error
		return (1);
    if(hauter(fdf,file) == -1 || largeur(fdf,file) == -1 || setup_map(fdf,file) == 1)
		return (1);
	printf("hauter = %d largeur = %d\n", fdf->hauter, fdf->largeur);
	set_z(fdf);
	calculate_zoom_80_percent(fdf);
	fdf->mlx_ptr = mlx_init();
	if(!fdf->mlx_ptr)
		return (1);
    fdf->winmlx_ptr = mlx_new_window(fdf->mlx_ptr,fdf->win_x,fdf->win_y,"FDF");
	if(!fdf->winmlx_ptr)
		return (1);
    fdf->mlx_image = mlx_new_image(fdf->mlx_ptr, fdf->win_x, fdf->win_y);
	if (!fdf->mlx_image)
		return (1);
	fdf->ptr_image = mlx_get_data_addr(fdf->mlx_image,&fdf->bits_per_pixel,&fdf->line_length,&fdf->endian);//Fill automatiquement win_x * 4 (32 bits) = line_length 
	if(!fdf->ptr_image)
		return (1);
	return (0);
}