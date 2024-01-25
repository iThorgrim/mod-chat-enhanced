/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

// Importing required libraries and headers
#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

#include <algorithm>
#include <regex>

#include "Chat_Enhanced.h"

void Chat_Enhanced_World::OnBeforeConfigLoad(bool reload)
{
    if (!sConfigMgr->GetOption<bool>("ModChatEnchanced.Enable", false))
    {
        return;
    }

    if (reload)
    {
        ceEmojiMap.clear();
    }

    LOG_INFO("module", "Loading Chat Enhanced emojis from chat_enhanced_emojis..");

    auto qResult = WorldDatabase.Query("SELECT * FROM chat_enhanced_emojis");
    uint32 count = 0;

    do
    {
        Field* fields = qResult->Fetch();

        std::string emoji = Acore::StringFormatFmt(":{}:", fields[0].Get<std::string>());
        std::string resource = Acore::StringFormatFmt("|T{}|t", fields[1].Get<std::string>());

        ceEmojiMap.emplace(emoji, resource);
        count++;
    }
    while (qResult->NextRow());

    LOG_INFO("module", Acore::StringFormatFmt(">> Loaded '{}' emojis.", count));
}

Player* Chat_Enhanced_Player::FindPlayerByName(const std::string& name)
{
    return ObjectAccessor::FindPlayerByName(name, false);
}

std::string Chat_Enhanced_Player::FormatPlayerName(const std::string& playerName)
{
    std::string formatted_player_name = playerName;
    formatted_player_name[0] = std::toupper(formatted_player_name[0]);
    std::transform(formatted_player_name.begin() + 1, formatted_player_name.end(),
        formatted_player_name.begin() + 1, ::tolower);

    return formatted_player_name;
}

void Chat_Enhanced_Player::OnBeforeSendChatMessage(Player* player, uint32& /*type*/, uint32& /*lang*/, std::string& msg)
{
    if (!sConfigMgr->GetOption<bool>("ModChatEnchanced.Enable", false))
    {
        return;
    }

    // Logic related to broadcasting messages and tagging other players in the chat

    // Check if the player is a Game Master and if the message contains "@here" or "@everyone" tags.
    if (player->IsGameMaster() && (msg.find("@here") != std::string::npos || msg.find("@everyone") != std::string::npos)) {
        // Getting all active sessions.
        SessionMap const& sessions = sWorld->GetAllSessions();
        // Formatting the name of the game master in context.
        std::string formatted_player_name = "[|Hplayer:" + player->GetName() + "|h" + player->GetName() + "|h]";

        // If the message has "@here", it's intended for all players in the same area as the Game Master.
        if (msg.find("@here") != std::string::npos)
        {
            // Storing the area ID of the game master.
            uint32 gmAreaId = player->GetAreaId();
            // Iterate over all active game sessions to find players in the same area.
            for (SessionMap::const_iterator i = sessions.begin(); i != sessions.end(); ++i)
            {
                Player* p = i->second->GetPlayer();

                // For each player found in the same area,
                if (p->GetAreaId() == gmAreaId)
                {
                    // remove "@here", broadcast the message and play a sound.
                    msg = std::regex_replace(msg, std::regex("@here"), ""); // remove "@here"
                    ChatHandler(p->GetSession()).PSendSysMessage("%s : %s", formatted_player_name, msg.c_str());

                    p->PlayDirectSound(SOUND_IG_BONUS_BAR_OPEN);
                }
            }
        }

        // Similarly, if the message contains "@everyone", it's intended for all players in the game.
        if (msg.find("@everyone") != std::string::npos)
        {
            // Iterate over all active game sessions
            for (SessionMap::const_iterator i = sessions.begin(); i != sessions.end(); ++i)
            {
                Player* p = i->second->GetPlayer();

                // For each player, remove "@everyone", broadcast the message and play a sound.
                msg = std::regex_replace(msg, std::regex("@everyone"), ""); // remove "@everyone"
                ChatHandler(p->GetSession()).PSendSysMessage("%s : %s", formatted_player_name, msg.c_str());

                p->PlayDirectSound(SOUND_IG_BONUS_BAR_OPEN);
            }
        }
    }

    // Create an input stringstream from the message
    std::istringstream iss(msg);

    // Split the message into words and store them into a vector
    std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    // Iterate over every word in the message
    for (const auto& word : words)
    {
        // Check if the word is a user tag, which starts with '@'
        if (word[0] == '@') {
            // Extract the player's name from the tag (by removing '@') and format this name
            std::string player_name = FormatPlayerName(word.substr(1));
            // Look up the corresponding player
            Player* foundPlayer = FindPlayerByName(player_name);

            // Check if the player exists (is logged in)
            if (foundPlayer)
            {
                // If the player exists, replace the tag with a formatted version in the message
                std::string player_tag = "[|Hplayer:" + player_name + "|h" + player_name + "|h]";
                msg = std::regex_replace(msg, std::regex(word), player_tag);
            }
        }

        // Check if the current word is an emoticon by performing a map lookup
        auto search = ceEmojiMap.find(word);

        // If it is an emoticon, replace the emoticon text with its image
        if (search != ceEmojiMap.end())
        {
            std::string replaced = std::regex_replace(msg, std::regex(word), search->second);
            msg = replaced;
        }
    }
}

void AddSC_Chat_Enhanced()
{
    new Chat_Enhanced_World();
    new Chat_Enhanced_Player();
}
