# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sderet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/13 15:33:21 by sderet            #+#    #+#              #
#    Updated: 2018/06/29 16:42:56 by sderet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = rtv1
SRCS = true_main.c display_fun.c win_crea.c color.c get_conf.c light.c \
		parser_objet.c test_obj.c tang.c primitives_intersection.c \
		intersections_general.c vec_fun.c camera.c objet.c
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
	@$(CC) $(LIBS) $(FRAMEW) -o $(NAME) $(SRCS) $(CFLAGS)
	@echo "Successfully compiled $(NAME)"
minilibx/libmlx.a:  
	@$(MAKE) -C minilibx
	@echo "Successfully compiled minilibx"
libft/libft.a:
	@$(MAKE) -C libft
	@echo "Successfully compiled libft"
$(OBJ): %.o: %.c $(HEAD)
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
