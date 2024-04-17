/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:07:01 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/17 19:04:48 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


// mode +o hdg

// mode +ilo pp
// mode +i hh +o jj +jhf 

//mode #group +-++olg arg1 arg2 arg3

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


    // 3 hndl : mode #group without flag no need to be operator 

    // ":" + hostname + " 329 " + nick + " " + channelName + " " + time + "\r\n"

    // ":" + hostname + " 329 " + nick + " " + channelName + " " + time + "\r\n"
    if(Cmds.size() == 2)
    {
        std::string msg = ": 324 " + Client.getNickname() + " " + Channel.getName() + " " + Channel.ft_get_mode() + "\r\n";
        
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    
    // gets 
    // mode #group
    // : 324 a #group +tk
    // : 329 a #group 1712499970
    // return 

    // 4 --sue switch ..
    // falg == sign 
    // and llop on arg 3 and send the the send evry time the function get s
    
    // siemd the type => iot..
    // flag true == + - false = -
    // tow caese requre arg - dont require an arg 

    
    // the argumet , or empty if there nothing if it requires one 
    
    // size 
    // case jsut mode chennl ==>return chennl data ..
    // check size == 1 ==> 2 eerr
    // check size == 2 ==> 3 rror 
    // 

    //create a forr loop loeapoing on the arg3 
    
}
