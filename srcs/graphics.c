/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:46:38 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/20 23:46:42 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_game *game)
{
    int	img_size;

    img_size = TILE_SIZE;
    game->wall = mlx_xpm_file_to_image(game->mlx,
            "textures/wall.xpm", &img_size, &img_size);
    game->floor = mlx_xpm_file_to_image(game->mlx,
            "textures/floor.xpm", &img_size, &img_size);
    game->collectible = mlx_xpm_file_to_image(game->mlx,
            "textures/collectible.xpm", &img_size, &img_size);
    game->exit = mlx_xpm_file_to_image(game->mlx,
            "textures/exit.xpm", &img_size, &img_size);
    game->player = mlx_xpm_file_to_image(game->mlx,
            "textures/player.xpm", &img_size, &img_size);
    if (!game->wall || !game->floor || !game->collectible
        || !game->exit || !game->player)
        error_exit("Failed to load textures", game);
}

void	render_map(t_game *game)
{
    int	x;
    int	y;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            mlx_put_image_to_window(game->mlx, game->win, game->floor,
                x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall,
                    x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible,
                    x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit,
                    x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->player,
        game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}
