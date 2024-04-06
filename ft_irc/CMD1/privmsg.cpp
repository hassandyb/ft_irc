/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:54:36 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/06 00:34:16 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"



// PRIVMSG <target>{,<target>} <text to be sent>

// craete like the join styole
// a a mian function the a function that 
// privmsg p1,p2,g1p3, :hi gyus .. 
  
void server::ft_privmsg(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(Cmds.size() < 3)
    {
        std::string msg = Client.getNickname() + " " + Cmds[0] + " (461) : :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    std::vector<std::string > dst = ft_split_with_comma(Cmds[1]);

    for(size_t i = 0; i < dst.size(); i++)
    {
        if()// if it a channelexist  == true ... sue a fucted of utils ...
        {
            // ft send to chane
        }
        else if ()// it a ciletexist == true ...
        {
            
        }
        else
        {
            // send ..   401 #fsghjf :No such nick/channel
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


