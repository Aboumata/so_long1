/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:48:57 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/20 23:49:04 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"

# define TILE_SIZE 64
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_game
{
    void	*mlx;
    void	*win;
    char	**map;
    int		map_width;
    int		map_height;
    void	*wall;
    void	*floor;
    void	*collectible;
    void	*exit;
    void	*player;
    int		player_x;
    int		player_y;
    int		collectibles;
    int		moves;
}	t_game;

typedef struct s_map_state
{
    int	x;
    int	y;
    int	has_exit;
    int	has_start;
}	t_map_state;

// Map validation
void	validate_map(char *map_file, t_game *game);
void	check_map_contents(t_game *game);
void	check_walls(t_game *game);
int		validate_path(t_game *game);
void	check_name(char *filename);
void	read_map(char *map_file, t_game *game);

// Graphics
void	load_textures(t_game *game);
void	render_map(t_game *game);

// Hooks
int		key_hook(int keycode, t_game *game);
int		close_game(t_game *game);
void	move_player(int keycode, t_game *game);

// Utils
void	error_exit(char *message, t_game *game);
void	free_game(t_game *game);
void	init_game(t_game *game);
void	free_array(char **array);
char	*ft_strdup(const char *s1);

// Libft
int	    ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putnbr_fd(int n, int fd);

#endif
