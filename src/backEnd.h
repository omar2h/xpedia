#ifndef __BACKEND_H__
#define __BACKEND_H__
#include "user.h"

class BackEnd
{
public:
    static void save_user_in_db(User &);
    static User user_login(const std::string &, const std::string &);
};
#endif // __BACKEND_H__