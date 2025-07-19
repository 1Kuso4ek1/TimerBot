#include "core/Application.hpp"
#include "core/Constants.hpp"

#include "handlers/KillHandler.hpp"
#include "handlers/StartHandler.hpp"
#include "handlers/TimeHandler.hpp"

#include <print>

Application::Application()
    : bot(Env::token, httpClient),
      longPoll(bot),
      ui(bot)
{
    startHandler = std::make_unique<StartHandler>(ui);
    timeHandler = std::make_unique<TimeHandler>(bot, ui);
    killHandler = std::make_unique<KillHandler>(bot, ui);

    setupCommands();
    setupCallbackQueries();
}

void Application::run()
{
    while(true)
    {
        try
        {
            std::println("Bot name: {}", bot.getApi().getMe()->firstName);

            while(true)
                longPoll.start();
        }
        catch(const std::exception& e)
        {
            std::println("'Application::run': {}", e.what());
        }
    }
}

void Application::handleAny(const TgBot::Message::Ptr& message) const
{
    if(!message->text.empty() && message->text.front() == '/')
        return;

    killHandler->handle(message);
}

void Application::setupCommands()
{
    bot.getEvents().onAnyMessage([&](const auto& message) { handleAny(message); });

    for(const auto& [command, func] : commands)
        bot.getEvents().onCommand(command, func);
}

void Application::setupCallbackQueries()
{
    bot.getEvents().onCallbackQuery([&](const auto& query)
    {
        for(const auto& [name, callback] : callbacks)
        {
            if(query->data.starts_with(name))
                callback(query);
        }
    });
}
