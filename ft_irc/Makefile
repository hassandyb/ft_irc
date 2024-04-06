# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 16:07:35 by hed-dyb           #+#    #+#              #
#    Updated: 2024/04/06 18:46:37 by hed-dyb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

HEADER = HEADERS/server.hpp HEADERS/client.hpp HEADERS/channel.hpp

CC = c++

RM = rm -rf 

FLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3

CMD = $(addprefix CMD/, cmd.cpp pass.cpp nick.cpp user.cpp join.cpp invite.cpp privmsg.cpp)

 SERVER = $(addprefix SERVER/, server.cpp client.cpp channel.cpp)

SRC = main.cpp $(SERVER)  $(CMD)

OBJECTS = ./OBJECT_FILES

OBJ = $(addprefix $(OBJECTS)/, $(SRC:.cpp=.o))

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS)  $(OBJ) -o $(NAME)
	
$(OBJECTS)/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(FLAGS)  -c $< -o $@

clean :
	$(RM) $(OBJECTS)

fclean : clean
	$(RM) $(NAME)

re : fclean all