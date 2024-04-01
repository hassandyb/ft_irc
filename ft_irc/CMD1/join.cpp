/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:36:59 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/01 17:29:34 by hed-dyb          ###   ########.fr       */
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

void server::ft_join_message(std::vector<std::string> & Cmds, size_t i, client & Client, channel & Channel)
{
        std::string msg1 = ":" + Client.getNickname() + "!" + Client.getNickname() + "@127.0.0.1 JOIN " + Cmds[i];
        std::string msg2 = ": 353 " + Client.getNickname() + " @ " + Cmds[i] + " :" + Channel.ft_list_admins_and_members();
        std::string msg3 = ": 366 " + Client.getNickname() + " " + Cmds[i] + " :END of /NAMES list";
        
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

void server::ft_join_channel(std::vector<std::string> & Cmds, size_t i, client & Client, bool password)
{
    // case zero : entered only #
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " " + Cmds[i] + " 475 :Cannot join channel (+k)";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;        
    }
    // case 1 : channel does no exist in channels #########################################
    if(ft_channel_exist(Cmds[i]) == false)
    {
        channel new_channel;
        new_channel.setName(Cmds[i]);
        new_channel.ft_add_admin(Client);
        this->Channels.push_back(new_channel);
        
       ft_join_message(Cmds, i, Client, new_channel);
      return ;  
    }
    
    // case 2 : channel does exist #########################################
    (void)password;
    channel Channel = ft_find_channel(Cmds[i]);
    
    // invite only channel 
    if(Channel.ft_find_client("Invited", Client.getNickname()) == false)
    {
        std::string msg = Client.getNickname() + " " + Cmds[i] + " :Cannot join channel (+i)";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    else
    {
        Channel.ft_add_member(Client);
        ft_join_message(Cmds, i, Client, Channel);
        return ;
    }
    
    // channel require a password
    if(Channel.getPassWordStatus() == true)
    {
        bool err = false;
        
        // cases 
        if(password == false)// No password entered after args 
            err = true;
        if(password == true)// there is a password after the channel name
        {
            if(Cmds[i + 1] == Channel.getPassword())
                err = true;
        }
        
        if(err == true)
        {
            std::string msg = Client.getNickname() + " " + Cmds[i] + " (475) :Cannot join channel (+k)";
            ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        }
        else
        {
            Channel.ft_add_member(Client);
            ft_join_message(Cmds, i, Client, Channel);
        }
        return ;
    }
 
}

void server::ft_join(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) : :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
    }
    if(Cmds[1].at(0) != '#')
    {
        std::string msg = Client.getNickname() + " localhost (403) :No such channel";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    size_t i = 1;
   while(i < Cmds.size())
   {
        bool password;
        if(Cmds[i].at(0) == '#')
        {
            
            if(i + 1 >= Cmds.size())
                password = false;
            if(i + 1 < Cmds.size())
            {
                if(Cmds[i + 1].at(0) == '#')
                password = false;
            }
            password = true;
            ft_join_channel(Cmds, i, Client, password);
            
        }
        i++;
   }
   
}