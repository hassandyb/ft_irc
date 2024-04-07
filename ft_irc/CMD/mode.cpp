/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:07:01 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/07 17:18:09 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


// mode +o hdg

// mode +ilo pp
// mode +i hh +o jj +jhf 

//            mode #group +-++olg arg1 arg2 arg3

void server::ft_mode(std::vector<std::string>  Cmds, client & Client, int Socket)
{
    // 0 : size == 1  ==:Not enough parameters.

    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " MODE " + "(461) :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
// (hostname, channel, nick) ":" + hostname + " 403 " + nick + " " + channel + " :No such channel\r\n"

    if(this->ft_find_a_channel(Cmds[1]) == false)
    {
        // std::string msg = ":"
    }
    // 1 chek that this channel exsit
    // no such channel/client ==>:No such channel

    
    
    // 2 : first check that this client is operator ...(you are not chennl operator)
    //  :You're not on that channel\r\n  (442)
    

    // 3   hndl : mode #group without flag no need to be operator 
    // if(size == 2)
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
