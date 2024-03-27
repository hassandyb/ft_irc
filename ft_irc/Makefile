# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 16:07:35 by hed-dyb           #+#    #+#              #
#    Updated: 2024/03/27 18:00:20 by hed-dyb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

HEADER = HEADERS/server.hpp HEADERS/client.hpp HEADERS/channel.hpp

CC = c++

RM = rm -rf 

FLAGS = -Wall -Werror -Wextra -std=c++98 #-fsanitize=address -g3

CMD1 = $(addprefix CMD1/, cmd.cpp pass.cpp)
# CMD2 = $(addprefix CMD2/, files ....)
 SERVER = $(addprefix SERVER/, server.cpp client.cpp channel.cpp)

SRC = main.cpp $(SERVER)  $(CMD1) #$(CMD2) 

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