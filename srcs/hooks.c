/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:46:58 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/20 23:47:03 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

static void	update_position(t_game *game, int x, int y)
{
	game->moves++;
	write(1, "Moves: ", 7);
	ft_putnbr_fd(game->moves, 1);
	write(1, "\n", 1);
	if (game->map[y][x] == 'C')
		game->collectibles--;
	if (game->map[y][x] == 'E' && game->collectibles == 0)
		close_game(game);
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = x;
	game->player_y = y;
	game->map[y][x] = 'P';
	render_map(game);
}

void	move_player(int keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if (keycode == KEY_W)
		y--;
	else if (keycode == KEY_S)
		y++;
	else if (keycode == KEY_A)
		x--;
	else if (keycode == KEY_D)
		x++;
	if (game->map[y][x] == '1' || (game->map[y][x] == 'E'
			&& game->collectibles > 0))
		return ;
	update_position(game, x, y);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D)
		move_player(keycode, game);
	return (0);
}
