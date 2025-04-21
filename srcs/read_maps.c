/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:16:42 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/21 19:16:43 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_line(char *line, int *last_non_empty, int line_count,
		t_game *game)
{
	char	*nl;

	nl = ft_strchr(line, '\n');
	if (nl)
		*nl = '\0';
	game->map[line_count] = line;
	if (ft_strlen(line) > 0)
		*last_non_empty = line_count;
}

static void	map_dimensions(t_game *game, int line_count, int last_non_empty)
{
	int	i;

	game->map[line_count] = NULL;
	if (last_non_empty == -1)
		error_exit("Map is empty", game);
	game->map_height = last_non_empty + 1;
	game->map_width = ft_strlen(game->map[0]);
	i = 0;
	while (i < game->map_height)
	{
		if (ft_strlen(game->map[i]) != game->map_width)
			error_exit("Map is not rectangular", game);
		i++;
	}
}

void	read_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	int		line_count;
	int		last_non_empty;

	line_count = 0;
	last_non_empty = -1;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Map file not found", game);
	game->map = malloc(sizeof(char *) * 1024);
	if (!game->map)
		error_exit("Malloc failed", game);
	line = get_next_line(fd);
	while (line)
	{
		handle_line(line, &last_non_empty, line_count, game);
		line_count++;
		line = get_next_line(fd);
	}
	close(fd);
	map_dimensions(game, line_count, last_non_empty);
}
