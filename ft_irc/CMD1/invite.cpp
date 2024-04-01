/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:07:14 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/01 22:52:10 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// invite <nickname> <channel>

void server::ft_invite(std::vector<std::string> Cmds, client & Client, int Socket)
{
    (void)Cmds;
    (void)Client;
    (void)Socket;

    if(Cmds.size() != 3)
    {
        std::string msg = Client.getNickname() + " invite (461) :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }


    // client do not exist (not regestred) - channel does not exist ..

    if(ft_find_a_client(Cmds[1]) == false || ft_find_a_channel(Cmds[2]) == false)
    {
        std::string msg = Client.getNickname() + " (401) :No such nick/channel";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    // Client exscuting this comand not a  member/admine on this channel 
    channel Channel = ft_get_a_channel(Cmds[2]);
    if(Channel.ft_a_member_or_admin(Client.getNickname()) == false)
    {
        std::string msg = Client.getNickname() + " " + Cmds[2] + " (442) :You're not on that channel";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    // now you chould check if the person been invited getes a message if yes then you hsould send his too 
}





