/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chatgtp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:19:25 by schennal          #+#    #+#             */
/*   Updated: 2024/06/03 21:28:17 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "mlx/mlx.h" // Include miniLibX library

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_HEIGHT 640
#define SCREEN_WIDTH 480

typedef struct s_game
{
    void *mlx;
    void *win;
    int map[MAP_HEIGHT][MAP_WIDTH];
    double player_x;
    double player_y;
    double player_dir_x;
    double player_dir_y;
    double plane_x;
    double plane_y;
} t_game;

void parse_map(t_game *game, char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    // Parse the map from the file and store it in game->map
    // Update player position and direction
    close(fd);
}

void initialize_game(t_game *game)
{
    // Initialize miniLibX window
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");

    // Initialize player position and direction
    game->player_x = 22.0;
    game->player_y = 11.5;
    game->player_dir_x = -1.0;
    game->player_dir_y = 0.0;
    game->plane_x = 0.0;
    game->plane_y = 0.66;

    // Parse the map from the scene description file
    parse_map(game, "map.cub");
}

void render_frame(t_game *game)
{
    // Render the frame using ray-casting algorithm
    // Draw walls, floor, ceiling, and player position
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        printf("Usage: ./cub3D map_file.cub\n");
        return 1;
    }

    initialize_game(&game);

    // Main game loop
    while (1)
    {
        // Render the frame
        render_frame(&game);
        // Handle controls
        // Implement controls for moving the player and rotating the view
    }

    return 0;
}
