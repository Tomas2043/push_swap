# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/20 15:35:18 by toandrad          #+#    #+#              #
#    Updated: 2025/09/25 10:34:56 by toandrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================ #

# Program name
NAME		= push_swap

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# Colors for output
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
BLUE		= \033[0;34m
RED			= \033[0;31m
BOLD		= \033[1m
RESET		= \033[0m

# Directories
SRCDIR		= srcs
OBJSDIR		= objects
INCDIR		= inc
LIBFT_DIR	= libft
PRINTF_DIR	= $(LIBFT_DIR)/ft_printf
VPATH = $(SRCDIR) $(SRCDIR)/moves

# Source files
SRCS		= main.c	push_pop.c	push.c	reverse_rotate.c \
					rotate.c	swap.c	stack_utils.c	utils_order.c \
					sort3.c	sort5.c	parser.c	debug.c	turk_sort.c \
					turk_rotate.c	turk_utils.c	turk_cost.c
					

# Object files
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a
PRINTF		= $(PRINTF_DIR)/libftprintf.a

# ================================== RULES ================================== #

# Default target
all: $(NAME)

# Build libraries
$(LIBFT):
	@echo "$(YELLOW)🛠️  Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✅ libft built successfully.$(RESET)"

$(PRINTF):
	@echo "$(YELLOW)🛠️  Building ft_printf..."
	@$(MAKE) -C $(PRINTF_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✅ ft_printf built successfully.$(RESET)"

# Build main executable
$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@echo "$(YELLOW)🛠️  Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -I$(INCDIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -o $(NAME)
	@echo "$(GREEN)✅ Executable created: $(BLUE)$(NAME)$(RESET)"

# Compile object files
$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
	@echo "$(YELLOW)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -c $< -o $@

# Create objects directory
$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

# Clean object files
clean:
	@rm -rf $(OBJSDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(PRINTF_DIR) clean > /dev/null 2>&1
	@echo "$(RED)🧹 Object files deleted.$(RESET)"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@$(MAKE) -C $(PRINTF_DIR) fclean > /dev/null 2>&1
	@echo "$(RED)🗑️  All generated files deleted.$(RESET)"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
