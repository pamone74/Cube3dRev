/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:34:48 by schennal          #+#    #+#             */
/*   Updated: 2024/06/07 23:50:00 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// int	put_pixels(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < WIN_H)
// 	{
// 		j = -1;
// 		while (++j < WIN_W)
// 			update_image(data, j, i);
// 	}
// 	data->image.addr[WIN_H / 2 * WIN_W + WIN_W / 2] = 0x00FF00;
// 	return (0);
// }

int	is_ceiling(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (--i > -1)
	{
		if (buffer[i][k] != WHITE)
			return (0);
	}
	return (1);
}

int	is_floor(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (++i < WIN_H)
	{
		if (buffer[i][k] != WHITE)
			return (0);
	}
	return (1);
}

void	update_image(t_data *data, int j, int i)
{
	// if (is_ceiling(data->buffer, i, j))
	// 	data->image.addr[i * WIN_W + j] = data->parse->ceil_color;
	// else if (is_floor(data->buffer, i, j))
	// 	data->image.addr[i * WIN_W + j] = data->parse->floor_color;
	if (i < WIN_H / 2 && data->buffer[i][j] == WHITE)
		data->image.addr[i * WIN_W + j] = data->parse->ceil_color;
	else if (i > WIN_H / 2 && data->buffer[i][j] == WHITE)
		data->image.addr[i * WIN_W + j] = data->parse->floor_color;
	else
		data->image.addr[i * WIN_W + j] = data->buffer[i][j];
	// else
	// 	data->image.addr[i * WIN_W + j] = data->buffer[i][j];
	if (((i > WIN_H / 2 - 8 && i < WIN_H / 2 - 3)
			|| (i > WIN_H / 2 + 3 && i < WIN_H / 2 + 8))
		&& j == WIN_W / 2)
		data->image.addr[i * WIN_W + j] = 0x00FF00;
	if (((j > WIN_W / 2 - 8 && j < WIN_W / 2 - 3)
			|| (j > WIN_W / 2 + 3 && j < WIN_W / 2 + 8))
		&& i == WIN_H / 2)
		data->image.addr[i * WIN_W + j] = 0x00FF00;
}


void	draw_game(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_H)
	{
		j = -1;
		while (++j < WIN_W)
			update_image(data, j, i);
	}
	data->image.addr[WIN_H / 2 * WIN_W + WIN_W / 2] = 0x00FF00;
	//return (0);
	// mlx_put_image_to_window(data->window.mlx, data->window.win,
	// 	data->image.img, 0, 0);
	// mlx_put_image_to_window(data->window.mlx, data->window.win,
	// 	data->mini_map.img, 0, 0);
}