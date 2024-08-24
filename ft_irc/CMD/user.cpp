/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:38:48 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/24 20:24:00 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

void server::ft_user(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // did not enter the correct password yet ..
    if(Client.getPassStage() == false)
    {
        std::string msg =  ": 451 :You have not registered !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    // check 4 paramters ..
    if(Cmds.size() < 5)
    {
        std::string msg = ": 461 " + Client.getNickname() + " " + Cmds[0] + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }

    // changing username after regestration..
    if(Client.getRegestred() == true)
    {
        std::string msg = ": 462 " + Client.getNickname() + " :You may not reregister !\r\n";
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
        // this->Clients.push_back(Client);  // already set in the server
        std::string msg = ": 001 " + Client.getNickname() + " :Welcome to the ft_irc Network\r\n";
        std::cout << msg << std::endl;
        ft_send(Socket, msg.c_str(), msg.size(), 0);
    }
}







