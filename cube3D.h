/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:27:01 by schennal          #+#    #+#             */
/*   Updated: 2024/06/08 00:53:00 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"

# define KEY_PRESS_EVENT		2
# define KEY_RELEASE_EVENT		3
# define EXIT_EVENT				17

# define WALL_ERR "MAP_NOT_SURROUNDED_BY_WALLS"

# define WIN_W	640
# define WIN_H	448

# define STEP_SIZE  5.00
# define FOV 60.00
# define ROTATION_ANGLE 0.06
# define PI 3.1415926535898
# define CUBE_SIZE 64.00
//colors
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

// keys 
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

enum e_tex_idx
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST
};

enum e_out
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BR = 3,
	CONTINUE = 4
};

typedef struct s_imap
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	int		height;
	int		width;
	int		end_idx;
}	t_imap;

typedef struct s_parse
{
	char			**map;        // map Data
	int				num_lines;    // total nuber of lines
	char			**text;		  // texture 
	char			*no_text;// North texture   
	char			*so_text;// south texture
	char			*we_text;// West texture
	char			*ea_text;// east texture
	int				floor_color;// color of the floor
	int				ceil_color;// color of the cieling
	size_t			column;// column of the map
	size_t			row;// map row
	int				*floor;
	int				*ceiling;
	char			pdir;
	t_imap			imap;
}				t_parse;

// typedef struct s_ray {
// 	double			angle;
// 	struct s_data	*data;
// 	double			x;
// 	double			y;
// 	double			x_intercept;
// 	double			y_intercept;
// 	int				intercepts[2];
// 	int				h_wall_hit_flag;
// 	int				v_wall_hit_flag;
// 	double			h_distance;
// 	double			v_distance;
// 	double			ray_length;
// 	double			wall_height;
// 	int				draw_start;
// 	int				draw_end;
// }	t_ray;

typedef struct s_img
{
	void	*background_img;
	void	*wall_img;
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		t_width;
	int		t_height;
}	t_img;

typedef struct s_player
{
	double		x_pos;
	double		y_pos;
	double		angle;
	double		fov;
	double		delta_x;
	double		delta_y;
}	t_player;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	int		map_width;
	int		map_height;
}	t_window;

typedef struct s_keys {
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_image {
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_draw_line {
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		color;
}	t_draw_line;

typedef struct s_ray {
	double			angle;
	struct s_data	*data;
	double			x;
	double			y;
	double			x_intercept;
	double			y_intercept;
	int				intercepts[2];
	int				h_wall_hit_flag;
	int				v_wall_hit_flag;
	double			h_distance;
	double			v_distance;
	double			ray_length;
	double			wall_height;
	int				draw_start;
	int				draw_end;
}	t_ray;

typedef struct s_data
{
	t_parse			*parse;
	t_ray			ray;
	t_player		player;
	t_window		window;
	t_keys			keys;
	double			angle_increment;
	t_image			image;
	t_image			mini_map;
	unsigned int	**buffer;
	int				previous;
	t_img			texture;
	t_img			no_img;
	t_img			so_img;
	t_img			we_img;
	t_img			ea_img;
	t_img		    floor_img;
	t_draw_line		draw_line;
	t_img			gun;
}				t_data;


int init(t_data *data);

void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
int	handle_keypress(int key, void *data_game);
int	handle_keyrelease(int key, void *data_game);
int	terminate_game(void *ptr);
int	render_loop(void *data_game);

int	init_window(t_data *data);

//init.c/*-----------------------------------------------*/
int	init_keys(t_data *data);
int	init_player(t_data *data);
int	player_pos(t_data *data, int i, int j);
int init_map(t_data *data);

//init1.c/*-----------------------------------------------*/
int	init_texture(t_parse *parse, t_data *data);
int	setup_hooks(t_data *data);

//game.c/*-----------------------------------------------*/
int	let_the_game_begin(t_data *data, t_ray *ray);
void	init_game(t_data *data);
int	init_rays(t_data *data);
int	init_buffer(t_data *data);
void init_gun(t_data *data);

//minimap.c/*-----------------------------------------------*/
void	init_vars(t_data *data, int x1, int y1, int *pos2);
void	draw_ray(t_data *data, int x1, int y1, int *pos2);
void	draw_player(t_data *data, int x, int y);
int	draw_grid_lines(t_data *data, int win_width, int win_height, int color);
void	init_minimap(t_data *data, char **map, int x, int y);

//compute_ray.c/*-----------------------------------------------*/
int	compute_h_wall_interception(t_ray *ray, char **map,
		double x_offset, double y_offset);
int	h_raycast(t_ray *ray, char **map);
int	compute_v_wall_interception(t_ray *ray, char **map,
		double x_offset, double y_offset);
int	v_raycast(t_ray *ray, char **map);

//game_utils.c/*-----------------------------------------------*/
int	fix_fish_eye(t_ray *ray, double player_angle);
void	shortest_ray2(t_data *data, t_ray *ray,
			int x_intercept, int y_intercept);
void	shortest_ray(t_data *data, t_ray *ray,
			int x_intercept, int y_intercept);
int	pythagoras(t_ray *ray, double x, double y);
int	is_wall(t_ray *ray, double x, double y, char **map);





//wall.c/*-----------------------------------------------*/
int	init_wall(t_ray *ray, t_data *data, int x);


//game1.c/*-----------------------------------------------*/
void	draw_game(t_data *data);


//parsing
void	free_parser(t_parse *parse);
void	free_memory(t_parse *parse, t_data *data);
void	free_double_array(char ***str);
void	free_double_array2(unsigned int ***str);
int		print_err(char *info, char *str, int code);
void	initialize_imap(t_imap *inputmap);
void	void_free_arr(void **str);
int		ft_parse(t_parse *parse, char *path);
int		print_err_val(int detail, char *str, int code);
void	parse_map_file(char *path, t_parse *parse);
int		fill_dir_tex(t_parse *parse, char *line, int j);
int		fill_color_textures(t_parse *parse, char *line, int j);
int		check_map_ifvalid(t_parse *parse, char **map);
int		check_mapfile(char *arg, bool cub);
int		check_texture(t_parse *parse);
int		get_map(t_parse *parse, char **map);
int		check_map_elements(t_parse *parse, char **map_tab);
int		check_map_is_at_the_end(t_imap *map);
int		create_map(t_parse *parse, char **file, int i);
int		check_wall_elements(t_parse *p, int j, int i, int start);
int		is_start_zero(char **map, int j);
int		check_front(char **map, int j, int i);
int		check_wall_elements_2(t_parse *p, int j, int i, int start);
// size_t	find_biggest_len(t_imap *map, int i);
void	initialize_parse_vars(t_parse *parse);
void	duplicate_parse(t_parse *parse);
int		check_walls(t_parse *p, int j, int i);

#endif
