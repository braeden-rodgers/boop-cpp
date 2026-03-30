/**
 * colors.h 
 * 
 * Header file that defines a set of constant strings representing ANSI escape
 * codes for coloring text in the terminal
 * 
 */

#ifndef COLORS_H
#define COLORS_H

#include <string>

// Text Formatting Styles
const std::string RESET      = "\e[0m";
const std::string BOLD       = "\e[1m";
const std::string ITALIC     = "\e[3m";
const std::string UNDERLINE  = "\e[4m";
const std::string BLINK      = "\e[5m";          	

// Regular Colors
const std::string BLACK      = "\e[30m";
const std::string RED        = "\e[31m";
const std::string GREEN      = "\e[32m";
const std::string YELLOW     = "\e[33m";
const std::string BLUE       = "\e[34m";
const std::string PURPLE     = "\e[35m";
const std::string CYAN       = "\e[36m";
const std::string WHITE      = "\e[37m";

// Background Colors
const std::string BG_BLACK   = "\e[40m";
const std::string BG_RED     = "\e[41m";
const std::string BG_GREEN   = "\e[42m";
const std::string BG_YELLOW  = "\e[43m";
const std::string BG_BLUE    = "\e[44m";
const std::string BG_PURPLE  = "\e[45m";
const std::string BG_CYAN    = "\e[46m";
const std::string BG_WHITE   = "\e[47m";

// High Intensity Colors
const std::string H_BLACK    = "\e[90m";
const std::string H_RED      = "\e[91m";
const std::string H_GREEN    = "\e[92m";
const std::string H_YELLOW   = "\e[93m";
const std::string H_BLUE     = "\e[94m";
const std::string H_PURPLE   = "\e[95m";
const std::string H_CYAN     = "\e[96m";
const std::string H_WHITE    = "\e[97m";

// High Intensity Background Colors
const std::string HBG_BLACK  = "\e[100m";
const std::string HBG_RED    = "\e[101m";
const std::string HBG_GREEN  = "\e[102m";
const std::string HBG_YELLOW = "\e[103m";
const std::string HBG_BLUE   = "\e[104m";
const std::string HBG_PURPLE = "\e[105m";
const std::string HBG_CYAN   = "\e[106m";
const std::string HBG_WHITE  = "\e[107m";

// Shortcuts 
const std::string ERROR      = "\e[1;41;37m\a";  // Bold white text with red background
const std::string MENU       = "\e[44;37m";      // Regular white text with blue background

#endif  // COLORS_H
