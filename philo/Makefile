NAME = philo

CC = cc
CFLAGS = -g3 -w -Wall -Wextra -Werror #-fsanitize=thread

SRCS = src/init_data.c \
       src/monitor.c \
       src/philo_life.c \
       src/philo_action.c \
       src/philo_print.c \
       src/philo_start.c \
       src/utils.c \
       src/main.c

OBJ_DIR = obj
OBJ = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

GREEN = \033[38;5;82m
PINK = \033[38;5;213m
RESET = \033[0m

all: $(NAME)
	@echo "$(GREEN)(っ◔◡◔)っ Philosopher$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L -lft -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Fichiers objets supprimés.$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)Exécutable supprimé.$(RESET)"

re: fclean all

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re run
