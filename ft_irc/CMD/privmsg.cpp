/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:54:36 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 21:26:03 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


void server::ft_priv_msg_client(std::string Recipient_name, client & Client, std::string message)
{
    client & Recipient = ft_get_client(Recipient_name);

    std::string msg = ":" + Client.getNickname() + "!~" + Client.getUsername() + "@localhost PRIVMSG " + Recipient.getNickname() + " :" + message + "\r\n";
    ft_send(Recipient.getSocket(), msg.c_str(), msg.size(), 0);
}

void server::ft_priv_msg_channel(std::string Recipient_channel, client & Client, std::string message)
{
    channel & Channel = ft_get_a_channel(Recipient_channel);

    // He cant send a message to a channel if he not a member :
    if(Channel.ft_find_client("Members",Client.getNickname()) == false && Channel.ft_find_client("Admins",Client.getNickname()) == false)
    {
        std::string msg = ": 404 " + Client.getNickname() + " " + Recipient_channel + " :Cannot send to channel\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    
    // sending to all members and admins ...
    std::string msg = ":" + Client.getNickname() + "!~" + Client.getUsername() + "@localhost PRIVMSG " + Recipient_channel + " :" + message + "\r\n";
    
    std::vector<client > Members = Channel.getMembers();
    std::vector<client > Admins = Channel.getAdmins();
    
    for(size_t i = 0; i < Members.size(); i++)
    {
        if(Members[i].getNickname() != Client.getNickname())// no ned to send msg to the client why want to send the message ...
            ft_send(Members[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
    for(size_t i = 0; i < Admins.size(); i++)
    {
        if(Admins[i].getNickname() != Client.getNickname())
            ft_send(Admins[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
}

void server::ft_privmsg(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() == 1)
    {
        std::string msg = ": 411 " + Client.getNickname() + " :No recipient given (PRIVMSG)\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(Cmds.size() == 2)
    {
        std::string msg = ": 412 " + Client.getNickname() + " :No text to send\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;        
    }
    std::vector<std::string > dst = ft_split_with_comma(Cmds[1]);

    for(size_t i = 0; i < dst.size(); i++)
    {
        if(ft_find_a_client(dst[i]) == true)
        {
            ft_priv_msg_client(dst[i], Client, Cmds[2]);
        }
        else if (ft_find_a_channel(dst[i]) == true)
        {
            ft_priv_msg_channel(dst[i], Client, Cmds[2]);
        }
        else
        {
            std::string msg = ": 401 " + dst[i] + " :No such nick/channel\r\n";
            ft_send(Socket, msg.c_str(), msg.size(), 0);

        }
    }
    
}




