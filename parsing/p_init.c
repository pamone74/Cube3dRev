/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:38:45 by aandom            #+#    #+#             */
/*   Updated: 2024/06/03 20:24:02 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	initialize_imap(t_imap *inputmap)
{
	inputmap->fd = 0;
	inputmap->line_count = 0;
	inputmap->path = NULL;
	inputmap->file = NULL;
	inputmap->height = 0;
	inputmap->width = 0;
	inputmap->end_idx = 0;
}
/*
duplicates data from one structure (parse->imap) to another structure (parse). 
It's important to note that when copying pointers like in the second line (parse->text = parse->imap.file;), 
it's a shallow copy, meaning both structures will point to the same memory location
*/
void	duplicate_parse(t_parse *parse)
{
	parse->num_lines = parse->imap.line_count;
	parse->text = parse->imap.file;
	parse->column = parse->imap.width;
	parse->row = parse->imap.height;
}

void	initialize_parse_vars(t_parse *parse)
{
	parse->no_text = NULL;
	parse->so_text = NULL;
	parse->we_text = NULL;
	parse->ea_text = NULL;
	parse->map = NULL;
	parse->floor = 0;
	parse->ceiling = 0;
}
