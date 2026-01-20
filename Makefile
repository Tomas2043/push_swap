# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/20 15:35:18 by toandrad          #+#    #+#              #
#    Updated: 2026/01/20 13:20:24 by toandrad         ###   ########.fr        #
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
					sort3.c	sort5.c	parser.c	turk_sort.c \
					turk_rotate.c	turk_utils.c turk_cost.c turk_exec.c
					

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
	@if [ ! -f tests/loop.sh ]; then \
		echo "$(RED)Error: tests/loop.sh not found!$(RESET)"; \
		exit 1; \
	fi
	@chmod +x tests/loop.sh
	@./tests/loop.sh

edge: $(NAME)
	@if [ ! -f tests/edge_tests.sh ]; then \
		echo "$(RED)Error: edge_tests.sh not found!$(RESET)"; \
		exit 1; \
	fi
	@chmod +x tests/edge_tests.sh
	@./tests/edge_tests.sh

re: fclean all

.PHONY: all clean fclean re tests edge
