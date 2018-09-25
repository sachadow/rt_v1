# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sderet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/13 15:33:21 by sderet            #+#    #+#              #
#    Updated: 2018/09/25 18:50:26 by sderet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = rtv1
SRCS_FOLDER = srcs/
SRCS = true_main.c display_fun.c win_crea.c color.c get_conf.c light.c \
		parser_objet.c test_obj.c tang.c primitives_intersection.c \
		intersections_general.c vec_fun.c camera.c objet.c \
		primitives_intersection2.c
HEAD_FOLDER = head/
HEAD = rtv1.h
LIBS = -L./libft -lft -L./minilibx -lmlx
FRAMEW = -framework OpenGL -framework Appkit
OBJ = $(SRCS:%.c=%.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

debug: CFLAGS += -g

debug: all

$(NAME): libft/libft.a minilibx/libmlx.a $(OBJ)
	@$(CC) $(LIBS) $(FRAMEW) -o $(NAME) $(OBJ) $(CFLAGS)
	@echo "Successfully compiled $(NAME)"

minilibx/libmlx.a:  
	@$(MAKE) -C minilibx
	@echo "Successfully compiled minilibx"

libft/libft.a:
	@$(MAKE) -C libft
	@echo "Successfully compiled libft"

$(OBJ): %.o: $(SRCS_FOLDER)%.c $(HEAD_FOLDER)$(HEAD)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "Successfully compiled object for $<"

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft $@
	@$(MAKE) -C minilibx $@
	@echo "$(NAME) clean successful"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft $@
	@echo "$(NAME) fclean successful"

re: fclean all
