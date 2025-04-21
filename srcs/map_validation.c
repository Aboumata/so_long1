/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:46:13 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/20 23:46:15 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void read_map(char *map_file, t_game *game)
{
    int fd;
    char *line = NULL;
    int line_count = 0;
    int i;
    int last_non_empty = -1;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        error_exit("Map file not found", game);

    game->map = malloc(sizeof(char *) * 1024);
    while ((line = get_next_line(fd)) != NULL)
    {
        char *nl = ft_strchr(line, '\n');
        if (nl)
            *nl = '\0';
        game->map[line_count] = line;
        if (ft_strlen(line) > 0)
            last_non_empty = line_count;
        line_count++;
    }
    game->map[line_count] = NULL;

    close(fd);

    if (last_non_empty == -1)
        error_exit("Map is empty", game);
    game->map_height = last_non_empty + 1;
    game->map_width = ft_strlen(game->map[0]);

    for (i = 0; i < game->map_height; i++)
    {
        if (ft_strlen(game->map[i]) != game->map_width)
        {
            error_exit("Map is not rectangular", game);
        }
    }
}

void check_walls(t_game *game)
{
    int x;
    int y;

    y = -1;
    while (++y < game->map_height)
    {
        x = -1;
        while (++x < game->map_width)
        {
            if ((y == 0 || y == game->map_height - 1) && game->map[y][x] != '1')
                error_exit("Map not surrounded by walls", game);
            if ((x == 0 || x == game->map_width - 1) && game->map[y][x] != '1')
                error_exit("Map not surrounded by walls", game);
        }
    }
}

void	check_map_contents(t_game *game)
{
    int	y;
    int	x;
    int	has_exit;
    int	has_start;

    y = -1;
    has_exit = 0;
    has_start = 0;
    game->collectibles = 0;
    while (game->map[++y])
    {
        x = -1;
        while (game->map[y][++x])
        {
            if (game->map[y][x] == 'E')
                has_exit++;
            else if (game->map[y][x] == 'P')
            {
                has_start++;
                game->player_x = x;
                game->player_y = y;
            }
            else if (game->map[y][x] == 'C')
                game->collectibles++;
            else if (!ft_strchr("01CEP", game->map[y][x]))
                error_exit("Invalid map character", game);
        }
    }
    if (has_exit != 1 || has_start != 1 || game->collectibles < 1)
        error_exit("Map content requirements not met", game);
}

void	validate_map(char *map_file, t_game *game)
{
    read_map(map_file, game);
    check_walls(game);
    check_map_contents(game);
    if (!validate_path(game))
        error_exit("No valid path in map", game);
}
