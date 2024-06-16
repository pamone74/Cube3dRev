/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:40:29 by Degef             #+#    #+#             */
/*   Updated: 2023/08/31 14:27:24 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_main_str(int fd, char *main_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(((size_t)(BUFFER_SIZE) + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(main_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		main_str = ft_strjoin(main_str, buff);
	}
	free(buff);
	return (main_str);
}

char	*get_next_line(int fd, char **result)
{
	char		*line;
	static char	*main_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (0);
	main_str = read_to_main_str(fd, main_str);
	if (!main_str)
		return (0);
	line = ft_get_line(main_str);
	main_str = ft_new_main_str(main_str);
	*result = line;
	return (line);
}
