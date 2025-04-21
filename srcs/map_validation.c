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

static void	read_map(char *map_file, t_game *game)
{
    int		fd;
    char	*line;
    int		i;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        error_exit("Map file not found", game);

    game->map_height = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        game->map_height++;
        free(line);
    }
    close(fd);

    game->map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!game->map)
        error_exit("Memory allocation failed", game);

    fd = open(map_file, O_RDONLY);
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        game->map[i] = line;
        if (ft_strchr(game->map[i], '\n'))
            *ft_strchr(game->map[i], '\n') = '\0';
        i++;
    }
    game->map[i] = NULL;
    close(fd);

    game->map_width = ft_strlen(game->map[0]);
}

void	check_walls(t_game *game)
{
    int	x;
    int	y;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        if ((size_t)ft_strlen(game->map[y]) != (size_t)game->map_width)
            error_exit("Map is not rectangular", game);
        while (game->map[y][x])
        {
            if ((y == 0 || y == game->map_height - 1) && game->map[y][x] != '1')
                error_exit("Map not surrounded by walls", game);
            if ((x == 0 || x == game->map_width - 1) && game->map[y][x] != '1')
                error_exit("Map not surrounded by walls", game);
            x++;
        }
        y++;
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
