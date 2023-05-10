CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	libftprintf.a
LIBFT_NAME	=	./libft/libft.a
INCLUDE			= -I ./include
SRCS_DIR		= ./srcs
SRCS		=	ft_printf.c \
				ft_put_func1.c
OBJ_DIR			= objs
#オブジェクトファイルの作成
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT_NAME)
			cp $(LIBFT_NAME) $(NAME)
			ar rcs $(NAME) $(OBJS)

#オブジェクトファイルが作られたら、ディレクトリを作成してからオブジェクトファイルを配下に置く。その後コンパイル。
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT_NAME):
			$(MAKE) -C ./libft

clean:
			$(RM) -rf $(OBJ_DIR)
			$(MAKE) clean -C ./libft

fclean:		clean
			rm -f $(NAME) $(LIBFT_NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
