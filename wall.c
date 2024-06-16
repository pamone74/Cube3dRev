/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:58:51 by schennal          #+#    #+#             */
/*   Updated: 2024/06/07 23:44:11 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static double	compute_xcord(t_data *data, t_ray *ray)
{
	double	x_cord;

	if (ray->h_wall_hit_flag)
	{
		x_cord = (int)(ray->x_intercept) % data->texture.t_width;
		if (ray->angle > PI)
			x_cord = data->texture.t_width - x_cord - 1;
	}
	else
	{
		x_cord = (int)(ray->y_intercept) % data->texture.t_width;
		if (ray->angle < PI / 2.0 || ray->angle > 3 * PI / 2.0)
			x_cord = data->texture.t_width - x_cord - 1;
	}
	return (x_cord);
}

static void	draw_wall(t_data *data, t_ray *ray, int x, int y)
{
	double	x_cord;
	double	step;
	double	tex_pos;
	int		tex_y;

	x_cord = compute_xcord(data, ray);
	step = data->texture.t_height / ray->wall_height;
	tex_pos = (ray->draw_start - (WIN_H / 2) + ray->wall_height / 2) * step;
	tex_y = (int)tex_pos & (data->texture.t_height - 1);
	while (y < ray->draw_end)
	{
		if ((y > -1 && y <= WIN_H) && (x > -1 && x <= WIN_W) && data->buffer[y][x] == WHITE) // the last condition is to avoid drawing over the gun
			data->buffer[y][x] = data->texture.addr[(tex_y * 64) + (int)x_cord];
		tex_pos += step;
		tex_y = (int)tex_pos & (data->texture.t_height - 1);
		y++;
	}
}

static t_img	compute_texture(t_data *data, t_ray *ray)
{
	if (ray->h_wall_hit_flag && ray->angle > 0 && ray->angle < PI)
		return (data->texture = data->no_img);
	else if (ray->h_wall_hit_flag && ray->angle > PI && ray->angle < 2 * PI)
		return (data->texture = data->so_img);
	else if (ray->v_wall_hit_flag && ray->angle > PI / 2 
		&& ray->angle < 3 * PI / 2)
		return (data->texture = data->ea_img);
	else if (ray->v_wall_hit_flag && (ray->angle < PI / 2 
			|| ray->angle > 3 * PI / 2))
		return (data->texture = data->we_img);
	else if (ray->h_wall_hit_flag)
		return (data->texture = data->no_img);
	else if (ray->v_wall_hit_flag)
		return (data->texture = data->so_img);
	return (data->we_img);
}

int	init_wall(t_ray *ray, t_data *data, int x)
{
	int		y;

	ray->wall_height = ((CUBE_SIZE * WIN_H) / ray->ray_length);
	ray->draw_start = (WIN_H / 2) - (ray->wall_height / 2.0);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (WIN_H / 2) + (ray->wall_height / 2);
	if (ray->draw_end > WIN_H)
		ray->draw_end = WIN_H;
	y = ray->draw_start - 1;
	data->texture = compute_texture(data, ray);
	draw_wall(data, ray, x, y);
	return (0);
}