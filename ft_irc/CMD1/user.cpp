/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:38:48 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/28 15:20:06 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// bool server::ft_send(int socket, const void * buff, size_t len, int flags);


void server::ft_user(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    // did not enter the correct password yet ..
    if(Client.getPassStage() == false)
    {
        std::string msg =  " :You have not registered!";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
}







