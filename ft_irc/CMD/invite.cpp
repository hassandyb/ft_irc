/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:07:14 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 21:28:51 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"




void server::ft_invite(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() != 3)
    {
        
        std::string msg = ": 461 " + Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(ft_find_a_client(Cmds[1]) == false)
    {
        std::string msg = ":localhost 401 " +  Cmds[1] + " :No such nick\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(ft_find_a_channel(Cmds[2]) == false)
    {
        std::string msg = ": 403 " + Cmds[2] + " :No such channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    // Client exscuting this comand not an admine on this channel 
    channel & Channel = ft_get_a_channel(Cmds[2]);
    if(Channel.ft_find_client("Admins", Client.getNickname()) == false)
    {
        std::string msg = ": 482 " + Cmds[2] + ":You're not a channel operator\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    
    // the client been invited is already a memeber/admin ...
    client & InvitedClient = ft_get_client(Cmds[1]);
    if(Channel.ft_a_member_or_admin(InvitedClient.getNickname()) == true)
    {

        std::string msg = ": 443 " + Client.getNickname() + " " + Cmds[2] + " :is already on channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }


    // add to invite list... succusful invitation
    Channel.ft_add_invited(InvitedClient);
    
    std::string msg1 = ": 341 " + Client.getNickname() + " " + Cmds[1] + " " + Cmds[2] + " :Inviting " + Cmds[1] + " to " + Cmds[2] + "\r\n";
    std::string msg2 = ":" + InvitedClient.getNickname() + "!" + InvitedClient.getUsername() + " INVITE " + InvitedClient.getNickname() + " " + Cmds[2] + "\r\n";


    
    ft_send(Socket, msg1.c_str(), msg1.size(), 0);
    ft_send(InvitedClient.getSocket(), msg2.c_str(), msg2.size(), 0);
}





