/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:30:17 by schennal          #+#    #+#             */
/*   Updated: 2024/06/07 21:35:52 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int init_map(t_data *data)
{
    int i;

    data->window.map_width = data->parse->column * 64;
	data->window.map_height = data->parse->row * 64;
	data->ray.data = data;
    data->angle_increment = (FOV * PI / 180) / WIN_W;
    data->buffer = (unsigned int **)ft_calloc(WIN_H + 1, sizeof(unsigned int *));
    i = -1;
    while(++i < WIN_H)
        data->buffer[i] = (unsigned int *)ft_calloc(WIN_W, sizeof(unsigned int));
    return (0);
}



int	player_pos(t_data *data, int i, int j)
{
	data->player.x_pos = j * 64.00 + 32.00;
	data->player.y_pos = i * 64.00 + 32.00;
	if (data->parse->map[i][j] == 'E')
		data->player.angle = 0;
	if (data->parse->map[i][j] == 'N')
		data->player.angle = PI / 2;
	else if (data->parse->map[i][j] == 'W')
		data->player.angle = PI;
	else if (data->parse->map[i][j] == 'S')
		data->player.angle = 3 * PI / 2;
	data->parse->map[i][j] = '0';
	return (0);
}

int	init_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->parse->num_lines)
	{
		j = -1;
		while (data->parse->map[i][++j])
		{
			if (data->parse->map[i][j] == 'N' 
					|| data->parse->map[i][j] == 'S' 
					|| data->parse->map[i][j] == 'E'
					|| data->parse->map[i][j] == 'W')
				return (player_pos(data, i, j));
		}
	}
	return (0);
}

/// ================================= init Keys for the player's movemement ==============================

/*
	Initializing the intial positions of the player before the start of the game
*/
int	init_keys(t_data *data)
{
	data->keys.w = 0;// W key
	data->keys.a = 0;// A key
	data->keys.s = 0;// S key
	data->keys.d = 0;// D key 
	data->keys.left = 0;// The left key
	data->keys.right = 0;// the right keys
	return (0);
}