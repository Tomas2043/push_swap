# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:23:27 by toandrad          #+#    #+#              #
#    Updated: 2025/07/21 22:47:38 by toandrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
AR = ar rcs

SRCS =	ft_printf.c \
		utils/ft_putchar.c \
		utils/ft_puthex.c \
		utils/ft_putnbr.c \
		utils/ft_putptr.c \
		utils/ft_putstr.c \
		utils/ft_putunsigned.c

OBJSDIR = objects
SRC_NAMES = $(notdir $(SRCS))
OBJS = $(addprefix $(OBJSDIR)/, $(SRC_NAMES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "🛠️  Compiling ft_printf..."
	@$(AR) $(NAME) $(OBJS)
	@echo "✅ Finished compiling ft_printf."

$(OBJSDIR)/%.o: %.c ft_printf.h | $(OBJSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: utils/%.c ft_printf.h | $(OBJSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean:
	@rm -rf $(OBJSDIR)
	@echo "🧹 Printf object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  libftprintf.a deleted."

re: fclean all

.PHONY: all clean fclean re
