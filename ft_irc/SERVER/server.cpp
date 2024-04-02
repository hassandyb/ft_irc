/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:08:02 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/02 12:44:53 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// Canonical form : ----------------




server::server(char * port, char * Password)
{
    this->Port = atoi((const char *)port);
    std::string pass(Password);
    this->Password = pass;
}



// Setters ---------------------
void server::setSocket(int Socket) {this->Socket = Socket;}
void server::setPort(int Port) {this->Port = Port;}
void server::setPassword(std::string Password) {this->Password = Password;}

// Getters ---------------------
int server::getSocket() {return this->Socket;}
int server::getPort() {return this->Port;}
std::string server::getPassword() {return this->Password;}




// Utils -----------------------------------

bool server::ft_find_a_client(std::string Nick)
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        if(Clients[i].getNickname() == Nick)
            return true;
    }
    return false;
}

bool server::ft_find_a_channel(std::string Channel_name)
{
    for(size_t i = 0; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel_name)
            return true;
    }
    return false;
}

channel & server::ft_get_a_channel(std::string Channel_name)
{
    size_t i = 0;
    for(i = 0 ; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel_name)
            return Channels[i];
    }
    return Channels[i]; 
}


client & server::ft_get_client(std::string nick)
{
    size_t i ;
    for( i = 0; i < Clients.size(); i++)
    {
        if(Clients[i].getNickname() == nick)
            return Clients[i];
    }
    return Clients[i];
}
