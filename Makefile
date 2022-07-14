# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coder <coder@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 19:19:40 by vwildner          #+#    #+#              #
#    Updated: 2022/07/14 23:47:49 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

EXTERNAL_LIBS = -lpthread

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q --tool=memcheck

SAFE_MKDIR = mkdir -p

COPY = cp -p

REMOVE = rm -rf

OBJECTS_PATH = ./objects
SOURCES_PATH = ./sources
INCLUDES_PATH = ./includes

ARCHIVES_PATH = ./archives

HEADER_FILE = philo.h
HEADER = $(addprefix $(INCLUDES_PATH)/,$(HEADER_FILE))

SOURCE_FILES =	main.c \
				init.c \
				feast.c \
				helpers.c \
				jobs.c

SOURCES = $(addprefix $(SOURCES_PATH)/,$(SOURCE_FILES))

OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(subst .c,.o,$(SOURCE_FILES)))

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif


all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	@$(CC) $(CFLAGS) -w -g $(OBJECTS) -o $(NAME) -L $(ARCHIVES_PATH) -I $(INCLUDES_PATH) $(EXTERNAL_LIBS)

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.c $(HEADER)
	@$(SAFE_MKDIR) $(OBJECTS_PATH)
	@$(CC) $(CFLAGS) -g -I $(INCLUDES_PATH) -o $@ -c $<

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $(RUN_ARGS)

re:	fclean all

archives_clean:
	$(REMOVE) $(ARCHIVES_PATH)

clean:
	$(REMOVE) $(OBJECTS_PATH)

fclean: clean archives_clean
	$(REMOVE) $(NAME)

.PHONY: all run valgrind re fclean clean archives_clean libft_clean
