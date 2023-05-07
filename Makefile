NAME			= so_long
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
MINILIBX_DIR	= minilibx-linux
X11_DIR 		= /usr/X11
INCLUDE			=  -I $(MINILIBX_DIR) -I/usr/include
LIBS_DIR 		=   -L$(MINILIBX_DIR) -L$(X11_DIR)/lib
LIBS 			= -lXext -lX11 -lm -lz -lmlx_Darwin -framework OpenGL -framework AppKit
VPATH 			= ./srcs
SRCS			= main.c
OBJ_DIR			= objs
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

all: $(NAME)

# $^で依存関係のあるファイル(OBJS)を全て取得
# $@で$(NAME)を取得
$(NAME): $(OBJS)
	$(MAKE) -C $(MINILIBX_DIR)
	$(CC) $(CFLAGS) $^ $(LIBS_DIR) $(LIBS) -o $@

# $<でSRCSの中の.cファイルを取得
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDE) -O3 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus .c.o