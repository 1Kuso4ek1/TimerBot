#include "view/BotUi.hpp"

#include "core/Constants.hpp"

void BotUI::sendStartMessage(const int64_t chatId) const
{
    bot.getApi().sendMessage(chatId, Strings::helloWorld, {}, {}, {}, "Markdown");
}

int32_t BotUI::sendTimerStarted(const int64_t chatId, const std::string& time) const
{
    return bot.getApi().sendMessage(chatId, std::format(Strings::timeLeft, time))->messageId;
}

void BotUI::sendReminder(const int64_t chatId, const int minutes) const
{
    std::string ending;

    if(const int lastDigit = minutes % 10;
        minutes == 1 || (minutes > 20 && lastDigit == 1))
        ending = "a";
    else if((minutes < 11 || minutes > 19) && (lastDigit >= 2 && lastDigit <= 4))
        ending = "ы";
    else if(minutes >= 5)
        ending = "";

    bot.getApi().sendMessage(chatId, std::format(Strings::reminder, minutes, ending));
}

void BotUI::sendTimerEnded(const int64_t chatId) const
{
    bot.getApi().sendMessage(chatId, Strings::timerEnded);
}

void BotUI::sendKillerModeActivated(const int64_t chatId) const
{
    bot.getApi().sendMessage(chatId, Strings::killerModeActivated);
}

void BotUI::sendKillerModeDeactivated(const int64_t chatId) const
{
    bot.getApi().sendMessage(chatId, Strings::killerModeDisabled);
}

void BotUI::sendUserKilled(int64_t chatId, const std::string& fullName) const
{
    bot.getApi().sendMessage(chatId, std::format(Strings::userKilled, fullName));
}

void BotUI::editTimer(const int64_t chatId, const int32_t messageId, const std::string& time) const
{
    bot.getApi().editMessageText(std::format(Strings::timeLeft, time), chatId, messageId);
}

void BotUI::setupReplyKeyboards() {}

void BotUI::setupInlineKeyboards() {}

void BotUI::createReplyKeyboard(
    const std::vector<std::vector<std::string>>& layout,
    const TgBot::ReplyKeyboardMarkup::Ptr& keyboard
)
{
    for(const auto& i : layout)
    {
        std::vector<TgBot::KeyboardButton::Ptr> row;
        row.reserve(i.size());

        for(const auto& j : i)
            row.push_back(std::make_shared<TgBot::KeyboardButton>(j));

        keyboard->keyboard.push_back(row);
    }
}

void BotUI::createInlineKeyboard(
    const std::vector<std::vector<std::string>>& layout,
    const TgBot::InlineKeyboardMarkup::Ptr& keyboard
)
{
    for(const auto& i : layout)
    {
        std::vector<TgBot::InlineKeyboardButton::Ptr> row;
        row.reserve(i.size());

        for(const auto& j : i)
            row.push_back(std::make_shared<TgBot::InlineKeyboardButton>(j, "", j));

        keyboard->inlineKeyboard.push_back(row);
    }
}
