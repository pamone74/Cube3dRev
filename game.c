/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:34:25 by schennal          #+#    #+#             */
/*   Updated: 2024/06/08 00:00:49 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	init_buffer(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			data->buffer[i][j] = WHITE;
			j++;
		}
		i++;
	}
	return (0);
}

void init_gun(t_data *data)
{
	int i = 0;
	int y = 267;
	while (++y < WIN_H)
	{
		int x = 200;
		while (++x < WIN_W - 70)
		{
			data->buffer[y][x + 70] = data->gun.addr[i * WIN_W + x];
		}
		i++;
	}	
}

// converting th FOV to radioan FOV * PI / 180 and by dividing it by 2 we get the half of FOV in radians
// this means that the rays will cast from the center of player's field of view to the edge
// the formula to convert the degree into radian is [radians = degrees * PI/180]
// in trig, the angle ranges from 0 to 2PI and we need to make sure we are in the range

int	init_rays(t_data *data)
{
	data->ray.angle = data->player.angle + (FOV * PI / 180) / 2.0;
	if (data->ray.angle > 2 * PI)
		data->ray.angle -= 2 * PI;
	if (data->ray.angle < 0)
		data->ray.angle += 2 * PI;
	data->ray.x = data->player.x_pos;
	data->ray.y = data->player.y_pos;
	return (0);
}
void	init_game(t_data *data)
{
	init_rays(data);
	init_buffer(data);
	init_gun(data);
	init_minimap(data, data->parse->map, data->parse->column * 8,
		data->parse->row * 8);
}
/*
function handles the main loop of the game, which includes raycasting to render the game scene, correcting for the fish-eye effect, 
drawing the game scene, and updating the game window with the rendered images
*/
int	let_the_game_begin(t_data *data, t_ray *ray)
{
	int	i;
	int	x_intercept;
	int	y_intercept;
    //(void)ray;
	i = -1;
	init_game(data); //start_initialiser
	while (++i < WIN_W)
	{
		h_raycast(ray, data->parse->map);
		x_intercept = ray->x_intercept;
		y_intercept = ray->y_intercept;
		v_raycast(ray, data->parse->map);
		shortest_ray(data, ray, x_intercept, y_intercept);
		fix_fish_eye(ray, data->player.angle);
		init_wall(ray, data, i);
        draw_ray(data, ray->x / 64 * 8, ray->y / 64 * 8, ray->intercepts);
		ray->angle -= data->angle_increment;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		if (data->ray.angle < 0)
			data->ray.angle += 2 * PI;
	}
	draw_game(data);
    mlx_put_image_to_window(data->window.mlx, data->window.win,
		data->image.img, 0, 0);
	mlx_put_image_to_window(data->window.mlx, data->window.win,
		data->mini_map.img, 0, 0);
	return (0);
}


