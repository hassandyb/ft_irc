/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:12 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/31 14:17:56 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

void server::ft_inform_clients(std::string msg)
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        ft_send(Clients[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
}

bool server::ft_nick_already_used(std::string nick)
{
    for(size_t i = 0; i < this->Clients.size(); i++)
    {
         std::cout << Clients[i].getNickname() <<  "  " << nick << std::endl;
        if(Clients[i].getNickname() == nick)
        {
           
            return true;
        }
            
    }
    return false;
}


void server::ft_nick(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // did not enter the correct password yet ..
    if(Client.getPassStage() == false)
    {

        std::string msg =  Client.getNickname() + " (451) :You have not registered";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " (431) :No nickname given.";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    //  Erroneus nickname cases
    char first_char = Cmds[1].at(0);
    // too many args, first paramter is gigit , emty nickname
    if(Cmds.size() > 2 || std::isdigit(first_char) == true || Cmds[1].empty() == true)// we need a args and the nickname must start witha char , or thet ....
    {
        std::string msg = Client.getNickname() + " (432) :Erroneus nickname";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;       
    }
    if(ft_nick_already_used(Cmds[1]) == true)
    {
        std::string msg = Client.getNickname() + " (433) :Nickname is already in use";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;          
    }
    if(Cmds[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
    {
        std::string msg =  Client.getNickname() + " (432) :Erroneus nickname";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;       
    }

    
    // changing the nick name after regestration..
    if(Client.getRegestred() == true)
    {
        std::string msg = Client.getNickname() + " changed his nickname to " + Cmds[1] + ".";
        std::cout << msg << std::endl;
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        Client.setNickname(Cmds[1]);
        ft_inform_clients(msg);
        return ;
    }
    
    Client.setNickname(Cmds[1]);
    // now if the username exist  == we regestred this clinet 
    if((Client.getUsername()).empty() != true)
    {
        Client.setRegestred(true);
        this->Clients.push_back(Client);
        std::string msg = Client.getNickname() + " (001) :Welcome to the ft_irc Network";
        std::cout << msg << std::endl;
        ft_send(Socket, msg.c_str(), msg.size(), 0);
    }

}

