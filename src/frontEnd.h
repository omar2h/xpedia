#ifndef __FRONTEND_H__
#define __FRONTEND_H__
#include <string>

class FrontEnd
{
public:
    static int show_start_menu();
    static void display_welcome_message(const std::string &, const std::string &);
    static int display_main_menu();
};
#endif // __FRONTEND_H__