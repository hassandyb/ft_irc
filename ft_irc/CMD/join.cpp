/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:36:59 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 20:09:46 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

bool server::ft_channel_exist(std::string channel_name)
{
    for(size_t i = 0; i < Channels.size() ; i++)
    {
        if(channel_name == Channels[i].getName())
            return true;
    }
    return false;
}

void server::ft_join_message(std::string & channel_name, client & Client, channel & new_channel)
{
    std::string msg1 = ":" + Client.getNickname() + "!" + Client.getUsername() + "@127.0.0.1 JOIN " + channel_name + "\r\n";
    std::string msg2 = ": 353 " + Client.getNickname() + " @ " + channel_name + " :" + new_channel.ft_list_admins_and_members() + "\r\n";
    std::string msg3 = ": 366 " + Client.getNickname() + " " + channel_name + " :End of /NAMES list" + "\r\n";
    
    // send to client 
    ft_send(Client.getSocket(), msg1.c_str(), msg1.size(), 0);
    ft_send(Client.getSocket(), msg2.c_str(), msg2.size(), 0);
    ft_send(Client.getSocket(), msg3.c_str(), msg3.size(), 0);
    
    // desplay on the server ...

    std::cout << msg1 << msg2 << msg3;
       
}

void server::ft_inform_the_rest(channel & Channel, client & Client)
{

    std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + "@127.0.0.1 JOIN " + Channel.getName() + "\r\n";

    std::vector<client> Members = Channel.getMembers();
    for(size_t i = 0; i < Members.size(); i++)
    {
        if(Members[i].getNickname() == Client.getNickname())
            continue;
        ft_send(Members[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
    
    std::vector<client> Admins = Channel.getAdmins();
    
    for(size_t i = 0; i < Admins.size(); i++)
    {
        if(Admins[i].getNickname() == Client.getNickname())
            continue;
        ft_send(Admins[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
    
}

void server::ft_try_to_join(std::string channel_name, std::string password, client & Client)
{
    if(channel_name.at(0) != '#' || channel_name.size() == 1)
    {
        std::string msg = ": 403 " + Client.getNickname() + " " + channel_name + " :No such channel\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;        
    }
    // case 1 : channel does no exist in channels
    if(ft_channel_exist(channel_name) == false)
    {
        channel new_channel;
        new_channel.setName(channel_name);
        new_channel.ft_add_admin(Client);
        new_channel.ft_save_creation_time();
        this->Channels.push_back(new_channel);
        
        ft_join_message(channel_name, Client, new_channel);
        return ;  
    }
    
    // case 2 : channel already exist in the server
    channel & Channel = ft_get_a_channel(channel_name);




    //  error: invite only channel 
    if(Channel.getInvitaionStatus() == true && Channel.ft_find_client("Invited", Client.getNickname()) == false)
    {
        std::string msg = ": 473 " + Client.getNickname() + " " + channel_name + " :Cannot join channel (+i)\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
            
    // error : channel requries a password ..
    if(Channel.getPassWordStatus() == true && Channel.ft_find_client("Invited", Client.getNickname()) == false)
    {
        if(password.empty() == true|| Channel.getPassword() != password)
        {
            std::string msg = ": 475 " + Client.getNickname() + " " + channel_name + " :Cannot join channel (+K) - bad key\r\n";
            ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
            return ;
        }
    }

    // error : channel channel has limit ...
    if(Channel.getLimitStatus() == true && Channel.ft_channel_size() >= Channel.getLimit())
    {
        
        std::string msg = ": 471 " + Client.getNickname() + " " + channel_name + " :Cannot join channel (+l)\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    
    if(Channel.ft_a_member_or_admin(Client.getNickname()) == false)
    {
        Channel.ft_add_member(Client);

        ft_join_message(channel_name, Client, Channel);
        ft_inform_the_rest(Channel, Client);
    }

}

void server::ft_join(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() == 1)
    {
        std::string msg = ": 461 " +  Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }
    std::vector<std::string> channels_names = ft_split_with_comma(Cmds[1]);


    std::vector<std::string> passwords;
    if(Cmds.size() >= 3)
        passwords = ft_split_with_comma(Cmds[2]);

    
    for(size_t i = 0; i < channels_names.size(); i++)
    {
        if(i < passwords.size())
            ft_try_to_join(channels_names[i], passwords[i], Client);
        else
        {
            std::string empty;
            ft_try_to_join(channels_names[i], empty, Client);
        }
    }
}
