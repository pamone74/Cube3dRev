/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:46:35 by aandom            #+#    #+#             */
/*   Updated: 2024/06/03 20:31:21 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

// ================================ substitute_tabs ======================================

/*
** This function substitutes tabs in a line with spaces.
** 
** line: The pointer to the original line.
** new_line: The pointer to the new line with tabs substituted.
** len: The length of the original line.
** j: Index for the new line.
**  Usage::::: it takes a line of text (*line) and replaces each tab characters with four spaces characters.
** Returns: The pointer to the new line.
*/

static char	*substitute_tabs(char **line, char **new_line, int len, int j)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < len)
	{
		if ((*line)[i] == '\t')
		{
			while (++k <= 4)
				(*new_line)[j++] = ' ';
			k = 0;
		}
		else
			(*new_line)[j++] = (*line)[i];
	}
	free(*line);
	return (*new_line);
}


// =========================================Handle tab ===============================================

/*
** This function handles tabs in a line.
** 
** line: The pointer to the line.
** i: Index for iterating through the line.
** len: The length of the line.
** tab_count: The count of tabs in the line.
** Usage:::::: This counts the number of tab  characters in a line and calculate and calculate the new length of the line after 
	replacing each tab with four spaces. Then it calls the substitute_tabs to perform replacement. 


*/
static void	handle_tab(char **line, int i, int len, int tab_count)
{
	int		new_len;
	char	*new_line;

	len = ft_strlen(*line);
	while (++i < len)
		if ((*line)[i] == '\t')
			tab_count++;
	if (tab_count == 0)
		return ;
	new_len = len + (tab_count * 3);
	new_line = ft_calloc(new_len + 1, sizeof(char));
	*line = substitute_tabs(line, &new_line, len, 0);
}

//  ======================================= Dup_map_files ===========================================
/*
** This function duplicates the map file into memory.
** 
** row: Index for rows in the map file.
** column: Index for columns in the map file.
** i: Index for iterating through the line.
** parse: The pointer to the parse structure.


Usage:::: This function readlines from a file (parese->imap.fd) and duplicates them into a 2D array (parse->imap.file) after
handling tabs. It allocates memeory for each line and stores them in the array

*/
static void	dup_map_file(int row, int column, int i, t_parse *parse)
{
	char	*line;

	line = get_next_line_3(parse->imap.fd);
	while (line != NULL)
	{
		handle_tab(&line, -1, 0, 0);
		if (ft_strchr(line, '\n') != 0)
			parse->imap.file[row] = ft_calloc(ft_strlen(line), sizeof(char));
		else
			parse->imap.file[row] = ft_calloc(ft_strlen(line) + 1,
					sizeof(char));
		if (!parse->imap.file[row])
		{
			print_err(NULL, "Couldn't allocate memory", 0);
			return (void_free_arr((void **)parse->imap.file));
		}
		while (line[i] != '\n' && line[i] != '\0')
			parse->imap.file[row][column++] = line[i++];
		parse->imap.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line_3(parse->imap.fd);
	}
	parse->imap.file[row] = NULL;
}

// ========================================== get_line_num ===============================================
/*
** This function calculates the number of lines in a file.
** 
** path: The path to the file.
** 
** Returns: The number of lines in the file.

Usage: Opens the file and count the number of lines
*/
static int	get_line_num(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_err(path, strerror(errno), errno);
	else
	{
		line = get_next_line_3(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line_3(fd);
		}
		close(fd);
	}
	return (line_count);
}


// ==================== Parse_map_file =============================
/*
	This function is used for validating, locating memory and making sure that our map is properly 
	parsed
** This function parses the map file.
** 
** path: The path to the map file.
** parse: The pointer to the parse structure.

Usage: I can say in a simple term that this function is the summary of all persing process 
*/
void	parse_map_file(char *path, t_parse *parse)
{
	int		row;
	size_t	col;
	int		i;

	i = 0;
	row = 0;
	col = 0;
	parse->imap.line_count = get_line_num(path);
	parse->imap.path = path;
	if (parse->imap.line_count == 0)
		return ((void)(print_err(NULL, "EMPTY_MAP_FILE", 0)));
	parse->imap.file = ft_calloc(parse->imap.line_count + 1, sizeof(char *));
	if (!(parse->imap.file))
		return ((void)(print_err(NULL, "Couldn't allocate memory", 0)));
	parse->imap.fd = open(path, O_RDONLY);
	if (parse->imap.fd < 0)
		print_err(path, strerror(errno), 1);
	else
	{
		dup_map_file(row, col, i, parse);
		close(parse->imap.fd);
	}
}
