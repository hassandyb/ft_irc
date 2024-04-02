/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:54:36 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/02 15:35:44 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) : :Not enough parameters";
// ft_send(Socket, msg.c_str(), msg.size(), 0);
// return;

// PRIVMSG <target>{,<target>} <text to be sent>

  
void server::ft_privmsg(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() < 3)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) : :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    // 
    if(ft_channel_exist(Cmds[i]) == false)
    {
        channel new_channel;
        new_channel.setName(Cmds[i]);
        new_channel.ft_add_admin(Client);
        this->Channels.push_back(new_channel);
        
       ft_join_message(Cmds, i, Client, new_channel);
      return ;  
    }
}



// privmsg #channel,client, #chennl, clinet :hi how are you doing to day 
// so check wiethr you have : when join the message and create it and save it 


// remember if you add : the mas should be all this (:hi how are you doing to day ),

// now silt the second arg if you have , and save them ...

// if the second arg contained , it means you are sending the mesage to many channels / clients 

// now send the to function that takes the message and the channel/clinet to send too , and of cours our client trying to send this mesage .


