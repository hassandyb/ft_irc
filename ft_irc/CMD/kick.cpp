/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:18:57 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 21:30:04 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


void server::ft_kick_users(channel & Channel, client & Client, std::vector<std::string> Cmds)
{
    std::vector<std::string> Users = ft_split_with_comma(Cmds[2]);
    std::string reason ;
    
    if(Cmds.size() > 3)
        reason = ":" + Cmds[3];

    for(size_t i = 0; i < Users.size(); i++)
    {
        if(Channel.ft_a_member_or_admin(Users[i]) == false)// not a member or admin
        {
            std::string msg = ": 441 " + Channel.getName() + " :they aren't on that channel\r\n";
            ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
            continue;
        }
        
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " KICK " + Channel.getName() + " " + Users[i] + " " + reason + "\r\n";
        
        ft_send_msg_to_all(Channel.getAdmins(), msg);
        ft_send_msg_to_all(Channel.getMembers(), msg);
        
        if(Channel.ft_find_client("Admins", Users[i]) == true)
            Channel.ft_erase_client("Admins", Users[i]);
        if(Channel.ft_find_client("Members", Users[i]) == true)
            Channel.ft_erase_client("Members", Users[i]);
    }

    
}

void server::ft_kick(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() < 3)
    {
        std::string msg = ": 461 " + Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(ft_find_a_channel(Cmds[1]) == false)
    {
        std::string msg = ": 403 " + Client.getNickname() + " " + Cmds[1] + " :No such channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }
    channel & Channel = ft_get_a_channel(Cmds[1]);

    if(Channel.ft_find_client("Admins", Client.getNickname()) == false)
    {
        std::string msg = ": 482 " + Channel.getName() + " :You're not a channel operator\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    
    ft_kick_users(Channel, Client, Cmds);
}


