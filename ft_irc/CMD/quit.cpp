/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:21:07 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/23 12:23:45 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// when he quites a all the channel memevers he is in recive this ==

//      :b!~b@localhost QUIT Quit
// the user gets this first quit
//      :b!~b@localhost QUIT :i have no raeson


void server::ft_quit(std::vector<std::string> Cmds, client & Client, int Socket)
{
    
    std::string reason = "Quit";
    if(Cmds.size() >= 2)
        reason = ":" + Cmds[1];
    
    std::string msg = "Quit\r\n";;
    ft_send(Socket, msg.c_str(), msg.size(), 0);
    for(size_t i = 0; i < Channels.size(); i++)
    {
        // if clinet in that channel - erase him .
        bool flag = false;
        if(Channels[i].ft_find_client("Members", Client.getNickname()) == true)
        {
            Channels[i].ft_erase_client("Members", Client.getNickname());
            flag = true;
        } 
        if(Channels[i].ft_find_client("Admins", Client.getNickname()) == true)
        {
            Channels[i].ft_erase_client("Admins", Client.getNickname());
            flag = true;
        }
        // if clinet in that channel - infrom the members  .
        if(flag == true)
        {
            std::string msg = ":" + Client.getNickname() + "!~" + Client.getUsername() + " QUIT " + reason + "\r\n";
            ft_send_msg_to_all(Channels[i].getAdmins(),msg);
            ft_send_msg_to_all(Channels[i].getMembers(), msg);
        }
        
        ft_delete_client(Client);
        
    }
}



