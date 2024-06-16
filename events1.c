/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:44:27 by schennal          #+#    #+#             */
/*   Updated: 2024/06/08 00:42:06 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static void	move_forward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos + data->player.delta_x * 2) / 64;
	y = (int)(data->player.y_pos + data->player.delta_y * 2) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	x = (int)(data->player.x_pos + data->player.delta_x) / 64;
	y = (int)(data->player.y_pos + data->player.delta_y) / 64;
	if (data->parse->map[(int)data->player.y_pos / 64][x] == '1'
		&& data->parse->map[y][(int)data->player.x_pos / 64] == '1')
		return ;
	data->player.y_pos += data->player.delta_y;
	data->player.x_pos += data->player.delta_x;
}

static void	move_backward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos - data->player.delta_x * 2) / 64;
	y = (int)(data->player.y_pos - data->player.delta_y * 2) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	x = (int)(data->player.x_pos - data->player.delta_x) / 64;
	y = (int)(data->player.y_pos - data->player.delta_y) / 64;
	if (data->parse->map[(int)data->player.y_pos / 64][x] == '1'
		&& data->parse->map[y][(int)data->player.x_pos / 64] == '1')
		return ;
	data->player.y_pos -= data->player.delta_y;
	data->player.x_pos -= data->player.delta_x;
}

static void	move_left(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos + data->player.delta_y) / 64;
	y = (int)(data->player.y_pos - data->player.delta_x) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.x_pos += data->player.delta_y;
	data->player.y_pos -= data->player.delta_x;
}

static void	move_right(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos - data->player.delta_y) / 64;
	y = (int)(data->player.y_pos + data->player.delta_x) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.x_pos -= data->player.delta_y;
	data->player.y_pos += data->player.delta_x;
}

int	render_loop(void *data_game)
{
	t_data	*data;

	data = (t_data *)data_game;
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_backward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.left)
		rotate_left(data);
	if (data->keys.right)
		rotate_right(data);
	let_the_game_begin(data, &data->ray);
	return (0);
}