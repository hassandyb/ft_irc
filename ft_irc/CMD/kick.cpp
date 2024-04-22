/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:18:57 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/22 17:04:08 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"




//                Numeric Replies:
//
//                ERR_NEEDMOREPARAMS (461)     1111
//                ERR_NOSUCHCHANNEL (403)       11
//                ERR_CHANOPRIVSNEEDED (482) 1
//                ERR_USERNOTINCHANNEL (441)
//                ERR_NOTONCHANNEL (442)
//                Deprecated Numeric Reply:
//
//                ERR_BADCHANMASK (476)


//      KICK #channel1 user1,user2,user3 :Breaking the rules

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
    channel Channel = ft_get_a_channel(Cmds[1]);

    if(Channel.ft_find_client("Admins", Client.getNickname()) == false)
    {
        std::string msg = ": 482 " + Channel.getName() + " " + ":You're not a channel operator\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    std::vector<std::string> Users = ft_split_with_comma(Cmds[2]);

    

    
}


