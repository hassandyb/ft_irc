/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:07:14 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/01 17:57:30 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"



void server::ft_invite(std::vector<std::string> Cmds, client & Client, int Socket)
{
    (void)Cmds;
    (void)Client;
    (void)Socket;

    if(Cmds.size() != 3)
    {
        std::string msg = Client.getNickname() + " invite (461) :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    // search for that clinet if it regerstred ..if not return   ==>401 b :No such nick
    // searc h is i=he is our client in memeber or admine .. eather by  creating a vector of channels or find you own way 
    // if not a psrt or doe not eit .. whta ecver return  ==> 403 hgdwh :No such channel
}





