#ifndef CHAD_TERMINAL_H
#define CHAD_TERMINAL_H

#define VT100_RESET         "\033[0m"

#define VT100_BOLD          "\033[1m"
#define VT100_ITALICS       "\033[3m"
#define VT100_REVERSE       "\033[7m"

#define VT100_FG_BLACK      "\033[30m"
#define VT100_FG_RED        "\033[31m"
#define VT100_FG_GREEN      "\033[32m"
#define VT100_FG_YELLOW     "\033[33m"
#define VT100_FG_BLUE       "\033[34m"
#define VT100_FG_MAGENTA    "\033[35m"
#define VT100_FG_CYAN       "\033[36m"
#define VT100_FG_WHITE      "\033[37m"

#define VT100_BG_BLACK      "\033[40m"
#define VT100_BG_RED        "\033[41m"
#define VT100_BG_GREEN      "\033[42m"
#define VT100_BG_YELLOW     "\033[43m"
#define VT100_BG_BLUE       "\033[44m"
#define VT100_BG_MAGENTA    "\033[45m"
#define VT100_BG_CYAN       "\033[46m"
#define VT100_BG_WHITE      "\033[47m"

#define VT100_SAVE_CUR      "\033[s"
#define VT100_RESTORE_CUR   "\033[u"

#endif
