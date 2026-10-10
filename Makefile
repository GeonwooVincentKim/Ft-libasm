NAME		= libasm.a

AS			= nasm
ASFLAGS		= -f elf64
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar
ARFLAGS		= rcs
RM			= rm -f

SRCS		= ft_strlen.s \
			  ft_strcpy.s \
			  ft_strcmp.s \
			  ft_write.s \
			  ft_read.s \
			  ft_strdup.s \
			  ft_calloc.s

OBJS		= $(SRCS:.s=.o)

TEST_NAME	= testhook
TEST_SRC	= main.c

.DEFAULT_GOAL	:= all

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

$(TEST_NAME): $(NAME) $(TEST_SRC) libasm.h
	$(CC) $(CFLAGS) $(TEST_SRC) -L. -lasm -o $(TEST_NAME)

test: $(TEST_NAME)
	./$(TEST_NAME)

.PHONY: all clean fclean re test
