/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:30:38 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 21:32:14 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

size_t ft_string_to_size_t(std::string str)
{
    std::istringstream iss(str);
    size_t result;
    iss >> result;

    return result;
}

std::vector<std::string> ft_split_with_comma(std::string list)
{
    std::vector<std::string> Container;
    
    std::istringstream iss(list);
    std::string part;
    while(std::getline(iss, part, ','))
    {
        Container.push_back(part);
    }
    return Container;
}

void ft_split_with_spaces(std::vector<std::string> & Cmds, std::string Command)
{
    std::string split;
    std::istringstream iss(Command);
    
    while(iss >> split)
        Cmds.push_back(split);
}

bool server::ft_send(int socket, const void * buff, size_t len, int flags)
{

    ssize_t r =  send(socket, buff, len, flags);
    if(r == -1)// send faliere
    {
        std::cerr << "Send() failed to send respond!" << std::endl;
        return false;
    }
    return true;
}

void server::ft_send_msg_to_all(std::vector<client> Clients, std::string msg)
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        ft_send(Clients[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
}