#ifndef MODULE_CHAT_ENHANCED_H
#define MODULE_CHAT_ENHANCED_H

#include "ScriptMgr.h"

#include <map>

enum Chat_Enhanced_Constants
{
    SOUND_IG_BONUS_BAR_OPEN = 3201
};

std::map<std::string, std::string> ceEmojiMap;

class Chat_Enhanced_World : public WorldScript
{
public:
    Chat_Enhanced_World() : WorldScript("Chat_Enhanced_World") { }

public:
    void OnBeforeConfigLoad(bool /*reload*/) override;
};

class Chat_Enhanced_Player : public PlayerScript
{
public:
    Chat_Enhanced_Player() : PlayerScript("Chat_Enhanced_Player") { }

public:
    // Function to find a player by their name
    Player* FindPlayerByName(const std::string& /*name*/);

    // Function to format the player's name (uppercasing first character and lowercasing the rest)
    std::string FormatPlayerName(const std::string& /*playerName*/);

    // Function that is called before a player sends a chat message
    void OnBeforeSendChatMessage(Player* /*player*/, uint32& /*type*/, uint32& /*lang*/, std::string& /*msg*/) override;
};

#endif // MODULE_CHAT_ENHANCED_H
