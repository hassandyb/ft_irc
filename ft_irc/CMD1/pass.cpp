/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:17:15 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/28 15:29:32 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


// bool server::ft_send(int socket, const void * buff, size_t len, int flags);


void server::ft_pass(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // Client alreadyregestred ..
    if(Client.getRegestred() == true || Client.getPassStage() == true)
    {
        std::string msg = Client.getNickname() + " :You may not reregister";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    // enters more that tow args or the password worng
    if(Cmds[1] != this->getPassword() || Cmds.size() > 2)
    {
        std::string msg = Client.getNickname() + " :Password incorrect";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    Client.setPassStage(true);
     
}

