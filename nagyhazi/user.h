#pragma once

#include "memtrace.h"
#include <string>
#include "Mezo.h"




class User {

#ifdef EMAIL_SUPPORT
    std::string email;
#endif
    std::string nickname;
    std::string password;
    int games;

public:

#ifdef EMAIL_SUPPORT
    User(std::string email, std::string nickname, std::string password) : email(email), nickname(nickname), password(password), games(0) {}
    User() : email("JohnDoe@gmail.com"), nickname("JohnDoe"), password("JohnDoe123"), games(0) {}
    std::string getmail() { return email; }
#else
    User(std::string nickname, std::string password) : nickname(nickname), password(password), games(0) {}
    User() : nickname("JohnDoe"), password("JohnDoe123"), games(0) {}
#endif
    virtual ~User();
    void setjatszott(int jatszottt) { games = jatszottt; }
    void setpass(std::string pass) { password = pass; }
    std::string getname() { return nickname; }
    virtual Mezo* lep(Mezo* tabla, int length, int width, User& masik, bool& gameover) { return tabla; }

};

class Man : public User {

public:

#ifdef EMAIL_SUPPORT
    Man(std::string email, std::string nickname, std::string password) : User(email, nickname, password) {}
#else
    Man(std::string nickname, std::string password) : User(nickname, password) {}
#endif
    Man(User user) : User(user) {}
    Man() : User() {}
    virtual ~Man();
    Mezo* lep(Mezo* tabla, int length, int width, User& masik, bool& gameover);

};

class Cat : public User {

    Mezo where;

public:

#ifdef EMAIL_SUPPORT
    Cat(std::string email, std::string nickname, std::string password, Mezo where) : User(email, nickname, password), where(where) {}
#else
    Cat(std::string nickname, std::string password, Mezo where) : User(nickname, password), where(where) {}
#endif
    Cat(User user, Mezo where) : User(user), where(where) {}
    Cat(User user) : User(user), where(-1, -1, "NA", 0, 0, 0, 0) {}
    Cat() : User(), where(-1, -1, "NA", 0, 0, 0, 0) {}
    virtual ~Cat();
    Mezo hol() { return where; }
    Mezo* lep(Mezo* tabla, int length, int width, User& masik, bool& gameover);
    void merre(Mezo wheres) { where = wheres; }
    void drawline() { std::cout << "|OO"; }

};