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
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&img_size, &img_size);
	game->floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&img_size, &img_size);
	game->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &img_size, &img_size);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&img_size, &img_size);
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&img_size, &img_size);
	if (!game->wall || !game->floor || !game->collectible || !game->exit
		|| !game->player)
		error_exit("Failed to load textures", game);
}

void	render_map(t_game *game)
{
	int (x), y;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor, x
				* TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall, x
					* TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit, x
					* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->player, game->player_x
		* TILE_SIZE, game->player_y * TILE_SIZE);
}

static int	strings_equal(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == '\0' && *s2 == '\0');
}

static void	exit_with_error(void)
{
	write(STDERR_FILENO, "Error\ninvalid name\n", 19);
	exit(EXIT_FAILURE);
}

void	check_name(char *filename)
{
	char	*extension;
	char	*p;

	extension = NULL;
	p = filename;
	while (*p)
	{
		if (*p == '.')
		{
			extension = p;
		}
		p++;
	}
	if (!extension || extension == filename || *(extension - 1) == '/')
	{
		exit_with_error();
	}
	if (!strings_equal(extension, ".ber"))
	{
		exit_with_error();
	}
}
