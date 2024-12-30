NAME = exec
CC = cc
CC1 = clang
CC2 = gcc
CFLAGS = -Wall -Werror -Wextra -g

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC = libft/get_next_line.c libft/gnl_utils.c libft/gnljoin.c libft/split.c libft/atoi.c \
		libft/ft_printf.c libft/printf_utils.c

OBJ = $(SRC:.c=.o)

all: day1_silver

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

day1_silver: $(OBJ) day1/trebutchet1.o
	cp day1/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day1/trebutchet1.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day1_gold: $(OBJ) day1/trebutchet2.o
	cp day1/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day1/trebutchet2.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day2_silver: $(OBJ) day2/cubes1.o
	cp day2/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day2/cubes1.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day2_gold: $(OBJ) day2/cubes2.o
	cp day2/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day2/cubes2.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day3_silver: $(OBJ) day3/engine.o
	cp day3/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day3/engine.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day3_gold: $(OBJ) day3/star.o
	cp day3/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day3/star.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day4_silver: $(OBJ) day4/cards.o
	cp day4/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day4/cards.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day4_gold: $(OBJ) day4/wins.o
	cp day4/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day4/wins.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day5_silver: $(OBJ) day5/seeds.o
	cp day5/input.txt input.txt
	cp day5/1soil.txt 1soil.txt
	cp day5/2fertil.txt 2fertil.txt
	cp day5/3water.txt 3water.txt
	cp day5/4light.txt 4light.txt
	cp day5/5temp.txt 5temp.txt
	cp day5/6humidity.txt 6humidity.txt
	cp day5/7location.txt 7location.txt
	$(CC) $(CFLAGS) $(OBJ) day5/seeds.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day6_silver: $(OBJ) day6/boat.o
	$(CC) $(CFLAGS) $(OBJ) day6/boat.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day6_gold: $(OBJ) day6/big_boat.o
	$(CC) $(CFLAGS) $(OBJ) day6/big_boat.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day7_silver: $(OBJ) day7/cards.o
	cp day7/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day7/cards.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day8_silver: $(OBJ) day8/maze.o day8/hotrace.o
	cp day8/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day8/maze.o day8/hotrace.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

day9_silver: $(OBJ) day9/oasis.o
	cp day9/input.txt input.txt
	$(CC) $(CFLAGS) $(OBJ) day9/oasis.o -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

clean:
	rm -f */*.o *.txt

fclean: clean
	rm -f $(NAME)

smooth: all clean

re:
	@$(MAKE) fclean
	@$(MAKE) all

celan:
	@echo "$(YELLOW)Lol, that's not quite what you wanted to write, huh?$(DEF_COLOR)"
	
fcelan: celan

clear: celan

strict:
	@echo "$(GREEN)Compiling with $(YELLOW)$(CC1)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CC=$(CC1)
	@echo "$(GREEN)Cleaning up...$(DEF_COLOR)"
	@$(MAKE) fclean
	@echo "$(GREEN)Compiling with $(YELLOW)$(CC2)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CC=$(CC2)
	@echo "$(GREEN)Cleaning up again...$(DEF_COLOR)"
	@$(MAKE) clean
	@echo "$(GREEN)Tested for both compilers.$(DEF_COLOR)"

.PHONY: all clean fclean re bonus strict smooth celan fcelan clear