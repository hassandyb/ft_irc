/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:40:52 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 12:53:49 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


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
    channel & Channel = ft_get_a_channel(Cmds[1]);    
    if(Channel.ft_a_member_or_admin(Client.getNickname()) == false)
    {
        std::string msg = ": 442 " + Channel.getName() + " :You're not on that channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(Channel.getTopicStatus() == true && Channel.ft_find_client("Admins", Client.getNickname()) == false)
    {
        std::string msg = ": 482 " + Channel.getName() + " :You're not a channel operator\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    if(Cmds.size() == 2 && Channel.getTopic().empty() == true)
    {
        std::string msg = ": 331 " + Client.getNickname() + " " + Channel.getName() + " :No topic is set\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    
    if(Cmds.size() == 2 && Channel.getTopic().empty() != true)
    {
        std::string msg1 = ": 332 " + Client.getNickname() + " " + Channel.getName() + " :" + Channel.getTopic() + "\r\n";
        std::string msg2 = ": 333" + Client.getNickname() + " " + Channel.getName() + " " + Client.getNickname() + " " + Channel.ft_get_topic_time() + "\r\n";
        ft_send(Socket, msg1.c_str(), msg1.size(), 0);
        ft_send(Socket, msg2.c_str(), msg2.size(), 0);
        return ;

    }
    Channel.ft_save_topic_time();
    Channel.setTopic(Cmds[2]);
    std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " TOPIC " + Channel.getName() + " " + Channel.getTopic() + "\r\n";
    
    ft_send_msg_to_all(Channel.getAdmins(), msg);
    ft_send_msg_to_all(Channel.getMembers(), msg);
}   


