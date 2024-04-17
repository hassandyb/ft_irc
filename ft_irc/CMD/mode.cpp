/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:07:01 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/17 22:11:59 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


// mode +o hdg

// mode +ilo pp
// mode +i hh +o jj +jhf 



void server::ft_mode(std::vector<std::string>  Cmds, client & Client, int Socket)
{
    // 0 : size == 1  ==:Not enough parameters.





    

    if(Cmds.size() == 1)
    {
        std::string msg = " 461 " + Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    if(this->ft_find_a_channel(Cmds[1]) == false)
    {
        std::string msg = ": 403 " + Client.getNickname() + " " + Cmds[1] + " :No such channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
   channel Channel = ft_get_a_channel(Cmds[1]);
    std::string Client_name = Client.getNickname();
    if(Channel.ft_find_client("Members", Client_name) == false && Channel.ft_find_client("Admins", Client_name) == false)
    {
         std::string msg = ": 442 " + Cmds[1] + " " + ":You're not on that channel\r\n";
         ft_send(Socket, msg.c_str(), msg.size(), 0);
         return ;
    }

    if(Cmds.size() == 2 && (Channel.ft_find_client("Members", Client_name) == false || Channel.ft_find_client("Admins", Client_name) == false))
    {
        std::string msg1 = ": 324 " + Client.getNickname() + " " + Channel.getName() + " " + Channel.ft_get_mode() + "\r\n";
        std::string msg2 = ": 329 " + Client.getNickname() + " " + Channel.getName() + " " + Channel.ft_get_creation_time() + "\r\n";
        ft_send(Socket, msg1.c_str(), msg1.size(), 0);
        ft_send(Socket, msg2.c_str(), msg2.size(), 0);
        return ;
    }

    
    std::string Modestr = Cmds[2];
    size_t j = 3;// args ...
    bool sign = true;
    for(size_t i = 0; Modestr.size(); i++)
    {
        // if 
        // esle if ...ext 
        // else
            // 472 " + nick + " " + channel + " " + character + " :is unknown mode char to me\r\n"
            
    
    }
    //mode #group +-++olg arg1 arg2 arg3

    //      ":" + hostname + " 472 " + nick + " " + channel + " " + character + " :is unknown mode char to me\r\n"




    


    

    

    
}
