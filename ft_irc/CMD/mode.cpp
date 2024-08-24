/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:19:45 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 21:30:55 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

bool ft_valid_limit(std::string max)
{
    if(ft_string_to_size_t(max) <= 0)
        return false;
    return true;
}         

void server::ft_mode_invite(channel & Channel, client & Client, bool sign)
{
    if(sign == true && Channel.getInvitaionStatus() == false)
    {
        Channel.setInvitaionStatus(true);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " +i\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
    if(sign == false && Channel.getInvitaionStatus() == true)
    {
        Channel.setInvitaionStatus(false);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " -i\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
}

void server::ft_mode_topic(channel & Channel, client & Client, bool sign)
{
    if(sign == true && Channel.getTopicStatus() == false)
    {
        Channel.setTopicStatus(true);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " +t\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
    if(sign == false && Channel.getTopicStatus() == true)
    {
        Channel.setTopicStatus(false);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " -t\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
    }
}

void server::ft_mode_password(channel & Channel, client & Client, bool sign, std::string Password)
{
    if(Password.empty() == true)// case no passwrd entred
    {
        std::string msg = ": 696 " + Channel.getName() + " (k) * you must specifiy a parameter for the op mode\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return;
    }
    if(sign == true)// case +k
    {
        Channel.setPassword(Password);
        Channel.setPassWordStatus(true);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " +k " + Password + "\r\n";
        ft_send_msg_to_all(Channel.getMembers(), msg);
        ft_send_msg_to_all(Channel.getAdmins(), msg); 
    }
    if(sign == false)// case -k
    {

        if(Channel.getPassword() != Password) // incorect password
        {
            std::string msg = ": 467 " + Channel.getName() + " Channel key already set.\r\n";
            ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        }
        else //  // corect password
        {

            Channel.setPassWordStatus(false);
            std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " -k\r\n";
            ft_send_msg_to_all(Channel.getMembers(), msg);
            ft_send_msg_to_all(Channel.getAdmins(), msg); 
        }
    }
    

}

void server::ft_mode_limit(channel & Channel, client & Client, bool sign, std::string max)
{
    


    if(sign == true && max.empty() == true)// error 1 : +l requires  limit arg 
    {
        std::string msg = ": 461 " + Channel.getName() + " MODE +l :Not enough parameters !\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return;
    }
    if(sign == true && ft_valid_limit(max) == false) // error 2 : +l require valid limit number
    {
        std::string msg = ": 696 " + Channel.getName() + " +l :Invalid mode parameter.\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return;
    }

    if(sign == true)// case +l
    {
        Channel.setLimit(ft_string_to_size_t(max));
        Channel.setLimitStatus(true);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " +l " + max + "\r\n";
        ft_send_msg_to_all(Channel.getMembers(), msg);
        ft_send_msg_to_all(Channel.getAdmins(), msg); 
        
    }
    if(sign == false)// case -l
    {
        Channel.setLimitStatus(false);
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " -l\r\n";
        ft_send_msg_to_all(Channel.getMembers(), msg);
        ft_send_msg_to_all(Channel.getAdmins(), msg); 
    }
}

void server::ft_mode_operator(channel & Channel, client & Client, bool sign, std::string target_client)
{
    
   
   if(target_client.empty() == true)// error 1 : empty target 
    {
        std::string msg = ": 696 " + Channel.getName() + " * you must specifiy a parameter for the op mode\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return;
    } 
    
    if(Channel.ft_find_client("Members", target_client) == false && Channel.ft_find_client("Admins", target_client) == false )// error 2 : dont exist in members 
    {
        std::string msg = ": 401 " + Channel.getName() + " " + target_client + " :No such nick/channel\r\n";
        ft_send(Client.getSocket(), msg.c_str(), msg.size(), 0);
        return;
    }
    
    if(sign == true)// case +o
    {
        if(Channel.ft_find_client("Admins", target_client) == true)// case already an operator ...
            return ;
        
        client target = Channel.ft_get_client("Members", target_client);
        Channel.ft_add_client("Admins", target);    // add it to admins
        Channel.ft_erase_client("Members", target_client);// erase from members 

        
        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " +o " + target.getNickname() + "\r\n";

        
        ft_send_msg_to_all(Channel.getAdmins(), msg);
        ft_send_msg_to_all(Channel.getMembers(), msg);
        
    }
    if(sign == false)//  case -o
    {
        if(Channel.ft_find_client("Admins", target_client) == false)// not an operator ...
            return ;
        
        client target = Channel.ft_get_client("Admins", target_client);
        Channel.ft_add_client("Members", target);
        Channel.ft_erase_client("Admins", target_client);
        

        std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + " MODE " + Channel.getName() + " -o " + target.getNickname() + "\r\n";
        
        ft_send_msg_to_all(Channel.getAdmins(), msg);
        ft_send_msg_to_all(Channel.getMembers(), msg);
        
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
   channel & Channel = ft_get_a_channel(Cmds[1]);
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
         std::string msg = ": 482 " + Cmds[1] + " :You're not a channel operator\r\n";
         ft_send(Socket, msg.c_str(), msg.size(), 0);
         return ;
    }
    std::string Modestr = Cmds[2];
    size_t j = 3;
    bool sign = true;
    std::string empty;
    
    for(size_t i = 0; i < Modestr.size(); i++)
    {
        if(Modestr.at(i) == '+')
            sign = true;
        else if (Modestr.at(i) == '-')
            sign = false;

        else if (Modestr.at(i) == 'i')
            ft_mode_invite(Channel, Client, sign);
            
        else if(Modestr.at(i) == 't')
            ft_mode_topic(Channel, Client, sign);

        else if(Modestr.at(i) == 'k')
        {
            if(j < Cmds.size())
                ft_mode_password(Channel, Client, sign, Cmds[j]);
            else
                ft_mode_password(Channel, Client, sign, empty);
                j++;
        }
        else if(Modestr.at(i) == 'l')
        {
            if(j < Cmds.size())
                ft_mode_limit(Channel, Client, sign, Cmds[j]);
            else
                ft_mode_limit(Channel, Client, sign, empty);
            j++;  
        }
        else if(Modestr.at(i) == 'o')
        {
            if(j < Cmds.size())
                ft_mode_operator(Channel, Client, sign, Cmds[j]);
            else
                ft_mode_operator(Channel, Client, sign, empty);
            j++;
        }
        else
        {
            continue;
            std::string msg = ": 472 " + Client.getNickname() + " " + Channel.getName() + " " + Modestr.at(i) + " :is unknown mode char to me\r\n";
            ft_send(Socket, msg.c_str(), msg.size(), 0);
        }
    }


    }
