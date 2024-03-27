/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:11 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/27 14:45:53 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

void server::ft_execute_command(std::string Command, client & Client, int Socket)
{

    (void)Client;
    (void)Socket;

        
    std::istringstream iss(Command);
    std::string split;
    std::vector<std::string> Cmds;
    while(iss >> split)
    {
        Cmds.push_back(split);
    }
    if(Cmds.size() == 0)
        return;

    // if(Cmds[0] == "PASS" || Cmds[0] == "pass")
    //     ft_pass(Cmds, Client, Socket);
    // else if(Cmds[0] == "USER" || Cmds[0] == "user")
    //     ft_user(Cmds, Client, Socket);
    // else if(Cmds[0] == "NICK" || Cmds[0] == "nick")
    //     ft_nick(Cmds, Client, Socket);
    // else if(Cmds[0] == "JOIN" || Cmds[0] == "join")
    //     ft_join(Cmds, Client, Socket);
    // else if(Cmds[0] == "INVITE" || Cmds[0] == "invite")
    //     ft_invite(Cmds, Client, Socket);
    // else if(Cmds[0] == "MODE" || Cmds[0] == "mode")
    //     ft_mode(Cmds, Client, Socket);

    
    // else if(Cmds[0] == "TOPIC" || Cmds[0] == "topic")
    //     ft_topic(Cmds, Client, Socket);
    // else if(Cmds[0] == "PART" || Cmds[0] == "part")
    //     ft_part(Cmds, Client, Socket);
    // else if(Cmds[0] == "PRIVMSG" || Cmds[0] == "privmsg")
    //     ft_privmsg(Cmds, Client, Socket);
    // else if(Cmds[0] == "KICK" || Cmds[0] == "kick")
    //     ft_kick(Cmds, Client, Socket);
    // else if(Cmds[0] == "QUIT" || Cmds[0] == "quit")
    //     ft_quit(Cmds, Client, Socket);
    // else
    //     // ...



  

}




