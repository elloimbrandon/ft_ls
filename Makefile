SRCS = ./SRCS/ft_ls.c ./SRCS/handles.c ./SRCS/parse_tools.c ./SRCS/printing.c ./SRCS/sort.c ./SRCS/path.c

FLAGS = -Wall -Wextra -Werror

NAME = ft_ls

LIBFT = libft

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@gcc $(FLAGS) $(SRCS) -L $(LIBFT) -lft -o $(NAME)

clean:
	@rm -rf $(NAME)
	@rm -rf ft_ls.dSYM
	@make clean -C $(LIBFT)

fclean: clean
	@make fclean -C $(LIBFT)

re: fclean all

debug:
	@gcc $(FLAGS) $(SRCS) -L $(LIBFT) -lft -o $(NAME) -g -fsanitize=address


