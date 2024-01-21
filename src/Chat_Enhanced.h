#ifndef MODULE_CHAT_ENHANCED_H
#define MODULE_CHAT_ENHANCED_H

#include "ScriptMgr.h"

class Chat_Enhanced : public PlayerScript
{
public:
    Chat_Enhanced() : PlayerScript("Chat_Enhanced") { }

public:
    // Function to find a player by their name
    Player* FindPlayerByName(const std::string& /*name*/);

    // Function to format the player's name (uppercasing first character and lowercasing the rest)
    std::string FormatPlayerName(const std::string& /*playerName*/);

    // Function that is called before a player sends a chat message
    void OnBeforeSendChatMessage(Player* /*player*/, uint32& /*type*/, uint32& /*lang*/, std::string& /*msg*/) override;
};

#endif // MODULE_CHAT_ENHANCED_H
