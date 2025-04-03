NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3 -w 

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
PASTEL = \033[38;5;215m
RESET = \033[0m

all: $(NAME)
	@echo "$(GREEN)(っ◔◡◔)っ Philosopher$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L -lft -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(PASTEL)Object files deleted.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(PASTEL)Executable deleted..$(RESET)"

re: fclean all

re: fclean all

run: re
	./$(NAME) 5 800 200 200 10

.PHONY: all clean fclean re run
