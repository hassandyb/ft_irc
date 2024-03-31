/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:36:59 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/31 17:15:22 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// bool ft_send(int socket, const void * buff, size_t len, int flags);

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

void server::ft_join_channel(std::vector<std::string> & Cmds, size_t i, client & Client, bool password)
{
    // case 1 : channel does no exist
    if(ft_channel_exist(Cmds[i]) == false)
    {
        channel new_channel;
        new_channel.setName(Cmds[i]);
        new_channel.ft_add_admin(Client);
        this->Channels.push_back(new_channel);

        // send to client 
        // desplay on the server ...
      return ;  
    }
    
    // case 2 : channel does exist ....
    channel Channel = ft_find_channel(Cmds[i]);
}

void server::ft_join(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) : :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return;
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