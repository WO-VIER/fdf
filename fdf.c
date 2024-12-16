/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:35 by vwautier          #+#    #+#             */
/*   Updated: 2024/12/10 16:15:09 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx_int.h"
#include "minilibx-linux/mlx.h"
//#include "minilibx-linux/libmlx_Linux.a"

int main()
{
    void *init;
    void *window;

    init = mlx_init();
    window = mlx_new_window(init,2048,1536,"FDF");
    int i = 0;
    int j = 0;
    while (i < 2048)
    {
        while(j < 1536)
        {
            mlx_pixel_put(init,window,i,j++,0xFFFFFF);
            j++;
        }
        j = 0;
        i++;
    }
    
    mlx_pixel_put(init,window,0,0,0xFFFFFF);

        mlx_loop(init);

    return 0;
}

