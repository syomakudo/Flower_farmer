NAME			= get_next_line.a
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
INCLUDE			= -I ./include
SRCS_DIR		= ./srcs
SRCS			= get_next_line_utils.c \
					get_next_line.c
OBJ_DIR			= objs
#オブジェクトファイルの作成
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

#オブジェクトファイルが作られたら、ディレクトリを作成してからオブジェクトファイルを配下に置く。その後コンパイル。
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
