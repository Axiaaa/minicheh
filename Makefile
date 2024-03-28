NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
HEADER = -I inc -I libft
DEPS = inc/minishell.h \
       inc/struct.h \
       inc/collector.h \
       inc/pipex.h
LIBFT = libft/libft.a
SRCS =	build_in/built_in_echo.c \
	build_in/built_in_env.c \
	build_in/built_in_exit.c \
	build_in/build_in_unset.c \
	build_in/build_in_pwd.c \
	build_in/build_in_export.c \
	build_in/build_in_export_2.c \
	build_in/build_in_cd.c \
	build_in/built_in_utils.c \
	more_env_utils.c \
	create_envp.c \
	get_new_line.c \
	quote_stuff.c \
	loop_minishell.c \
	main.c \
	replace_str.c \
	sig.c \
	here_doc.c \
	here_doc_utils.c \
	redirections.c \
	redirections_utils.c \
	env_utils.c \
	execution.c \
	garbage_collector.c \
	defines.c \
	kind_of_pipex/almost_libft_utils.c \
	kind_of_pipex/execve_stuff.c \
	kind_of_pipex/ft_strjoins.c \
	kind_of_pipex/open_close_free.c \
	kind_of_pipex/pipex.c \
	kind_of_pipex/minishell_part.c \

SRCS_DIR = $(addprefix srcs/, $(SRCS))
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME) end

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(HEADER) -Llibft -lft -lreadline

$(OBJS_DIR)/%.o: srcs/%.c $(DEPS)
	mkdir -p $(OBJS_DIR)/kind_of_pipex
	mkdir -p $(OBJS_DIR)/build_in
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@ -I./inc -I./libft

$(LIBFT):
	cd ./libft && $(MAKE) all


end : 
	@echo "\033[1;31m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗		\033[0m"  
	@echo "\033[1;38;2;255;165;0m████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║		\033[0m"  
	@echo "\033[1;33m██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \033[0m"
	@echo "\033[1;32m██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \033[0m"
	@echo "\033[1;36m██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\033[0m"
	@echo "\033[1;38;2;128;0;128m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\033[0m"
	

clean:
	rm -rf $(OBJS_DIR)
	cd ./libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd ./libft && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re end 
