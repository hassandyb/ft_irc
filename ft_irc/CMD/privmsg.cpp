/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:54:36 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/06 15:01:58 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"



// PRIVMSG <target>{,<target>} <text to be sent>

// craete like the join styole
// a a mian function the a function that 
// privmsg p1,p2,g1p3, :hi gyus .. 


//   :Angel PRIVMSG Wiz :Hello are you receiving this message ?
//                                   ; Message from Angel to Wiz.

// :b!~b@localhost PRIVMSG #group :hiiiiii








void server::ft_priv_msg_client(std::string Recipient_name, client & Client, std::string message)
{
    client Recipient = ft_get_client(Recipient_name);
    std::string msg = Client.getNickname() + " PRIVMSG " + Recipient.getNickname() + ":" + message;
    ft_send(Recipient.getSocket(), msg.c_str(), msg.size(), 0);
}

void server::ft_priv_msg_channel(std::string Recipient_channel, client & Client, std::string message)
{
    channel Channel = ft_get_a_channel(Recipient_channel);

    // He cant send a message to a channel if he not a member :
    if(Channel.ft_find_client("Members",Client.getNickname()) == false && Channel.ft_find_client("Admins",Client.getNickname()) == false)
    {
        std::string msg = Client.getNickname() + " " + Recipient_channel + " (404) :Cannot send to channel";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    
    // sending to all members and admins ...
    std::string msg = Client.getNickname() + " PRIVMSG " + Recipient_channel + ":" + message;
    
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
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (411) :No recipient given";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(Cmds.size() == 2)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (412) :No text to send";
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
            std::string msg = Client.getNickname() + " (401) :No such nick/channel";
            ft_send(Socket, msg.c_str(), msg.size(), 0);

        }
    }
    
}




// ft_main 
// {
//     chach args they should be 3 
//     ft_splint chanels and clinet 
//     if clinet send to clinet 
//     is channel send to chanel 
// }


// privmsg #channel,client, #chennl, clinet :hi how are you doing to day 
// so check wiethr you have : when join the message and create it and save it 


// remember if you add : the mas should be all this (:hi how are you doing to day ),

// now silt the second arg if you have , and save them ...

// if the second arg contained , it means you are sending the mesage to many channels / clients 

// now send the to function that takes the message and the channel/clinet to send too , and of cours our client trying to send this mesage .


