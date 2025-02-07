/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:19:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/06 19:22:19 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int count_columns(char *line)
{
    int count = 0;
    char *copy = strdup(line);
    char *num = strtok(copy, " ");
    while (num)
    {
        count++;
        num = strtok(NULL, " ");
    }
    free(copy);
    return count;
}

int count_rows(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    int rows = 0;
    while (getline(&line, &len, file) != -1)
        rows++;
    free(line);
    rewind(file);
    return rows;
}

int **allocate_map(int rows, int cols)
{
    int **map = malloc(sizeof(int *) * rows);
    if (!map)
        return NULL;
    for (int i = 0; i < rows; i++)
    {
        map[i] = malloc(sizeof(int) * cols);
        if (!map[i])
        {
            while (--i >= 0)
                free(map[i]);
            free(map);
            return NULL;
        }
    }
    return map;
}

void fill_map(FILE *file, int **map, int rows, int cols)
{
    (void)rows;
    
    char *line = NULL;
    size_t len = 0;
    int y = 0;
    while (getline(&line, &len, file) != -1)
    {
        int x = 0;
        char *num = strtok(line, " ");
        while (num && x < cols)
        {
            map[y][x++] = atoi(num);
            num = strtok(NULL, " ");
        }
        y++;
    }
    free(line);
}

int **read_map(char *filename, int *rows, int *cols)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    *rows = count_rows(file);
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, file);
    *cols = count_columns(line);
    rewind(file);

    int **map = allocate_map(*rows, *cols);
    if (!map)
        return NULL;

    fill_map(file, map, *rows, *cols);
    
    free(line);
    fclose(file);
    return map;
}
