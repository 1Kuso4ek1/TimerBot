#pragma once
#include "HandlerBase.hpp"

#include "view/BotUi.hpp"

#include <tgbot/Bot.h>

class KillHandler final : public HandlerBase
{
public:
    KillHandler(TgBot::Bot& bot, BotUI& ui) : bot(bot), ui(ui) {}

    void handle(const TgBot::Message::Ptr& message) override;
    void handle(const TgBot::CallbackQuery::Ptr& query) override {}

private:
    std::unordered_map<int64_t, bool> chats, kills;

private:
    TgBot::Bot& bot;

    BotUI& ui;
};
