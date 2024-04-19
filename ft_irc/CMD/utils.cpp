/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:30:38 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/19 14:36:50 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

bool server::ft_send(int socket, const void * buff, size_t len, int flags)
{

    // for testing ...only
    (void)socket;
    (void)len;
    (void)flags;
    char *msg = (char *)buff;
    std::cout << msg << std::endl;
    




    
    // ssize_t r =  send(socket, buff, len, flags);
    // if(r == -1)// send faliere
    // {
    //     std::cerr << "Send() failed to send respond!" << std::endl;
    //     return false;
    // }
    return true;
}

bool server::ft_is_registred(client & Client, int Socket)
{
    if(Client.getRegestred() == false)
    {
        std::string msg = Client.getNickname() + " (451) :You have not registered";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return false;
    }
    return true;
}

void server::ft_send_msg_to_all(std::vector<client> Clients, std::string msg)
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        ft_send(Clients[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
}