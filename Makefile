CC = gcc
CFLAGS = -I include/

SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/

SRC = $(notdir $(wildcard $(SRCDIR)*.c))
OBJ = $(SRC:.c=.o)
BIN = minishell

RM = rm -rf

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(BINDIR)$(BIN): $(addprefix $(OBJDIR), $(OBJ))
	$(CC) $^ -o $@
	
all: $(BINDIR)$(BIN)
	
re: fclean all

clean:
	$(RM) $(addprefix $(OBJDIR), $(OBJ))
	
fclean: clean
	$(RM) $(BINDIR)$(BIN)

.PHONY: all re clean fclean
