#pragma once
#include "HandlerBase.hpp"

#include "view/BotUi.hpp"

#include <tgbot/Bot.h>

#include <chrono>

class TimeHandler final : public HandlerBase
{
public:
    TimeHandler(TgBot::Bot& bot, BotUI& ui) : bot(bot), ui(ui) {}

    void handle(const TgBot::Message::Ptr& message) override;
    void handle(const TgBot::CallbackQuery::Ptr& query) override {}

private:
    void startTimer(const std::chrono::seconds& duration, int64_t chatId) const;

    static std::chrono::seconds parseTime(const std::string& time);
    static std::string formatTime(const std::chrono::seconds& duration);

private:
    TgBot::Bot& bot;

    BotUI& ui;
};
