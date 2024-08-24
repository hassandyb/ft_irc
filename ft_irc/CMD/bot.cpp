#include "../HEADERS/server.hpp"


std::string server::getJoke()
{
    std::string jokes[] = 
    {
        "Why did the scarecrow win an award ?\n Because he was outstanding in his field!\n",
        "What do you call a fake noodle ?\n An impasta!\n",
        "Why did the coffee file a police report ?\n It got mugged!\n",
        "How does a penguin build its house ?\n Igloos it together!\n",
        "Dad, did you get a haircut ?\n No, I got them all cut!\n",
        "What do you call a belt made out of watches'?\n' A waist of time!\n",
        "How do you organize a space party ?\n You planet!\n",
        "I would avoid the sushi if I was you.\n It’s a little fishy.\n",
        "Want to hear a joke about construction ?\n I’m still working on it.\n",
        "Why couldn’t the bicycle stand up by itself ?\n It was two tired!\n",
        "What did one wall say to the other wall ?\n I’ll meet you at the corner!\n",
        "What did the grape do when he got stepped on ?\n He let out a little wine!\n",
        "I wouldn’t buy anything with velcro.\n It’s a total rip-off.\n",
        "The shovel was a ground-breaking invention.\n",
        "Dad, can you put my shoes on ?\n No, I don’t think they’ll fit me.\n",
    };

    srand(time(0));
    int random = rand() % 15;
    return jokes[random];
}