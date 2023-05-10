NAME			= so_long
CC				= cc
CFLAGS			= -Wall -Wextra -Werror 
MINILIBX_DIR	= minilibx-linux
GNL_DIR			= get_next_line
PRINTF_DIR		= ft_printf
X11_DIR 		= /usr/X11
INCLUDE			=  -I$(MINILIBX_DIR) -I/usr/include -I$(GNL_DIR)/include -I$(PRINTF_DIR)/include
LIBS_DIR 		=  -L$(MINILIBX_DIR) -L$(X11_DIR)/lib
LIBS 			= -lXext -lX11 -lm -lz -lmlx_Darwin -framework OpenGL -framework AppKit $(GNL_DIR)/get_next_line.a $(PRINTF_DIR)/libftprintf.a
VPATH 			= ./srcs
SRCS			= main.c
OBJ_DIR			= objs
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

all: $(NAME)

# $^で依存関係のあるファイル(OBJS)を全て取得
# $@で$(NAME)を取得
$(NAME): $(OBJS)
	$(MAKE) -C $(MINILIBX_DIR)
	$(MAKE) -C $(GNL_DIR)
	$(MAKE) -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $^ $(LIBS_DIR) $(LIBS) -o $@

# $<でSRCSの中の.cファイルを取得
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(INCLUDE) -O3 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(MINILIBX_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(GNL_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)


re: fclean all

.PHONY: all clean fclean re bonus .c.o