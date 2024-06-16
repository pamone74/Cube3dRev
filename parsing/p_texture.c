/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:24:26 by aandom            #+#    #+#             */
/*   Updated: 2024/06/03 20:24:24 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
// ============================= convert rgb to hexadecimal ========================
/*
This function takes an array rgb_tab containing three integers representing the red, green, and blue components of an RGB color.
It converts these components into a single unsigned long integer representing the color in hexadecimal format.
The function first extracts the individual components r, g, and b from the rgb_tab array.
Then, it constructs the hexadecimal representation by shifting the bits of each component into their respective positions and combining them using bitwise OR operations.
Finally, it returns the resulting unsigned long integer.
*/

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}
// ======================================= make sure the rgb is valid ===========================
/*
This function checks whether an array rgb representing an RGB color is valid.
It iterates over the elements of the array and checks if each component is within the valid range of 0 to 255.
If any component is outside this range, it prints an error message using print_err_val and returns a failure status.
Otherwise, it returns a success status.
*/
static int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_err_val(rgb[i], "Invalid color", FAILURE));
		i++;
	}
	return (SUCCESS);
}
// ===================================== get the path of the textures ================================
/*
This function extracts a file path from a string line.
It takes an index j as a starting point to scan the line.
It skips leading whitespace characters and calculates the length of the file path.
It dynamically allocates memory for the file path using malloc.
It copies characters from the line into the allocated memory until it encounters whitespace or a newline character.
It returns the allocated file path if successful, or NULL if memory allocation fails or if the line contains invalid characters after the file path.
*/
static char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}
// ============================= Assigning the path to related textures file =========================
/*
This function parses a line containing texture file paths and fills corresponding fields in the parse structure.
It checks if the line contains valid texture identifiers ('NO', 'SO', 'WE', 'EA').
If a valid texture identifier is found and the corresponding field in the parse structure is empty, it calls get_texture_path to extract the file path and assigns it to the corresponding field.
It returns a success status if the operation is successful, or an error status otherwise
*/
int	fill_dir_tex(t_parse *parse, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2]))
		return (ERR);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(parse->no_text))
		parse->no_text = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(parse->so_text))
		parse->so_text = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(parse->we_text))
		parse->we_text = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(parse->ea_text))
		parse->ea_text = get_texture_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

// ================ Check for the texture, map files and make sure everything is ok ==============================
/*
This function validates texture file paths and RGB color values stored in the parse structure.
It checks if all necessary texture file paths (no_text, so_text, we_text, ea_text) and RGB color values (floor, ceiling) are present.
If any required data is missing, it prints an error message and returns a failure status.
It also checks the validity of texture file paths and RGB color values using check_mapfile and check_valid_rgb functions.
If any of these checks fail, it returns a failure status.
Otherwise, it converts RGB color values to hexadecimal format using convert_rgb_to_hex, frees the memory allocated for RGB color values, and returns a success status.
*/
int	check_texture(t_parse *parse)
{
	if (!parse->no_text || !parse->so_text || !parse->we_text
		|| !parse->ea_text)
		return (print_err(parse->imap.path, "NO texture found", FAILURE));
	if (!parse->floor || !parse->ceiling)
		return (print_err(parse->imap.path, "NO color found", FAILURE));
	if (check_mapfile(parse->no_text, false) == FAILURE
		|| check_mapfile(parse->so_text, false) == FAILURE
		|| check_mapfile(parse->we_text, false) == FAILURE
		|| check_mapfile(parse->ea_text, false) == FAILURE
		|| check_valid_rgb(parse->floor) == FAILURE
		|| check_valid_rgb(parse->ceiling) == FAILURE)
		return (FAILURE);
	parse->floor_color = convert_rgb_to_hex(parse->floor);
	parse->ceil_color = convert_rgb_to_hex(parse->ceiling);
	free(parse->floor);
	free(parse->ceiling);
	return (SUCCESS);
}
