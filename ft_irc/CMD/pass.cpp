/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:17:15 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/02 14:15:37 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


void server::ft_pass(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // Client alreadyregestred ..
    if(Client.getRegestred() == true || Client.getPassStage() == true)
    {
        std::string msg = Client.getNickname() + " (462) :You may not reregister";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    // enters more that tow args or the password worng
    if(Cmds[1] != this->getPassword() || Cmds.size() > 2)
    {
        std::string msg = Client.getNickname() + " (464) :Password incorrect";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    Client.setPassStage(true);



        
           
     
}

