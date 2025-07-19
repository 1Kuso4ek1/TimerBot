#pragma once
#include <tgbot/Bot.h>

class BotUI
{
public:
    explicit BotUI(TgBot::Bot& bot) : bot(bot) {}

    void sendStartMessage(int64_t chatId) const;
    int32_t sendTimerStarted(int64_t chatId, const std::string& time) const;
    void sendReminder(int64_t chatId, int minutes) const;
    void sendTimerEnded(int64_t chatId) const;
    void sendKillerModeActivated(int64_t chatId) const;
    void sendKillerModeDeactivated(int64_t chatId) const;
    void sendUserKilled(int64_t chatId, const std::string& fullName) const;

    void editTimer(int64_t chatId, int32_t messageId, const std::string& time) const;

private:
    void setupReplyKeyboards();
    void setupInlineKeyboards();

    static void createReplyKeyboard(
        const std::vector<std::vector<std::string>>& layout,
        const TgBot::ReplyKeyboardMarkup::Ptr& keyboard
    );
    static void createInlineKeyboard(
        const std::vector<std::vector<std::string>>& layout,
        const TgBot::InlineKeyboardMarkup::Ptr& keyboard
    );

private:
    TgBot::Bot& bot;

private:
    std::unordered_map<std::string, TgBot::ReplyKeyboardMarkup::Ptr> replyKeyboards{};
    std::unordered_map<std::string, TgBot::InlineKeyboardMarkup::Ptr> inlineKeyboards{};
};
