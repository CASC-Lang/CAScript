//
// Created by alanjian85 on 8/12/2021.
//

#ifndef COLORED_COLORED_H
#define COLORED_COLORED_H

#include <iostream>
#include <string_view>

#ifdef _WIN32
#include <functional>

#include <Windows.h>
#endif

namespace cld {
    enum class Color {
        DEFAULT,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        LIGHT_GRAY,
        DARK_GRAY,
        LIGHT_RED,
        LIGHT_GREEN,
        LIGHT_YELLOW,
        LIGHT_BLUE,
        LIGHT_MAGENTA,
        LIGHT_CYAN,
        WHITE,
    };

//platform-specific codes
#ifdef __linux__
    const std::string_view bold = "\033[1m";
    const std::string_view dim = "\033[2m";
    const std::string_view underline = "\033[4m";
    const std::string_view blink = "\033[5m";
    const std::string_view invert = "\033[7m";
    const std::string_view hide = "\033[8m";

    const std::string_view reset = "\033[0m";
    const std::string_view nobold = "\033[21m";
    const std::string_view nodim = "\033[22m";
    const std::string_view nounderline = "\033[24m";
    const std::string_view noblink = "\033[25m";
    const std::string_view regular = "\033[27m";
    const std::string_view show = "\033[28m";

    inline std::string_view fg(Color color) {
        switch(color) {
            case Color::DEFAULT:        return "\033[39m";
            case Color::BLACK:          return "\033[30m";
            case Color::RED:            return "\033[31m";
            case Color::GREEN:          return "\033[32m";
            case Color::YELLOW:         return "\033[33m";
            case Color::BLUE:           return "\033[34m";
            case Color::MAGENTA:        return "\033[35m";
            case Color::CYAN:           return "\033[36m";
            case Color::LIGHT_GRAY:     return "\033[37m";
            case Color::DARK_GRAY:      return "\033[90m";
            case Color::LIGHT_RED:      return "\033[91m";
            case Color::LIGHT_GREEN:    return "\033[92m";
            case Color::LIGHT_YELLOW:   return "\033[93m";
            case Color::LIGHT_BLUE:     return "\033[94m";
            case Color::LIGHT_MAGENTA:  return "\033[95m";
            case Color::LIGHT_CYAN:     return "\033[96m";
            case Color::WHITE:          return "\033[97m";
            default:                    return ""; //unsupported color
        }
    }

    inline std::string_view bg(Color color) {
        switch(color) {
            case Color::DEFAULT:        return "\033[49m";
            case Color::BLACK:          return "\033[40m";
            case Color::RED:            return "\033[41m";
            case Color::GREEN:          return "\033[42m";
            case Color::YELLOW:         return "\033[43m";
            case Color::BLUE:           return "\033[44m";
            case Color::MAGENTA:        return "\033[45m";
            case Color::CYAN:           return "\033[46m";
            case Color::LIGHT_GRAY:     return "\033[47m";
            case Color::DARK_GRAY:      return "\033[100m";
            case Color::LIGHT_RED:      return "\033[101m";
            case Color::LIGHT_GREEN:    return "\033[102m";
            case Color::LIGHT_YELLOW:   return "\033[103m";
            case Color::LIGHT_BLUE:     return "\033[104m";
            case Color::LIGHT_MAGENTA:  return "\033[105m";
            case Color::LIGHT_CYAN:     return "\033[106m";
            case Color::WHITE:          return "\033[107m";
            default:                    return ""; //unsupported color
        }
    }
#elif defined(_WIN32)
    struct WindowsAttribFactor { std::function<void(WORD&)> factor = [](WORD&) {}; };
    std::ostream& operator<<(std::ostream& lhs, const WindowsAttribFactor& rhs);

    const WindowsAttribFactor bold;   //unsupported
    const WindowsAttribFactor dim;    //unsupported
    const WindowsAttribFactor underline = {[](WORD& attrib) { attrib |= COMMON_LVB_UNDERSCORE; }};
    const WindowsAttribFactor blink;  //unsupported
    const WindowsAttribFactor invert = {[](WORD& attrib) { attrib |= COMMON_LVB_REVERSE_VIDEO; }};
    const WindowsAttribFactor hide;   //unsupported

    extern const WindowsAttribFactor reset;
    const WindowsAttribFactor nobold;    //unsupported
    const WindowsAttribFactor nodim;     //unsupported
    const WindowsAttribFactor nounderline = {[](WORD& attrib) { attrib &= ~COMMON_LVB_UNDERSCORE; }};
    const WindowsAttribFactor noblink;   //unsupported
    const WindowsAttribFactor regular = {[](WORD& attrib) { attrib &= ~COMMON_LVB_REVERSE_VIDEO; }};
    const WindowsAttribFactor show;      //unsupported

    inline WindowsAttribFactor fg(Color color) {
        switch(color) {
            case Color::DEFAULT:        return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
                attrib &= ~FOREGROUND_INTENSITY;
            }};
            case Color::BLACK:          return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
            }};
            case Color::RED:            return {[](WORD& attrib) {
                attrib |= FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
                attrib &= ~FOREGROUND_INTENSITY;
            }};
            case Color::GREEN:          return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib |= FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
                attrib &= ~FOREGROUND_INTENSITY;
            }};
            case Color::YELLOW:         return {[](WORD& attrib) {
                attrib |= FOREGROUND_RED;
                attrib |= FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
                attrib &= ~FOREGROUND_INTENSITY;
            }};
            case Color::BLUE:           return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib &= ~FOREGROUND_INTENSITY;
            }};
            case Color::MAGENTA:        return {[](WORD& attrib) {
                attrib |= FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib &= ~FOREGROUND_INTENSITY;
            }};
            case Color::CYAN:           return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::LIGHT_GRAY:     return {[](WORD& attrib) {
                attrib |= FOREGROUND_RED;
                attrib |= FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::DARK_GRAY:      return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
            }};
            case Color::LIGHT_RED:      return {[](WORD& attrib) {
                attrib |= FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::LIGHT_GREEN:    return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib |= FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::LIGHT_YELLOW:   return {[](WORD& attrib) {
                attrib |= FOREGROUND_RED;
                attrib |= FOREGROUND_GREEN;
                attrib &= ~FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::LIGHT_BLUE:     return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::LIGHT_MAGENTA:  return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib |= FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::LIGHT_CYAN:     return {[](WORD& attrib) {
                attrib &= ~FOREGROUND_RED;
                attrib &= ~FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            case Color::WHITE:          return {[](WORD& attrib) {
                attrib |= FOREGROUND_RED;
                attrib |= FOREGROUND_GREEN;
                attrib |= FOREGROUND_BLUE;
                attrib |= FOREGROUND_INTENSITY;
            }};
            default:                    return {[](WORD& attrib) {}}; //unsupported color
        }
    }

    inline WindowsAttribFactor bg(Color color) {
        switch(color) {
            case Color::DEFAULT:        return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
                attrib &= ~BACKGROUND_INTENSITY;
            }};
            case Color::BLACK:          return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
            }};
            case Color::RED:            return {[](WORD& attrib) {
                attrib |= BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
                attrib &= ~BACKGROUND_INTENSITY;
            }};
            case Color::GREEN:          return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib |= BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
                attrib &= ~BACKGROUND_INTENSITY;
            }};
            case Color::YELLOW:         return {[](WORD& attrib) {
                attrib |= BACKGROUND_RED;
                attrib |= BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
                attrib &= ~BACKGROUND_INTENSITY;
            }};
            case Color::BLUE:           return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib &= ~BACKGROUND_INTENSITY;
            }};
            case Color::MAGENTA:        return {[](WORD& attrib) {
                attrib |= BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib &= ~BACKGROUND_INTENSITY;
            }};
            case Color::CYAN:           return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::LIGHT_GRAY:     return {[](WORD& attrib) {
                attrib |= BACKGROUND_RED;
                attrib |= BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::DARK_GRAY:      return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
            }};
            case Color::LIGHT_RED:      return {[](WORD& attrib) {
                attrib |= BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::LIGHT_GREEN:    return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib |= BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::LIGHT_YELLOW:   return {[](WORD& attrib) {
                attrib |= BACKGROUND_RED;
                attrib |= BACKGROUND_GREEN;
                attrib &= ~BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::LIGHT_BLUE:     return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::LIGHT_MAGENTA:  return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib |= BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::LIGHT_CYAN:     return {[](WORD& attrib) {
                attrib &= ~BACKGROUND_RED;
                attrib &= ~BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            case Color::WHITE:          return {[](WORD& attrib) {
                attrib |= BACKGROUND_RED;
                attrib |= BACKGROUND_GREEN;
                attrib |= BACKGROUND_BLUE;
                attrib |= BACKGROUND_INTENSITY;
            }};
            default:                    return {[](WORD& attrib) {}}; //unsupported color
        }
    }
#else
#error "Colored: Unsupported platform!"
#endif
}

#endif //COLORED_COLORED_H
