/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:59:15 by schennal          #+#    #+#             */
/*   Updated: 2024/06/07 23:48:33 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// =================== Bresenham's line Algorithm ==================================================
// Initializng the variables:
// The dx is a change in x which is rhe intial position -  the next position in the x cordinates
// the same applies to dy
// the sx its the sign to know weather to draw vartical or horizontal in 2 plane on x cordiantes
// same applies to sy
// the line err term is when thr line cannot bediagonally drwan perfecttly so the difference btn the cordinates is the 
// error terms. 


void	init_vars(t_data *data, int x1, int y1, int *pos2)
{
	data->draw_line.dx = abs(pos2[0] - x1);
	data->draw_line.dy = abs(pos2[1] - y1);
	data->draw_line.sx = -1;
	if (x1 < pos2[0])
		data->draw_line.sx = 1;
	data->draw_line.sy = -1;
	if (y1 < pos2[1])
		data->draw_line.sy = 1;
	data->draw_line.err = data->draw_line.dx - data->draw_line.dy;
}
// Drawing the line. There are few things i will take about them here:
/*
	the loops will run until we meet the target position: pos2[0] and pos2[1] whix is eqv x2, y2
	we set the color of each pixel at x1 and y1 on the minimap to "said color" [a hex color value]
	This y1 * data->parse->column * 8 + x1 is the index of array addr in the linear memeory address.
	If x1 and y1 has reached the targeted position, we break the loop.
	We calculate the error and adjust the cordinates, we are setting it twice to deciode which direction to move horizontally or
	vertically.

*/
void	draw_ray(t_data *data, int x1, int y1, int *pos2)
{
	init_vars(data, x1, y1, pos2);
	while (x1 != pos2[0] || y1 != pos2[1])
	{
		data->mini_map.addr[y1 * data->parse->column *8 + x1] = 0x74DF00;
		if (x1 == pos2[0] && y1 == pos2[1])
			break ;
		data->draw_line.e2 = 2 * data->draw_line.err;
		if (data->draw_line.e2 > -data->draw_line.dy) // horizontal step
		{
			data->draw_line.err -= data->draw_line.dy;
			x1 += data->draw_line.sx;
		}
		if (data->draw_line.e2 < data->draw_line.dx)
		{
			data->draw_line.err += data->draw_line.dx;
			y1 += data->draw_line.sy;
		}
	}
}

void	draw_player(t_data *data, int x, int y)
{
	int	size;
	int	i;
	int	j;

	i = -1;
	size = 3;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			data->mini_map.addr[(y + j)
				* data->parse->column * 8 + (x + i)] = 0x00FF00;
	}
}

int	draw_grid_lines(t_data *data, int win_width, int win_height, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < win_width)
	{
		y = -1;
		while (++y < win_height)
			data->mini_map.addr[y * win_width + x] = color;
		x += 8;
	}
	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (++x < win_width)
			data->mini_map.addr[y * win_width + x] = color;
		y += 8;
	}
	return (0);
}


void	init_minimap(t_data *data, char **map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < y)
	{
		j = -1;
		while (++j < x)
		{
			if (map[i / 8][j / 8] == '1')
				data->mini_map.addr[i * x + j] = 0x0489B1;
			else
				data->mini_map.addr[i * x + j] = 0x00000000;
		}
	}
	draw_grid_lines(data, x, y, 0x00000000);
	draw_player(data, data->player.x_pos / 64 * 8, data->player.y_pos / 64 * 8);
}
