/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:23:55 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/22 14:32:03 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

        //      ERR_NEEDMOREPARAMS (461)
        //      ERR_NOSUCHCHANNEL (403)
        //      ERR_NOTONCHANNEL (442)
//      :localhost 442 c #gg :You're not on that channel
//       ":" + hostname + " 403 " + nick + " " + channel + " :No such channel\r\n"

//  void server::ft_invite(std::vector<std::string> Cmds, client & Client, int Socket)


//  ":" + hostname + " 461 " + nick + " :Not enough parameters !\r\n"
//      :localhost 461 c :Not enough parameters

void server::ft_leave_channel(channel & Channel,client &  Client, std::vector<std::string> & Cmds)
{
    
    std::string reason;
    
    if(Cmds.size() >= 3)
        reason = Cmds[2];
    else
    {
        std::string empty;
        reason = empty;
    }

    
        // leave th echannel 
        // send the essage to all ..
}

void server::ft_part(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() == 1)
    {
        std::string msg = ": localhost 461 " + Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    //  PART #channel1,#channel2,#channel3 :noreason to lieave this channel
    std::vector<std::string> ChannelNames = ft_split_with_comma(Cmds[1]);

    for(size_t i = 0; i < ChannelNames.size(); i++)
    {
        if(ft_find_a_channel(ChannelNames[i]) == false)
        {
            std::string msg = ": 403 " + Client.getNickname() + " " + ChannelNames[i] + " :No such channel\r\n";
            ft_send(Socket, msg.c_str(), msg.size(), 0);
            continue ;
        }
        channel Channel = ft_get_a_channel(ChannelNames[i]);

        if(Channel.ft_a_member_or_admin(Client.getNickname()) == false)
        {
            std::string msg = ": 442 " + Channel.getName() + " :You're not on that channel\r\n";
            ft_send(Socket, msg.c_str(), msg.size(), 0);
            continue ;
        }
        

        ft_leave_channel(Channel, Client, Cmds);
    }
}

