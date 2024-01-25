## Overview
The Chat Enhanced module is an addition to the game server that augments chat functionalities to make in-game interactions more immersive and engaging. It introduces the capability of using emoticons and tagging other players directly in the chat.

## Features

- **Emoticons:** The module allows players to use pre-defined emoticons while chatting in the game. These emoticons range from different emojis to game-specific icons.
- **Player Tagging:** Players can directly tag other players in the chat using the '@' symbol followed by the username of the player they wish to tag. If the tagged player is online, the tag is replaced with a formatted version for a more immersive experience.

## How does it work?
The Chat_Enhanced module works by extending the PlayerScript class. Here is a light on what happens behind the scenes when a player sends a chat message:

- **Check for Tags:** The module checks all the words in the chat message, if a word begins with '@', it's treated as a user tag. If such a tag corresponds to an online player, it is replaced with a formatted version in the chat message.
- **Check for Emoticons:** All the words in the chat message are checked to see if they match with the predefined emoticons list. If a match is found, then the emoticon text is replaced with the corresponding image.
- **Game Master Commands:** Special commands '@here' and '@everyone' are designed for Game Masters. When a Game Master user tags '@here', all players in the same area as the Game Master receive the chat message. When they tag '@everyone', every online player receives the chat message, irrespective of their location.


- Tag player : `@playerName`
- Send emoticons : `:our_emoticons:`
- Tag everyone : `@everyone`
- Tag here : `@here`

## How do I add more emojis?
If you want to add more emojis you need to add an entry to the resource in the `chat_enhanced_emojis` table inside of your world database.

| emoji | resource |
| - | - |
| The key used ingame | The path to the resource in the game files. |

Example:

| emoji | resource|
| - | - |
| attack | Interface\CURSOR\Attack:14 |

### Resources
- To understand how the resource paths work, you can [read this wiki](https://wowpedia.fandom.com/wiki/UI_escape_sequences) (scroll down to texture examples).

- To extract the art from the game to view you can [read this wiki](https://wowpedia.fandom.com/wiki/Viewing_Blizzard%27s_interface_code).

- To view the BLP files extracted you can use [BLPView](https://www.wowinterface.com/downloads/info16700-BLPView.html).


