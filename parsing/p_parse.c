/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:18:22 by aandom            #+#    #+#             */
/*   Updated: 2024/06/03 20:24:17 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"


// ================= check_cub_file ============================
/*
** Checks if the file extension is .cub.
** 
** arg: The path to the file.
** 
** Returns: True if the extension is .cub, otherwise false.
*/
static bool	check_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}


// =============================== check xmp file extension ==========================================
/*
** Checks if the file extension is .xmp.
** 
** arg: The path to the file.
** 
** Returns: True if the extension is .xmp, otherwise false.
*/

static bool	check_xmp_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

// ============================= Dir check ================================================
/*
** Checks if the given path is a directory.
** 
** arg: The path to check.
** 
** Returns: True if the path is a directory, otherwise false.
*/

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

// ============================= Check map file ====================================================
/*
** Checks if the map file is valid and sets up the parsing process.
** 
** arg: The path to the map file.
** cub: Flag indicating whether the file is a .cub file.
** 
** Returns: 0 if successful, otherwise returns an error code.
*/

int	check_mapfile(char *arg, bool cub)
{
	int	fd;

	if (is_dir(arg))
		return (print_err(arg, "is Directory", 1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_err(arg, strerror(errno), 1));
	close(fd);
	if (cub && !check_cub_file(arg))
		return (print_err(arg, "not a .cub file", 1));
	if (!cub && !check_xmp_file(arg))
		return (print_err(arg, "not a .xmp file", 1));
	return (0);
}


// =========================================== Ft_parse ==========================================
/*
** Parses the input files.
** 
** parse: The pointer to the parsing structure.
** path: The path to the map file.
** 
** Returns: 1 if successful, otherwise returns an error code.
*/
int	ft_parse(t_parse *parse, char *path)
{
	if (check_mapfile(path, true) == 1)
		return (SUCCESS);
	parse->pdir = '\0';
	initialize_imap(&parse->imap);
	parse_map_file(path, parse);
	if (parse->imap.file == NULL)
		return (SUCCESS);
	initialize_parse_vars(parse);
	if (get_map(parse, parse->imap.file) == 1)
		return (free_double_array(&parse->imap.file), 0);
	if (check_map_ifvalid(parse, parse->map) == FAILURE)
		return (free_parser(parse), 0); 
	if (check_texture(parse) == FAILURE)
		return (free_parser(parse), 0);
	duplicate_parse(parse);
	return (1);
}
