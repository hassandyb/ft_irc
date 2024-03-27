/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:17:15 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/27 18:19:43 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// bool server::ft_send(int socket, const void * buff, size_t len, int flags);



void server::ft_pass(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // (void)Cmds;
    (void)Client;
    // (void)Socket;

    if(Cmds.size() == 1)
    {
        std::string msg = Cmds[0] + " :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
    }
    // if(this->PassWord != Cmds[1])
    // {
        
    // }
       
}

