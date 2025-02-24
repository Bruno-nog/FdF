/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:19:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/24 20:48:31 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_columns(char *line)
{
	int		count;
	char	*temp;
	char	*num;

	count = 0;
	temp = ft_strdup(line);
	num = ft_strtok(temp, " ");
	while (num)
	{
		count++;
		num = ft_strtok(NULL, " ");
	}
	free(temp);
	return (count);
}

int	count_rows(int *fd, char *filename)
{
	char	*line;
	int		rows;

	rows = 0;
	line = get_next_line(*fd);
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(*fd);
	}
	close(*fd);
	*fd = open(filename, O_RDONLY);
	return (rows);
}

static int	read_and_count_columns(int fd, int *cols)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	*cols = count_columns(line);
	free(line);
	return (1);
}

static int	get_dimensions(char *filename, int *rows, int *cols)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	*rows = count_rows(&fd, filename);
	if (!read_and_count_columns(fd, cols))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

int	**read_map(char *filename, int *rows, int *cols)
{
	int		**map;
	int		fd;

	if (get_dimensions(filename, rows, cols) < 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = allocate_map(*rows, *cols);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	fill_map(fd, map, *rows, *cols);
	close(fd);
	return (map);
}
