# project
NAME = pipex

# compiler
CC = CC
CFLAGS = -Wall -Wextra -Werror -pthread -I includes/
RM = rm -rf

# files
SRC_DIR = scr/
MAIN = main \
MAIN_BONUS = main_bonus \
FILES =	 \

SRC_MAIN = $(addsuffix .c, $(addprefix $(SRC_DIR), $(MAIN)))
SRC = $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILES)))
OBJ_MAIN = $(SRC_MAIN:.c=.o)
OBJ = $(SRC:.c=.o)

# esthetic
TOTAL = $(words $(SRCS))
COUNT = 0

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
