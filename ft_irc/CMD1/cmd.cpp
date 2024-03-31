/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:11 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/31 16:40:28 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

bool server::ft_send(int socket, const void * buff, size_t len, int flags)
{

    // for testing ...only
    (void)socket;
    (void)len;
    (void)flags;
    char *msg = (char *)buff;
    std::cout << msg << std::endl;
    




    
    // ssize_t r =  send(socket, buff, len, flags);
    // if(r == -1)// send faliere
    // {
    //     std::cerr << "Send() failed to send respond!" << std::endl;
    //     return false;
    // }
    return true;
}


bool server::ft_is_registred(client & Client, int Socket)
{
    if(Client.getRegestred() == false)
    {
        std::string msg = Client.getNickname() + " (451) :You have not registered";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return false;
    }
    return true;
}


void server::ft_execute_command(std::string Command, client & Client, int Socket)
{
    std::vector<std::string>::iterator it;
    std::istringstream iss(Command);
    std::string split;
    std::vector<std::string> Cmds;
    
    while(iss >> split)
    {
        Cmds.push_back(split);
    }
    if(Cmds.size() == 0)
        return;

    // Password stage and autotication satge 

    if(Cmds[0] == "PASS" || Cmds[0] == "pass")
    {
        ft_pass(Cmds, Client, Socket);
        return ;
    }
    if(Cmds[0] == "USER" || Cmds[0] == "user")
    {
        ft_user(Cmds, Client, Socket);
        return;
    }
    if(Cmds[0] == "NICK" || Cmds[0] == "nick")
    {
        ft_nick(Cmds, Client, Socket);
        return;
    }
    if(ft_is_registred(Client, Socket) == false)
        return;



   
        

    if(Cmds[0] == "JOIN" || Cmds[0] == "join")
        ft_join(Cmds, Client, Socket);
        
    // else if(Cmds[0] == "INVITE" || Cmds[0] == "invite")
    //     ft_invite(Cmds, Client, Socket);
    // else if(Cmds[0] == "PRIVMSG" || Cmds[0] == "privmsg")
    //     ft_privmsg(Cmds, Client, Socket);
    // else if(Cmds[0] == "MODE" || Cmds[0] == "mode")
    //     ft_mode(Cmds, Client, Socket);




    
    // else if(Cmds[0] == "TOPIC" || Cmds[0] == "topic")
    //     ft_topic(Cmds, Client, Socket);// enter clinet as reference so you can change it if you want same for all functions ..
    // else if(Cmds[0] == "PART" || Cmds[0] == "part")
    //     ft_part(Cmds, Client, Socket);

    // else if(Cmds[0] == "KICK" || Cmds[0] == "kick")
    //     ft_kick(Cmds, Client, Socket);
    // else if(Cmds[0] == "QUIT" || Cmds[0] == "quit")
    //     ft_quit(Cmds, Client, Socket);
    else
        std::cout << "else condition ..." << std::endl;



  

}




