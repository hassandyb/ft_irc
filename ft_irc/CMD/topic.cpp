/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:40:52 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/23 14:50:43 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


//          ERR_NEEDMOREPARAMS (461) ----
//          ERR_NOSUCHCHANNEL (403) ---
//          ERR_NOTONCHANNEL (442) ---
//          ERR_CHANOPRIVSNEEDED (482) ---
//          RPL_NOTOPIC (331) ---
//          RPL_TOPIC (332)
//          RPL_TOPICWHOTIME (333)

//      TOPIC <channel> [<new_topic>]


void server::ft_topic(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() == 1)
    {
        std::string msg = ": 461 " + Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }

    if(ft_find_a_channel(Cmds[1]) == false)
    {
        std::string msg = ": 403 " + Client.getNickname() + " " + Cmds[1] + " :No such channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    channel Channel = ft_get_a_channel(Client.getNickname());    
    if(Channel.ft_a_member_or_admin(Client.getNickname()) == false)
    {
        std::string msg = ": 442 " + Channel.getName() + " :You're not on that channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(Channel.getAdminStatus() == true && Channel.ft_find_client("Admins", Client.getNickname()) == false)
    {
        std::string msg = ": 482 " + Channel.getName() + " :You're not a channel operator\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(Cmds.size() == 2)
    {
        //       : 332 a #group new_topic
        //       : 333 a #group a 1713879553
        
        // ":" + hostname + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
        // ":" + hostname + " 332 " + nick + " " + channel + " :" + setter + " has set a new topic: " + topic + "\r\n"
        
        
        // std::string msg1 = ": 332 " + Client.getNickname() + " " + 
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    //      ":" + hostname + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
    //      ":" + hostname + " 332 " + nick + " " + channel + " :" + setter + " has set a new topic: " + topic + "\r\n"
    //      ":" + hostname + " 333 " + nick + " " + channelName + " " + topicsetter + "!~" + topicsetter + "@" + hostname + " " + time + "\r\n"
    
    //      :a!a@localhost TOPIC #group new_topic
}   


