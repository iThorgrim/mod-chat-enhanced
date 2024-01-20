/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

#include <algorithm>
#include <regex>

std::map<std::string, std::string> ChatEmotes = {
  { ":pepeabathur:", "|TInterface\\ICONS\\Emoji\\pepeabathur.blp:30:30|t" },
  { ":pepealarak:", "|TInterface\\ICONS\\Emoji\\pepealarak.blp:30:30|t" },
  { ":pepeally:", "|TInterface\\ICONS\\Emoji\\pepeally.blp:30:30|t" },
  { ":pepeanubarak:", "|TInterface\\ICONS\\Emoji\\pepeanubarak.blp:30:30|t" },
  { ":pepeartanis:", "|TInterface\\ICONS\\Emoji\\pepeartanis.blp:30:30|t" },
  { ":pepearthas:", "|TInterface\\ICONS\\Emoji\\pepearthas.blp:30:30|t" },
  { ":pepeasmodan:", "|TInterface\\ICONS\\Emoji\\pepeasmodan.blp:30:30|t" },
  { ":pepeauriel:", "|TInterface\\ICONS\\Emoji\\pepeauriel.blp:30:30|t" },
  { ":pepebaelog:", "|TInterface\\ICONS\\Emoji\\pepebaelog.blp:30:30|t" },
  { ":pepebalafré:", "|TInterface\\ICONS\\Emoji\\pepebl.blp:30:30|t" },
  { ":pepeblblbl:", "|TInterface\\ICONS\\Emoji\\pepeblblbl.blp:30:30|t" },
  { ":pepebourbie:", "|TInterface\\ICONS\\Emoji\\pepebourbie.blp:30:30|t" },
  { ":pepeception:", "|TInterface\\ICONS\\Emoji\\pepeception.blp:30:30|t" },
  { ":pepechasseur:", "|TInterface\\ICONS\\Emoji\\pepechasseur.blp:30:30|t" },
  { ":pepechen:", "|TInterface\\ICONS\\Emoji\\pepechen.blp:30:30|t" },
  { ":pepechevalier:", "|TInterface\\ICONS\\Emoji\\pepechevalier.blp:30:30|t" },
  { ":pepechogall:", "|TInterface\\ICONS\\Emoji\\pepechogall.blp:30:30|t" },
  { ":pepechromie:", "|TInterface\\ICONS\\Emoji\\pepechromie.blp:30:30|t" },
  { ":pepedehaka:", "|TInterface\\ICONS\\Emoji\\pepedehaka.blp:30:30|t" },
  { ":pepedemo:", "|TInterface\\ICONS\\Emoji\\pepedemo.blp:30:30|t" },
  { ":pepediablo:", "|TInterface\\ICONS\\Emoji\\pepediablo.blp:30:30|t" },
  { ":pepedruide:", "|TInterface\\ICONS\\Emoji\\pepedruide.blp:30:30|t" },
  { ":pepeElune:", "|TInterface\\ICONS\\Emoji\\pepeElune.blp:30:30|t" },
  { ":pepefalstad:", "|TInterface\\ICONS\\Emoji\\pepefalstad.blp:30:30|t" },
  { ":pepefox:", "|TInterface\\ICONS\\Emoji\\pepefox.blp:30:30|t" },
  { ":pepefox2:", "|TInterface\\ICONS\\Emoji\\pepefox2.blp:30:30|t" },
  { ":pepefox3:", "|TInterface\\ICONS\\Emoji\\pepefox3.blp:30:30|t" },
  { ":pepefurion:", "|TInterface\\ICONS\\Emoji\\pepefurion.blp:30:30|t" },
  { ":pepegazleu:", "|TInterface\\ICONS\\Emoji\\pepegazleu.blp:30:30|t" },
  { ":pepegold:", "|TInterface\\ICONS\\Emoji\\pepegold.blp:30:30|t" },
  { ":pepegrisetete:", "|TInterface\\ICONS\\Emoji\\pepegrisetete.blp:30:30|t" },
  { ":pepeguerrier:", "|TInterface\\ICONS\\Emoji\\pepeguerrier.blp:30:30|t" },
  { ":pepeguldan:", "|TInterface\\ICONS\\Emoji\\pepeguldan.blp:30:30|t" },
  { ":pepehorde:", "|TInterface\\ICONS\\Emoji\\pepehorde.blp:30:30|t" },
  { ":pepeillidan:", "|TInterface\\ICONS\\Emoji\\pepeillidan.blp:30:30|t" },
  { ":pepeillidan2:", "|TInterface\\ICONS\\Emoji\\pepeillidan2.blp:30:30|t" },
  { ":pepeillidemon:", "|TInterface\\ICONS\\Emoji\\pepeillidemon.blp:30:30|t" },
  { ":pepejaina:", "|TInterface\\ICONS\\Emoji\\pepejaina.blp:30:30|t" },
  { ":pepejohanna:", "|TInterface\\ICONS\\Emoji\\pepejohanna.blp:30:30|t" },
  { ":pepekaelthas:", "|TInterface\\ICONS\\Emoji\\pepekaelthas.blp:30:30|t" },
  { ":pepekerrigan:", "|TInterface\\ICONS\\Emoji\\pepekerrigan.blp:30:30|t" },
  { ":pepekharazim:", "|TInterface\\ICONS\\Emoji\\pepekharazim.blp:30:30|t" },
  { ":pepeleboucher:", "|TInterface\\ICONS\\Emoji\\pepeleboucher.blp:30:30|t" },
  { ":pepeleoric:", "|TInterface\\ICONS\\Emoji\\pepeleoric.blp:30:30|t" },
  { ":pepelichking:", "|TInterface\\ICONS\\Emoji\\pepelichking.blp:30:30|t" },
  { ":pepelili:", "|TInterface\\ICONS\\Emoji\\pepelili.blp:30:30|t" },
  { ":pepeliming:", "|TInterface\\ICONS\\Emoji\\pepeliming.blp:30:30|t" },
  { ":pepeluisaile:", "|TInterface\\ICONS\\Emoji\\pepeluisaile.blp:30:30|t" },
  { ":pepelunara:", "|TInterface\\ICONS\\Emoji\\pepelunara.blp:30:30|t" },
  { ":pepemage:", "|TInterface\\ICONS\\Emoji\\pepemage.blp:30:30|t" },
  { ":pepemalfurion:", "|TInterface\\ICONS\\Emoji\\pepemalfurion.blp:30:30|t" },
  { ":pepemarteau:", "|TInterface\\ICONS\\Emoji\\pepemarteau.blp:30:30|t" },
  { ":pepemedivh:", "|TInterface\\ICONS\\Emoji\\pepemedivh.blp:30:30|t" },
  { ":pepemorales:", "|TInterface\\ICONS\\Emoji\\pepemorales.blp:30:30|t" },
  { ":pepemuradin:", "|TInterface\\ICONS\\Emoji\\pepemuradin.blp:30:30|t" },
  { ":pepenaga:", "|TInterface\\ICONS\\Emoji\\pepenaga.blp:30:30|t" },
  { ":pepenasibo:", "|TInterface\\ICONS\\Emoji\\pepenasibo.blp:30:30|t" },
  { ":pepenature:", "|TInterface\\ICONS\\Emoji\\pepenature.blp:30:30|t" },
  { ":pepeninja:", "|TInterface\\ICONS\\Emoji\\pepeninja.blp:30:30|t" },
  { ":pepenova:", "|TInterface\\ICONS\\Emoji\\pepenova.blp:30:30|t" },
  { ":pepeOBS:", "|TInterface\\ICONS\\Emoji\\pepeOBS.blp:30:30|t" },
  { ":pepeolaf:", "|TInterface\\ICONS\\Emoji\\pepeolaf.blp:30:30|t" },
  { ":pepeonfire:", "|TInterface\\ICONS\\Emoji\\pepeonfire.blp:30:30|t" },
  { ":pepeonfire_vert:", "|TInterface\\ICONS\\Emoji\\pepeonfire_vert.blp:30:30|t" },
  { ":pepeonfire_violet:", "|TInterface\\ICONS\\Emoji\\pepeonfire_violet.blp:30:30|t" },
  { ":pepepal:", "|TInterface\\ICONS\\Emoji\\pepepal.blp:30:30|t" },
  { ":pepeparty:", "|TInterface\\ICONS\\Emoji\\pepeparty.blp:30:30|t" },
  { ":peperaynor:", "|TInterface\\ICONS\\Emoji\\peperaynor.blp:30:30|t" },
  { ":peperehgar:", "|TInterface\\ICONS\\Emoji\\peperehgar.blp:30:30|t" },
  { ":peperexxar:", "|TInterface\\ICONS\\Emoji\\peperexxar.blp:30:30|t" },
  { ":peperik:", "|TInterface\\ICONS\\Emoji\\peperik.blp:30:30|t" },
  { ":peperogue:", "|TInterface\\ICONS\\Emoji\\peperogue.blp:30:30|t" },
  { ":pepesilver:", "|TInterface\\ICONS\\Emoji\\pepesilver.blp:30:30|t" },
  { ":pepesonya:", "|TInterface\\ICONS\\Emoji\\pepesonya.blp:30:30|t" },
  { ":pepedruid:", "|TInterface\\ICONS\\Emoji\\pepedruid.blp:30:30|t" },
  { ":pepedruid2:", "|TInterface\\ICONS\\Emoji\\pepedruid2.blp:30:30|t" },
  { ":pepesylvanas:", "|TInterface\\ICONS\\Emoji\\pepesylvanas.blp:30:30|t" },
  { ":pepetassadar:", "|TInterface\\ICONS\\Emoji\\pepetassadar.blp:30:30|t" },
  { ":pepetc:", "|TInterface\\ICONS\\Emoji\\pepetc.blp:30:30|t" },
  { ":pepethrall:", "|TInterface\\ICONS\\Emoji\\pepethrall.blp:30:30|t" },
  { ":pepetracer:", "|TInterface\\ICONS\\Emoji\\pepetracer.blp:30:30|t" },
  { ":pepetychus:", "|TInterface\\ICONS\\Emoji\\pepetychus.blp:30:30|t" },
  { ":pepetyrael:", "|TInterface\\ICONS\\Emoji\\pepetyrael.blp:30:30|t" },
  { ":pepetyrande:", "|TInterface\\ICONS\\Emoji\\pepetyrande.blp:30:30|t" },
  { ":pepeuther:", "|TInterface\\ICONS\\Emoji\\pepeuther.blp:30:30|t" },
  { ":pepevalla:", "|TInterface\\ICONS\\Emoji\\pepevalla.blp:30:30|t" },
  { ":pepevide:", "|TInterface\\ICONS\\Emoji\\pepevide.blp:30:30|t" },
  { ":pepeviking:", "|TInterface\\ICONS\\Emoji\\pepeviking.blp:30:30|t" },
  { ":pepevikings:", "|TInterface\\ICONS\\Emoji\\pepevikings.blp:30:30|t" },
  { ":pepewtf:", "|TInterface\\ICONS\\Emoji\\pepewtf.blp:30:30|t" },
  { ":pepexul:", "|TInterface\\ICONS\\Emoji\\pepexul.blp:30:30|t" },
  { ":pepezagara:", "|TInterface\\ICONS\\Emoji\\pepezagara.blp:30:30|t" },
  { ":pepezandalar:", "|TInterface\\ICONS\\Emoji\\pepezandalar.blp:30:30|t" },
  { ":pepezeratul:", "|TInterface\\ICONS\\Emoji\\pepezeratul.blp:30:30|t" },
  { ":pepirate:", "|TInterface\\ICONS\\Emoji\\pepirate.blp:30:30|t" },
  { ":pepeyes:", "|TInterface\\ICONS\\Emoji\\pepeyes.blp:30:30|t" },
  { ":pepeno:", "|TInterface\\ICONS\\Emoji\\pepeno.blp:30:30|t" },
  { ":pepewhy:", "|TInterface\\ICONS\\Emoji\\pepewhy.blp:30:30|t" },
  { ":pepemoine:", "|TInterface\\ICONS\\Emoji\\pepemoine.blp:30:30|t" },
};

// Add player scripts
class Chat_Enhanced : public PlayerScript
{
public:
    Chat_Enhanced() : PlayerScript("Chat_Enhanced") { }

    Player* FindPlayerByName(const std::string& name)
    {
        return ObjectAccessor::FindPlayerByName(name, false);
    }

    // Formats a player's name to uppercase the first character and lowercase the rest.
    std::string FormatPlayerName(const std::string& player_name)
    {
        std::string formatted_player_name = player_name;
        formatted_player_name[0] = std::toupper(formatted_player_name[0]);
        std::transform(formatted_player_name.begin() + 1, formatted_player_name.end(),
            formatted_player_name.begin() + 1, ::tolower);

        return formatted_player_name;
    }

    void OnBeforeSendChatMessage(Player* /*player*/, uint32& /*type*/, uint32& /*lang*/, std::string& msg)
    {
        std::istringstream iss(msg);
        std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

        for(const auto& word : words)
        {
            // If the word starts with '@', it's a user tag
            if (word[0] == '@') {
                std::string player_name = FormatPlayerName(word.substr(1));

                // Check if player is logged in
                if (FindPlayerByName(player_name)) {
                    // Replace with formatted tag if player is online
                    std::string player_tag = "[|Hplayer:" + player_name + "|h" + player_name + "|h]";
                    msg = std::regex_replace(msg, std::regex(word), player_tag);
                }
            }

            auto search = ChatEmotes.find(word);
            if(search != ChatEmotes.end())
            {
                std::string replaced = std::regex_replace(msg, std::regex(word), search->second);
                msg = replaced;
            }
        }
    }
};

void AddSC_Chat_Enhanced()
{
    new Chat_Enhanced();
}