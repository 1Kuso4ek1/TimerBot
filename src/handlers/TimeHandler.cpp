#include "handlers/TimeHandler.hpp"

#include "core/Constants.hpp"

#include <print>
#include <regex>
#include <thread>


using namespace std::chrono_literals;

void TimeHandler::handle(const TgBot::Message::Ptr& message)
{
    if(message->from->id != Env::admId)
        return;

    try
    {
        const auto time = parseTime(message->text.substr(6));
        startTimer(time, message->chat->id);
    }
    catch(const std::exception& e)
    {
        std::println("'TimeHandler::handle': {}", e.what());
    }
}

void TimeHandler::startTimer(const std::chrono::seconds& duration, const int64_t chatId) const
{
    const auto messageId = ui.sendTimerStarted(chatId, formatTime(duration));

    try
    {
        bot.getApi().pinChatMessage(chatId, messageId, true);
    }
    catch(const std::exception& e)
    {
        std::println("'TimeHandler::startTimer': {}", e.what());
    }

    std::thread([this, chatId, messageId](std::chrono::seconds time)
    {
        while(true)
        {
            std::this_thread::sleep_for(5s);
            time -= 5s;

            try
            {
                if(time.count() % 60 == 0 && time.count() != 0)
                    ui.sendReminder(chatId, std::chrono::duration_cast<std::chrono::minutes>(time).count());

                ui.editTimer(chatId, messageId, formatTime(time));
            }
            catch(const std::exception& e)
            {
                std::println("'TimeHandler::startTimer::thread': {}", e.what());
            }

            if(time.count() <= 0)
            {
                try
                {
                    bot.getApi().unpinChatMessage(chatId);

                    ui.sendTimerEnded(chatId);
                }
                catch(const std::exception& e)
                {
                    std::println("'TimeHandler::startTimer::thread': {}", e.what());
                }

                return;
            }
        }
    }, duration).detach();
}

std::chrono::seconds TimeHandler::parseTime(const std::string& time)
{
    const std::regex timeRegex(R"((\d{1,3}):(\d{2}))");
    std::smatch match;

    if (!std::regex_match(time, match, timeRegex)) {
        throw std::invalid_argument("Неверный формат времени. Используйте ММ:СС");
    }

    const auto minutes = std::stoi(match[1].str());
    const auto seconds = std::stoi(match[2].str());

    if(seconds >= 60)
        throw std::invalid_argument("Секунды не могут быть больше 59");

    return std::chrono::minutes(minutes) + std::chrono::seconds(seconds);

}

std::string TimeHandler::formatTime(const std::chrono::seconds& duration)
{
    const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - minutes);

    return std::format("{:02d}:{:02d}", minutes.count(), seconds.count());
}
