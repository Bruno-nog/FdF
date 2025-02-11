/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:19:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:25:04 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_columns(char *line)
{
	int		count;
	char	*copy;
	char	*num;

	count = 0;
	copy = strdup(line);
	num = strtok(copy, " ");
	while (num)
	{
		count++;
		num = strtok(NULL, " ");
	}
	free(copy);
	return (count);
}

int	count_rows(FILE *file)
{
	char	*line;
	size_t	len;
	int		rows;

	line = NULL;
	len = 0;
	rows = 0;
	while (getline(&line, &len, file) != -1)
		rows++;
	free(line);
	rewind(file);
	return (rows);
}

int	**allocate_map(int rows, int cols)
{
	int	**map;
	int	i;

	i = 0;
	map = malloc(sizeof(int *) * rows);
	if (!map)
		return (NULL);
	while (i < rows)
	{
		map[i] = malloc(sizeof(int) * cols);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

void	fill_map(FILE *file, int **map, int x, int cols)
{
	char	*line;
	char	*num;
	size_t	len;
	int		y;

	line = NULL;
	len = 0;
	y = 0;
	while (getline(&line, &len, file) != -1)
	{
		x = 0;
		num = strtok(line, " ");
		while (num && x < cols)
		{
			map[y][x++] = atoi(num);
			num = strtok(NULL, " ");
		}
		y++;
	}
	free(line);
}

int	**read_map(char *filename, int *rows, int *cols)
{
	char	*line;
	size_t	len;
	int		**map;
	FILE	*file;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);
	*rows = count_rows(file);
	line = NULL;
	len = 0;
	getline(&line, &len, file);
	*cols = count_columns(line);
	rewind(file);
	map = allocate_map(*rows, *cols);
	if (!map)
		return (NULL);
	fill_map(file, map, *rows, *cols);
	free(line);
	fclose(file);
	return (map);
}
