#pragma once

namespace Env
{

// Environment
inline auto token = std::getenv("TOKEN");
inline auto admId = std::stoll(std::getenv("ADM_ID"));

}

namespace Strings
{

inline constexpr auto helloWorld = "Hello World!";
inline constexpr auto timeLeft = "Осталось времени: {}!";
inline constexpr auto reminder = "До конца {} минут{}!";
inline constexpr auto timerEnded = "Время вышло!";

inline constexpr auto killerModeActivated = "Режим убийства активирован!";
inline constexpr auto killerModeDisabled = "Режим убийства деактивирован!";

inline constexpr auto userKilled = "Пользователь {} оказался неосторожным и был убит!";

}
