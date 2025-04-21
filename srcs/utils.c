/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:46:48 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/20 23:46:50 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char *message, t_game *game)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	free_game(game);
	exit(1);
}

static void	free_images(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->collectible)
		mlx_destroy_image(game->mlx, game->collectible);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
			free(game->map[i++]);
		free(game->map);
	}
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		free_images(game);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->wall = NULL;
	game->floor = NULL;
	game->collectible = NULL;
	game->exit = NULL;
	game->player = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->collectibles = 0;
	game->moves = 0;
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
