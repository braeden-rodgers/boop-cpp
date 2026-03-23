/**
 * colors.h 
 * 
 * Header file that define a set of constant strings representing ANSI escape
 * codes for coloring text in the terminal
 * 
 */

#ifndef COLORS_H
#define COLORS_H

#include <string>
using namespace std;

// Text Formatting Styles
const string RESET      = "\e[0m";
const string BOLD       = "\e[1m";
const string ITALIC     = "\e[3m";
const string UNDERLINE  = "\e[4m";
const string BLINK      = "\e[5m";          	

// Regular Colors
const string BLACK      = "\e[30m";
const string RED        = "\e[31m";
const string GREEN      = "\e[32m";
const string YELLOW     = "\e[33m";
const string BLUE       = "\e[34m";
const string PURPLE     = "\e[35m";
const string CYAN       = "\e[36m";
const string WHITE      = "\e[37m";

// Background Colors
const string BG_BLACK   = "\e[40m";
const string BG_RED     = "\e[41m";
const string BG_GREEN   = "\e[42m";
const string BG_YELLOW  = "\e[43m";
const string BG_BLUE    = "\e[44m";
const string BG_PURPLE  = "\e[45m";
const string BG_CYAN    = "\e[46m";
const string BG_WHITE   = "\e[47m";

// High Intensity Colors
const string HI_BLACK   = "\e[90m";
const string HI_RED     = "\e[91m";
const string HI_GREEN   = "\e[92m";
const string HI_YELLOW  = "\e[93m";
const string HI_BLUE    = "\e[94m";
const string HI_PURPLE  = "\e[95m";
const string HI_CYAN    = "\e[96m";
const string HI_WHITE   = "\e[97m";

// High Intensity Background Colors
const string BG_BLACK   = "\e[100m";
const string BG_RED     = "\e[101m";
const string BG_GREEN   = "\e[102m";
const string BG_YELLOW  = "\e[103m";
const string BG_BLUE    = "\e[104m";
const string BG_PURPLE  = "\e[105m";
const string BG_CYAN    = "\e[106m";
const string BG_WHITE   = "\e[107m";

// Shortcuts 
const string ERROR      = "\e[1;41;37m\a";  // Bold white text with red background
const string MENU       = "\e[44;37m";      // Regular white text with blue background

#endif  // COLORS_H
