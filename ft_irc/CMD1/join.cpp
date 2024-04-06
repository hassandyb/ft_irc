/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:36:59 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/06 15:08:00 by hed-dyb          ###   ########.fr       */
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
        std::string msg1 = ":" + Client.getNickname() + "!" + Client.getNickname() + "@127.0.0.1 JOIN " + channel_name;
        std::string msg2 = ": 353 " + Client.getNickname() + " @ " + channel_name + " :" + new_channel.ft_list_admins_and_members();
        std::string msg3 = ": 366 " + Client.getNickname() + " " + channel_name + " :END of /NAMES list";
        
        // send to client 
        ft_send(Client.getSocket(), msg1.c_str(), msg1.size(), 0);
        ft_send(Client.getSocket(), msg2.c_str(), msg2.size(), 0);
        ft_send(Client.getSocket(), msg3.c_str(), msg3.size(), 0);
        
        // desplay on the server ...
        std::cout << std::endl;
        std::cout << msg1 << std::endl;
        std::cout << msg2 << std::endl;
        std::cout << msg3 << std::endl;        
}

channel & server::ft_find_channel(std::string channel_name)// we use return reference because we need to ake actuall changes to out channel
{
    size_t i;
    for( i = 0; i < Channels.size(); i++)
    {
        if(channel_name == this->Channels[i].getName())
            return this->Channels[i];
    }
    return this->Channels[i];
}
  
void server::ft_try_to_join(std::string channel_name, std::string password, client & Client)
{

    if(channel_name.at(0) != '#' || channel_name.size() == 1)
    {
        std::string msg = Client.getNickname() + " " + channel_name + " 475 :No such channel";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;        
    }
    // case 1 : channel does no exist in channels
    if(ft_channel_exist(channel_name) == false)
    {
        channel new_channel;
        new_channel.setName(channel_name);
        new_channel.ft_add_admin(Client);
        this->Channels.push_back(new_channel);
        
        ft_join_message(channel_name, Client, new_channel);
        return ;  
    }
    
    // case 2 : channel already exist in the server

    channel Channel = ft_find_channel(channel_name);

    //  error: invite only channel 
    if(Channel.ft_find_client("Invited", Client.getNickname()) == false)
    {
        std::string msg = Client.getNickname() + " " + channel_name + " :Cannot join channel (+i)";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
            
    // error : channel requries a password ..
    if(Channel.getPassWordStatus() == true)
    {
        if(password.empty() == true|| Channel.getPassword() != password)
        {
            std::string msg = Client.getNickname() + " " + channel_name + " (475) :Cannot join channel (+k)";
            ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
            return ;
        }
    }
    Channel.ft_add_member(Client);
    ft_join_message(channel_name, Client, Channel);
}

void server::ft_join(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) : :Not enough parameters";
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
