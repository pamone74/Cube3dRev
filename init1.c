/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:40:52 by schennal          #+#    #+#             */
/*   Updated: 2024/06/07 20:22:01 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// ================================== This is the function that manages the opening and closing of the window =====================

int	init_window(t_data *data)
{
	data->window.mlx = mlx_init();
	data->window.win = mlx_new_window(data->window.mlx, WIN_W, WIN_H, "Cub3D");
	data->image.img = mlx_new_image(data->window.mlx, WIN_W, WIN_H);
	data->image.addr = (int *)mlx_get_data_addr(data->image.img,
			&data->image.bpp, 
			&data->image.line_length, &data->image.endian);
	data->mini_map.img = mlx_new_image(data->window.mlx,
			data->parse->column * 8, data->parse->row * 8);
	data->mini_map.addr = (int *)mlx_get_data_addr(data->mini_map.img,
			&data->mini_map.bpp,
			&data->mini_map.line_length, &data->mini_map.endian);
	// if (!get_texture(data->parse, data))
	// 	return (0);
	// cast_rays(data, &data->ray);
	return (1);
}

static int load_texture (t_parse *parse, t_data *data)
{
	data->no_img.img = mlx_xpm_file_to_image(data->window.mlx,
			parse->no_text, &data->no_img.t_width, &data->no_img.t_height);
	data->so_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->so_text,
			&data->so_img.t_width, &data->so_img.t_height);
	data->we_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->we_text,
			&data->we_img.t_width, &data->we_img.t_height);
	data->ea_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->ea_text,
			&data->ea_img.t_width, &data->ea_img.t_height);
	data->floor_img.img = mlx_xpm_file_to_image(data->window.mlx,
			"./textures/floor.xpm", &data->floor_img.t_width,
			&data->floor_img.t_height);
	data->gun.img = mlx_xpm_file_to_image(data->window.mlx,
			"./textures/gun.xpm", &data->gun.t_width, &data->gun.t_height);
	if (!data->no_img.img || !data->so_img.img || !data->we_img.img 
		|| !data->ea_img.img || !data->floor_img.img)
		return (printf("Error! Texture not found\n"), 0);
	return(1);
}

// static int load_texture(t_parse *parse, t_data *data)
// {
//     // Load North texture
//     data->no_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->no_text,
//                                              &data->no_img.t_width, &data->no_img.t_height);
//     if (!data->no_img.img)
//     {
//         printf("Error loading texture: %s\n", parse->no_text);
//         return 0;
//     }

//     // Load South texture
//     data->so_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->so_text,
//                                              &data->so_img.t_width, &data->so_img.t_height);
//     if (!data->so_img.img)
//     {
//         printf("Error loading texture: %s\n", parse->so_text);
//         return 0;
//     }

//     // Load West texture
//     data->we_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->we_text,
//                                              &data->we_img.t_width, &data->we_img.t_height);
//     if (!data->we_img.img)
//     {
//         printf("Error loading texture: %s\n", parse->we_text);
//         return 0;
//     }

//     // Load East texture
//     data->ea_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->ea_text,
//                                              &data->ea_img.t_width, &data->ea_img.t_height);
//     if (!data->ea_img.img)
//     {
//         printf("Error loading texture: %s\n", parse->ea_text);
//         return 0;
//     }

//     // Load floor texture
//     data->floor_img.img = mlx_xpm_file_to_image(data->window.mlx, "./textures/floor.xpm",
//                                                 &data->floor_img.t_width, &data->floor_img.t_height);
//     if (!data->floor_img.img)
//     {
//         printf("Error loading texture: ./textures/floor.xpm\n");
//         return 0;
//     }

//     // Load gun texture
//     data->gun.img = mlx_xpm_file_to_image(data->window.mlx, "./textures/gun.xpm",
//                                           &data->gun.t_width, &data->gun.t_height);
//     if (!data->gun.img)
//     {
//         printf("Error loading texture: ./textures/gun.xpm\n");
//         return 0;
//     }

//     return 1;
// }

static int	extract_texture(t_data *data) 
{
	data->no_img.addr = (int *)mlx_get_data_addr(data->no_img.img,
			&data->no_img.bpp, &data->no_img.line_length, &data->no_img.endian);
	data->so_img.addr = (int *)mlx_get_data_addr(data->so_img.img,
			&data->so_img.bpp, &data->so_img.line_length, &data->so_img.endian);
	data->we_img.addr = (int *)mlx_get_data_addr(data->we_img.img,
			&data->we_img.bpp, &data->we_img.line_length, &data->we_img.endian);
	data->ea_img.addr = (int *)mlx_get_data_addr(data->ea_img.img,
			&data->ea_img.bpp, &data->ea_img.line_length, &data->ea_img.endian);
	data->floor_img.addr = (int *)mlx_get_data_addr(data->floor_img.img,
			&data->floor_img.bpp, &data->floor_img.line_length,
			&data->floor_img.endian);
	data->gun.addr = (int *)mlx_get_data_addr(data->gun.img,
			&data->gun.bpp, &data->gun.line_length, &data->gun.endian);
	return (1);
}

int	init_texture(t_parse *parse, t_data *data)
{
	load_texture (parse, data);
	extract_texture(data);
	return (1);
}

int	setup_hooks(t_data *data)
{
	mlx_hook(data->window.win, KEY_PRESS_EVENT, 1L<<0, &handle_keypress, data);
	mlx_hook(data->window.win, KEY_RELEASE_EVENT, 1L<<1, &handle_keyrelease, data);
	mlx_hook(data->window.win, EXIT_EVENT, 1L << 17, &terminate_game, data);
	mlx_loop_hook(data->window.mlx, &render_loop, data);
	mlx_loop(data->window.mlx);
	(void) data;
	return (1);
}
