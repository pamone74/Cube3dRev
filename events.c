/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:42:50 by schennal          #+#    #+#             */
/*   Updated: 2024/06/08 00:42:50 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	rotate_left(t_data *data)
{
	data->player.angle += ROTATION_ANGLE;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	data->player.delta_x = cos(data->player.angle) * STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle) * STEP_SIZE;
}

void	rotate_right(t_data *data)
{
	data->player.angle -= ROTATION_ANGLE;
	if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	data->player.delta_x = cos(data->player.angle) * STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle) * STEP_SIZE;
}


int	handle_keypress(int key, void *data_game)
{
	t_data	*data;

	data = (t_data *)data_game;
	if (key == ESC)
		terminate_game(data);
	else if (key == W)
		data->keys.w = 1;
	else if (key == S)
		data->keys.s = 1;
	else if (key == A)
		data->keys.a = 1;
	else if (key == D)
	{
		data->keys.d = 1;
	}
		
	else if (key == LEFT)
		data->keys.left = 1;
	else if (key == RIGHT)
		data->keys.right = 1;
	return (0);
}

int	handle_keyrelease(int key, void *data_game)
{
	t_data	*data;

	data = (t_data *)data_game;
	if (key == W)
		data->keys.w = 0;
	else if (key == S)
		data->keys.s = 0;
	else if (key == A)
		data->keys.a = 0;
	else if (key == D)
		data->keys.d = 0;
	else if (key == LEFT)
		data->keys.left = 0;
	else if (key == RIGHT)
		data->keys.right = 0;
	return (0);
}

int	terminate_game(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	mlx_destroy_window(data->window.mlx, data->window.win);
	mlx_destroy_image(data->window.mlx, data->image.img);
	mlx_destroy_image(data->window.mlx, data->mini_map.img);
	free_double_array2(&data->buffer);
	free_memory(data->parse, data);
	exit(0);
}