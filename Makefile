# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/20 15:35:18 by toandrad          #+#    #+#              #
#    Updated: 2025/12/12 14:09:27 by toandrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

GREEN		= \033[0;32m
YELLOW		= \033[1;33m
BLUE		= \033[0;34m
RED			= \033[0;31m
BOLD		= \033[1m
RESET		= \033[0m

SRCDIR		= srcs
OBJSDIR		= objects
INCDIR		= inc
LIBFT_DIR	= libft
PRINTF_DIR	= $(LIBFT_DIR)/ft_printf
VPATH = $(SRCDIR) $(SRCDIR)/moves

SRCS		= main.c	push_pop.c	push.c	reverse_rotate.c \
					rotate.c	swap.c	stack_utils.c	utils_order.c \
					sort3.c	sort5.c	parser.c	debug.c	turk_sort.c \
					turk_rotate.c	turk_utils.c	turk_cost.c
					

OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

LIBFT		= $(LIBFT_DIR)/libft.a
PRINTF		= $(PRINTF_DIR)/libftprintf.a

# ================================== RULES ================================== #

all: $(NAME)

$(LIBFT):
	@echo "$(YELLOW)🛠️  Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✅ libft built successfully.$(RESET)"

$(PRINTF):
	@echo "$(YELLOW)🛠️  Building ft_printf..."
	@$(MAKE) -C $(PRINTF_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✅ ft_printf built successfully.$(RESET)"

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@echo "$(YELLOW)🛠️  Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -I$(INCDIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -o $(NAME)
	@echo "$(GREEN)✅ Executable created: $(BLUE)$(NAME)$(RESET)"

$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
	@echo "$(YELLOW)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean:
	@rm -rf $(OBJSDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(PRINTF_DIR) clean > /dev/null 2>&1
	@echo "$(RED)🧹 Object files deleted.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@$(MAKE) -C $(PRINTF_DIR) fclean > /dev/null 2>&1
	@echo "$(RED)🗑️  All generated files deleted.$(RESET)"

tests: $(NAME)
	@echo "$(BLUE)Running tests...$(RESET)"
	@echo ""
	@echo "$(YELLOW)Test 1: 3 Numbers$(RESET)"
	@./$(NAME) 2 1 3 | wc -l
	@echo ""
	@echo "$(YELLOW)Test 2: 5 numbers$(RESET)"
	@ARG="$$(shuf -i 0-100 -n 5 | tr '\n' ' ')"; \
	echo "Numbers: $$ARG"; \
	./$(NAME) $$ARG | wc -l
	@echo ""
	@echo "$(YELLOW)Test 3: 100 numbers$(RESET)"
	@ARG="$$(shuf -i 0-5000 -n 100 | tr '\n' ' ')"; \
	MOVES=$$(./$(NAME) $$ARG | wc -l); \
	echo "Moves: $$MOVES"
	@echo ""
	@echo "$(YELLOW)Test 4: 500 Numbers$(RESET)"
	@ARG="$$(shuf -i 0-5000 -n 500 | tr '\n' ' ')"; \
	MOVES=$$(./$(NAME) $$ARG | wc -l); \
	echo "Moves: $$MOVES"
	@echo ""
	@echo "$(YELLOW)Test 5: Already sorted$(RESET)"
	@./$(NAME) 1 2 3 4 5 | wc -l
	@echo ""
	@echo "$(YELLOW)Test 6: Error - duplicates$(RESET)"
	@./$(NAME) 1 2 3 2 2>&1 || echo "Error detected ✓"
	@echo ""
	@echo "$(GREEN)Tests complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re tests
