/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:12 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/28 16:42:29 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// bool server::ft_send(int socket, const void * buff, size_t len, int flags);

bool server::ft_nick_already_used(std::string nick)
{
    for(int i = 0; i < this->Clients.size(); i++)
    {
        if(Clients[i].getNickname() == nick)
            return true;
    }
    return false;
}


void server::ft_nick(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // did not enter the correct password yet ..
    if(Client.getPassStage() == false)
    {
        std::string msg =  Client.getNickname() + " :You have not registered!";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " :No nickname given.";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    //  Erroneus nickname cases
    char first_char = Cmds[1].at(0);
    if(Cmds.size() > 2 || std::isdigit(first_char) == true || ft_nick_already_used(Client.getNickname()) == true)// we need a args and the nickname must start witha char , or thet ....
    {
        std::string msg = Client.getNickname() + " :Erroneus nickname";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;       
    }
    if(Cmds[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
    {
        std::string msg = Client.getNickname() + " :Erroneus nickname";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;       
    }

    
    Client.setNickname(Cmds[1]);
    // now if the username exist  == we regestred this clinet by changing Regestred to true, and add him to clients
    if((Client.getUsername()).empty() != true)
    {
        Client.setRegestred(true);
        this->Clients.push_back(Client);
    }
        

}

