/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:42:18 by schennal          #+#    #+#             */
/*   Updated: 2024/06/07 23:51:17 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	is_wall(t_ray *ray, double x, double y, char **map)
{
	if (x > 0 && x < ray->data->window.map_width
		&& y > 0 && y < ray->data->window.map_height)
	{
		if (map[((int)y >> 6)][((int)x >> 6)] == '1')
			return (1);
	}
	return (0);
}

int	pythagoras(t_ray *ray, double x, double y)
{
	int	dist;

	dist = sqrt(pow(ray->x - x, 2) + pow(ray->y - y, 2));
	return (dist);
}

int	fix_fish_eye(t_ray *ray, double player_angle)
{
	double	angle;

	angle = ray->angle - player_angle;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	ray->ray_length = ray->ray_length * cos(angle);
	return (0);
}

void	shortest_ray2(t_data *data, t_ray *ray,
			int x_intercept, int y_intercept)
{
	if (data->previous == 'h')
	{
		ray->x_intercept = x_intercept;
		ray->y_intercept = y_intercept;
		ray->ray_length = ray->h_distance;
		ray->v_wall_hit_flag = 0;
	}
	else if (data->previous == 'v')
	{
		ray->ray_length = ray->v_distance;
		ray->h_wall_hit_flag = 0;
	}
}

void	shortest_ray(t_data *data, t_ray *ray,
			int x_intercept, int y_intercept)
{
	if (ray->h_distance < ray->v_distance && ray->h_wall_hit_flag)
	{
		ray->x_intercept = x_intercept;
		ray->y_intercept = y_intercept;
		ray->ray_length = ray->h_distance;
		ray->v_wall_hit_flag = 0;
		data->previous = 'h';
	}
	else if (ray->h_distance > ray->v_distance && ray->v_wall_hit_flag)
	{
		ray->ray_length = ray->v_distance;
		ray->h_wall_hit_flag = 0;
		data->previous = 'v';
	}
	else
		shortest_ray2(data, ray, x_intercept, y_intercept);
	ray->intercepts[0] = ray->x_intercept / 64 * 8;
	ray->intercepts[1] = ray->y_intercept / 64 * 8;
}

