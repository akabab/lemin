# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/26 16:39:11 by ycribier          #+#    #+#              #
#    Updated: 2014/03/13 14:18:43 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc -g -O2 $(FLAGS)
FLAGS			=	-Wall -Wextra -Werror
NAME			=	lem-in
LIB				=	libft/libft.a
LIB_PATH		=	libft/
INCLUDES		=	./includes
SRCS			=	lemin.c				\
					arg.c				\
					entry.c				\
					manage_entry.c		\
					resolve.c			\
					bfs.c				\
					path_opti.c			\
					travel.c			\
					free.c				\
					lem_htable.c		\
					lem_hft.c			\
					lem_htable_rm.c		\
					dbg.c				\
					err.c
OBJS			=	$(SRCS:.c=.o)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) -o $@ $^ -L $(LIB_PATH) -lft
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

$(LIB):
	make -C $(LIB_PATH)

%.o: %.c $(INCLUDES)/lemin.h
	@$(CC) -c -o $@ $< -I $(LIB_PATH)$(INCLUDES) -I $(INCLUDES)
	@echo "Linking" [ $< ] $(OK)

clean:
	@rm -f $(OBJS)
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: all clean fclean re
