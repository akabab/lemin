# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/03 16:39:11 by ycribier          #+#    #+#              #
#    Updated: 2014/03/23 18:01:45 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc -g -O2 #$(FLAGS)
FLAGS			=	-Wall -Wextra -Werror
NAME			=	lem-in
LIB				=	libft/libft.a
LIB_PATH		=	libft/
INCLUDES		=	./includes
SRCS			=	src/lemin.c				\
					src/arg.c				\
					src/entry.c				\
					src/manage_entry.c		\
					src/resolve.c			\
					src/bfs.c				\
					src/path_opti.c			\
					src/travel.c			\
					src/free.c				\
					src/lem_htable.c		\
					src/lem_hft.c			\
					src/lem_htable_rm.c		\
					src/dbg.c				\
					src/err.c
OBJS			=	$(SRCS:src/%.c=obj/%.o)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: obj $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) -o $@ $^ -L $(LIB_PATH) -lft
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

$(LIB):
	@make -C $(LIB_PATH)

obj:
	@mkdir -p obj

obj/%.o: src/%.c $(INCLUDES)/lemin.h
	@$(CC) -c -o $@ $< -I $(LIB_PATH)$(INCLUDES) -I $(INCLUDES)
	@echo "Linking" [ $< ] $(OK)

clean:
	@rm -f $(OBJS)
	@rm -rf obj
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: all clean fclean re
