/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:12 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/28 15:37:41 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// bool server::ft_send(int socket, const void * buff, size_t len, int flags);


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
    if(Cmds.size() > 2 || )
    {
        std::string msg = Client.getNickname() + " :Erroneus nickname";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;       
    }
}

