/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:17:15 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/23 18:23:43 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


void server::ft_pass(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // Client alreadyregestred ..
    if(Client.getRegestred() == true || Client.getPassStage() == true)
    {
        std::string msg = ": 462 " + Client.getNickname() + " :You may not reregister !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    if(Cmds.size() == 1)
    {
        std::string msg = ": 461 " + Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    // enters more that tow args or the password worng
    if(Cmds[1] != this->getPassword() || Cmds.size() > 2)
    {
        std::string msg = ": 464 " + Client.getNickname() + " :Password incorrect !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    Client.setPassStage(true);

}

