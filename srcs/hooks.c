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

void	move_player(int keycode, t_game *game)
{
    int	new_x;
    int	new_y;

    new_x = game->player_x;
    new_y = game->player_y;
    if (keycode == KEY_W)
        new_y--;
    else if (keycode == KEY_S)
        new_y++;
    else if (keycode == KEY_A)
        new_x--;
    else if (keycode == KEY_D)
        new_x++;
    if (game->map[new_y][new_x] != '1')
    {
        if (game->map[new_y][new_x] == 'E' && game->collectibles != 0)
            return;
        game->moves++;
        printf("Moves: %d\n", game->moves);
        if (game->map[new_y][new_x] == 'C')
            game->collectibles--;
        if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
            close_game(game);
        game->map[game->player_y][game->player_x] = '0';
        game->player_x = new_x;
        game->player_y = new_y;
        game->map[new_y][new_x] = 'P';
        render_map(game);
    }
}

int	key_hook(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_game(game);
    else if (keycode == KEY_W || keycode == KEY_A
        || keycode == KEY_S || keycode == KEY_D)
        move_player(keycode, game);
    return (0);
}
