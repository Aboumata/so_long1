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

void	check_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
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

static void	handle_tile(t_game *game, t_map_state *s)
{
	char	tile;

	tile = game->map[s->y][s->x];
	if (tile == 'E')
		s->has_exit++;
	else if (tile == 'P')
	{
		s->has_start++;
		game->player_x = s->x;
		game->player_y = s->y;
	}
	else if (tile == 'C')
		game->collectibles++;
	else if (!ft_strchr("01CEP", tile))
		error_exit("Invalid map character", game);
}

void	check_map_contents(t_game *game)
{
	t_map_state	s;

	s.y = 0;
	s.has_exit = 0;
	s.has_start = 0;
	game->collectibles = 0;
	while (game->map[s.y])
	{
		s.x = 0;
		while (game->map[s.y][s.x])
		{
			handle_tile(game, &s);
			s.x++;
		}
		s.y++;
	}
	if (s.has_exit != 1 || s.has_start != 1 || game->collectibles < 1)
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
