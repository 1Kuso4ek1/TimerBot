#include "handlers/KillHandler.hpp"

#include "core/Constants.hpp"

#include <print>

void KillHandler::handle(const TgBot::Message::Ptr& message)
{
    if(message->text == "/kill" && message->from->id == Env::admId)
    {
        try
        {
            ui.sendKillerModeActivated(message->chat->id);
        }
        catch(const std::exception& e)
        {
            std::println("'KillHandler::handle': {}", e.what());
        }

        chats[message->chat->id] = true;
    }
    else if(message->text == "/nokill" && message->from->id == Env::admId)
    {
        try
        {
            ui.sendKillerModeDeactivated(message->chat->id);
        }
        catch(const std::exception& e)
        {
            std::println("'KillHandler::handle': {}", e.what());
        }

        chats.erase(message->chat->id);

        kills.clear();
    }
    else if(chats.contains(message->chat->id)
        && message->from->id != Env::admId
        && !message->from->isBot
        && !kills.contains(message->from->id))
    {
        try
        {
            bot.getApi().banChatMember(message->chat->id, message->from->id);

            ui.sendUserKilled(message->chat->id, std::format("{} {}", message->from->firstName, message->from->lastName));

            kills[message->from->id] = true;
        }
        catch(const std::exception& e)
        {
            std::println("'KillHandler::handle': {}", e.what());
        }
    }
}
