/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 00:37:23 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/21 00:37:24 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**map_copy(t_game *game)
{
    char	**copy;
    int		i;

    copy = malloc(sizeof(char *) * (game->map_height + 1));
    if (!copy)
        return (NULL);
    i = -1;
    while (++i < game->map_height)
    {
        copy[i] = ft_strdup(game->map[i]);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
    }
    copy[i] = NULL;
    return (copy);
}

static void	fill(char **copy, int x, int y, t_game *game)
{
    if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
        return ;
    if (copy[y][x] == '1' || copy[y][x] == 'X' || copy[y][x] == 'E')
        return ;
    copy[y][x] = 'X';
    fill(copy, x + 1, y, game);
    fill(copy, x - 1, y, game);
    fill(copy, x, y + 1, game);
    fill(copy, x, y - 1, game);
}

static int	check_path(char **copy, t_game *game)
{
    int	y;
    int	x;

    y = -1;
    while (++y < game->map_height)
    {
        x = -1;
        while (++x < game->map_width)
        {
            if (copy[y][x] == 'C')
                return (0);
        }
    }
    return (1);
}

int	validate_path(t_game *game)
{
    char	**copy;
    int		result;

    copy = map_copy(game);
    if (!copy)
        error_exit("Memory allocation failed", game);
    fill(copy, game->player_x, game->player_y, game);
    result = check_path(copy, game);
    free_array(copy);
    return (result);
}
