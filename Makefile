# -*- Makefile -*-

NAME        = so_long

SRCS_DIR    = srcs
LIBFT_DIR   = libft
MLX_DIR     = libs/minilibx-linux

SRCS        = $(SRCS_DIR)/main.c \
              $(SRCS_DIR)/map_validation.c \
              $(SRCS_DIR)/graphics.c \
              $(SRCS_DIR)/hooks.c \
              $(SRCS_DIR)/utils.c \
              $(SRCS_DIR)/flood_fill.c

LIBFT_SRCS  = $(LIBFT_DIR)/ft_strlen.c \
              $(LIBFT_DIR)/ft_strchr.c \
              $(LIBFT_DIR)/ft_memset.c \
              $(LIBFT_DIR)/get_next_line.c \
              $(LIBFT_DIR)/get_next_line_utils.c

OBJS        = $(SRCS:.c=.o)
LIBFT_OBJS  = $(LIBFT_SRCS:.c=.o)

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11
INCLUDES    = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)

GREEN       = \033[0;32m
RED         = \033[0;31m
NC          = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@echo "$(GREEN)Building minilibx...$(NC)"
	@make -s -C $(MLX_DIR)
	@echo "$(GREEN)Linking everything...$(NC)"
	@$(CC) $(CFLAGS) $^ $(MLX_FLAGS) -o $@
	@echo "$(GREEN)Done! Run with ./$(NAME) maps/map1.ber$(NC)"

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_OBJS): %.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	@echo "$(RED)Removing executable...$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
