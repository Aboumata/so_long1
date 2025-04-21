/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:45:55 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/20 23:45:56 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
    t_game	game;

    init_game(&game);
    if (argc != 2)
        error_exit("Usage: ./so_long <map_file.ber>", &game);
    check_name(argv[1]);
    validate_map(argv[1], &game);
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE,
            game.map_height * TILE_SIZE, "so_long");
    load_textures(&game);
    render_map(&game);
    mlx_hook(game.win, 17, 0, close_game, &game);
    mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
    mlx_loop(game.mlx);
    return (0);
}
