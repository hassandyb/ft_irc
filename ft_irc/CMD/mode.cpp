/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:07:01 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/07 16:19:39 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"


// mode +o hdg

// mode +ilo pp
// mode +i hh +o jj +jhf 



void server::ft_mode(std::vector<std::string>  Cmds, client & Client, int Socket)
{
    // 0 : size == 0  ==:Not enough parameters.

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
