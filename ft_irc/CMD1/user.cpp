/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:38:48 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/02 23:27:20 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

void server::ft_user(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // did not enter the correct password yet ..
    if(Client.getPassStage() == false)
    {
        std::string msg =  " (451) :You have not registered";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    // check 4 paramters ..
    if(Cmds.size() < 5)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }

    // changing username after regestration..
    if(Client.getRegestred() == true)
    {
        std::string msg = Client.getNickname() + "(462) :You may not reregister";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }

    
    Client.setUsername(Cmds[1]);
    
    //saving realname ...
    std::string name;
    for(size_t i = 4 ; i < Cmds.size(); i++)
        name = name + Cmds[i] + " ";
    Client.setRealname(name);

    // if the nick exist we regester this clinet ...
    if((Client.getNickname()).empty() != true)
    {
        Client.setRegestred(true);
        this->Clients.push_back(Client);
        std::string msg = Client.getNickname() + " (001) :Welcome to the ft_irc Network";
        std::cout << msg << std::endl;
        ft_send(Socket, msg.c_str(), msg.size(), 0);
    }
}







