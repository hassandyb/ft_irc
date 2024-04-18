/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:07:01 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/18 18:51:33 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"




                
                // +t (topic):
                // /mode #channel +t
                // /mode #channel -t
                
                // +k (key):
                // /mode #channel +k password
                // /mode #channel -k
                
                // +o (operator):
                // /mode #channel +o nickname
                // /mode #channel -o nickname
                
                // +l (limit):
                // /mode #channel +l limit
                // /mode #channel -l


                // +i (invite-only):
                // /mode #channel +i
                // /mode #channel -i
void server::ft_mode_invite(channel & Channel, client & Client, bool sign)
{
    // :a!a MODE #group -l == 
    // bool server::ft_send(int socket, const void * buff, size_t len, int flags)
    if(sign == true && Channel.getInvitaionStatus() == false)
    {
        Channel.setInvitaionStatus(true);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getNickname() + " MODE " + Channel.getName() + " +i\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
    if(sign == false && Channel.getInvitaionStatus() == true)
    {
        Channel.setInvitaionStatus(false);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getNickname() + " MODE " + Channel.getName() + " -i\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
}

void server::ft_mode_topic(channel & Channel, client & Client, bool sign)
{
    if(sign == true && Channel.getTopicStatus() == false)
    {
        Channel.setTopicStatus(true);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getNickname() + " MODE " + Channel.getName() + " +t\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
    if(sign == false && Channel.getTopicStatus() == false)
    {
        Channel.setTopicStatus(false);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getNickname() + " MODE " + Channel.getName() + " -t\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
}






void server::ft_mode(std::vector<std::string>  Cmds, client & Client, int Socket)
{

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
    if(Cmds.size() == 2 && (Channel.ft_find_client("Members", Client_name) == false || Channel.ft_find_client("Admins", Client_name) == false))
    {
        std::string msg1 = ": 324 " + Client.getNickname() + " " + Channel.getName() + " " + Channel.ft_get_mode() + "\r\n";
        std::string msg2 = ": 329 " + Client.getNickname() + " " + Channel.getName() + " " + Channel.ft_get_creation_time() + "\r\n";
        ft_send(Socket, msg1.c_str(), msg1.size(), 0);
        ft_send(Socket, msg2.c_str(), msg2.size(), 0);
        return ;
    }
    if(Channel.ft_find_client("Admins", Client_name) == false)
    {
         std::string msg = ": 482 " + Cmds[1] + " " + ":You're not a channel operator\r\n";
         ft_send(Socket, msg.c_str(), msg.size(), 0);
         return ;
    }



    
    std::string Modestr = Cmds[2];
    size_t j = 3;// args ...
    bool sign = true;
    std::string empty;
    //mode #group +-++olg arg1 arg2 arg3
    // +itkl   o -
    //      ":" + hostname + " 472 " + nick + " " + channel + " " + character + " :is unknown mode char to me\r\n"
    
    for(size_t i = 0; Modestr.size(); i++)
    {
        if(Modestr.at(i) == '+')
            sign = true;
        else if (Modestr.at(i) == '-')
            sign = false;

        else if (Modestr.at(i) == 'i')
            ft_mode_invite(Channel, Client, sign);
            
        else if(Modestr.at(i) == 't')
            ft_mode_topic(Channel, Client, sign)

        // else if(Modestr.at(i) == 'k')
        // {
        //     if(j < Cmds.size())
        //         ft_mode_password(Channel, Client, sign, Cmds[j]);
        //     else
        //         ft_mode_password(Channel, Client, sign, empty);
                // j++;
        // }
            
        // else if(Modestr.at(i) == 'l')
        // {
        //     if(j < Cmds.size())
        //         ft_mode_limit(Channel, Client, sign, Cmds[j]);
        //     else
        //         ft_mode_limit(Channel, Client, sign, empty);
        //     j++;
                
        // }
        // else if(Modestr.at(i) == 'o')
        // {
        //     if(j < Cmds.size())
        //         ft_mode_operator(Channel, Client, sign, Cmds[j]);
        //     else
        //         ft_mode_operator(Channel, Client, sign, empty);
        //     j++;
        // }
        else
        {
            std::string msg = ": 472 " + Client.getNickname() + " " + Channel.getName() + " " + Modestr.at(i) + " :is unknown mode char to me\r\n";
            ft_send(Socket, msg.c_str(), msg.size(), 0);
        }

            
            
    
    }




    


    

    

    
}
