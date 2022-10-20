#ifndef __FRONTEND_H__
#define __FRONTEND_H__
#include <string>
#include "user.h"
class FrontEnd
{
public:
    static int show_start_menu();
    static void display_welcome_message(const std::string &, const std::string &);
    static int display_main_menu();
    static void display_user_profile(const User &);
};
#endif // __FRONTEND_H__