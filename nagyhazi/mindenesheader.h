#pragma once

#include "memtrace.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <thread>
#include <chrono>
#include <functional>
#include <vector> 
#include "econio.h"
#include "User.h"
#include "Kiolvasando.h"
#include "Mezo.h"
#include "Pont.h"
#include <cstdlib>




class HelperFunctions {
public:
    void fajlkiolvas(std::string fajlnev) {

        std::fstream fajl(fajlnev);
        std::string fajlsor;
        while (std::getline(fajl, fajlsor)) std::cout << "\n" << fajlsor;
        fajl.close();

    }
    int sajatatoi(char ch) {

        std::string betuk = "0123456789abcdefghijklmnopqrstuvdxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (size_t i = 0; i < betuk.size(); i++) {

            if (betuk[i] == ch) return i;

        }
        return -1;
    }

    void osszesito() {

        std::ifstream fajl("osszesito.txt");
        int ertekeles;
        double atlag;
        fajl >> ertekeles;
        fajl >> atlag;
        std::cout << " From " << ertekeles << " reviews we are rated " << atlag << " stars/5";
        fajl.close();

    }

    int valaszto(int elsovalasz, int maxvalasz, int jelenlegi, const char* fajlnev, int ertekeles) {

        std::ifstream fajl(fajlnev);
        std::string fajlsor;
        int sor = 0;
        if (jelenlegi > maxvalasz) jelenlegi = 0;
        if (jelenlegi < 0) jelenlegi = maxvalasz;
        jelenlegi += elsovalasz;
        while (std::getline(fajl, fajlsor)) {

            std::cout << fajlsor;
            if (sor == jelenlegi) std::cout << "  <--";
            if (jelenlegi == ertekeles + elsovalasz && sor == ertekeles + elsovalasz) osszesito();
            std::cout << "\n";
            sor++;

        }
        fajl.close();

        return jelenlegi - elsovalasz;

    }



    int arrowfind(int elsovalasz, int maxvalasz, const char* fajlnev, int ertekeles) {

        int jelenlegi = 0;
        econio_rawmode();
        for (int i = 0; i < 50; i++) std::cout << "\n";
        fajlkiolvas("cica-line-art.txt");
        jelenlegi = valaszto(elsovalasz, maxvalasz, jelenlegi, fajlnev, ertekeles);

        while (true) {

            int key = econio_getch();
            if (key == KEY_UP) {

                jelenlegi--;
                for (int i = 0; i < 25; i++) std::cout << "\n";
                fajlkiolvas("cica-line-art.txt");
                jelenlegi = valaszto(elsovalasz, maxvalasz, jelenlegi, fajlnev, ertekeles);

            }
            if (key == KEY_DOWN) {

                jelenlegi++;
                for (int i = 0; i < 25; i++) std::cout << "\n";
                fajlkiolvas("cica-line-art.txt");
                jelenlegi = valaszto(elsovalasz, maxvalasz, jelenlegi, fajlnev, ertekeles);

            }
            if (key == KEY_ENTER) {

                econio_normalmode();
                return jelenlegi;

            }
            if (key == KEY_ESCAPE) { econio_normalmode(); return -1; }

        }
        econio_normalmode();
        return jelenlegi;

    }


    void csillag(double star, bool needquestion) {

        if (needquestion) fajlkiolvas("ertekelj.txt");

        std::ifstream fajl("csillag.txt");
        std::string fajlsor;
        std::cout << "\n \n";
        while (std::getline(fajl, fajlsor)) {

            int i = 0;
            for (; i < star - 1; i++) std::cout << fajlsor;
            for (double j = 0; j <= (star - i); j += 0.1)
                std::cout << fajlsor[1 + static_cast<std::size_t>(10 * j)];
            std::cout << "\n";

        }
        std::cout << "\n \n" << star;

    }





    void animate() {

        std::ifstream listafajl("animations.txt");
        std::string fajlnev;
        while (std::getline(listafajl, fajlnev)) {
            for (int i = 0; i < 25; i++) std::cout << "\n";
            std::fstream fajl(fajlnev);
            std::string fajlsor;
            while (std::getline(fajl, fajlsor)) std::cout << fajlsor << "\n";
            fajl.close();
            //std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        system("pause >nul");
        fajlkiolvas("lasagna-recipe.txt");
        system("pause >nul");

    }



    bool bipolar(std::string paratlan, std::string paros) {

        //std::cout << "beleleptunk a bipolar fuggvenybe";

        bool polar = false;
        if (polar) { fajlkiolvas(paros); }
        else { fajlkiolvas(paratlan); }
        econio_rawmode();
        while (true)
        {

            int key = econio_getch();
            if (key == KEY_TAB) polar = !polar;
            if (polar) fajlkiolvas(paros);
            else fajlkiolvas(paratlan);
            if (key == KEY_ENTER) break;
        }
        econio_normalmode();
        return polar;
    }



    bool modositFelhasznalo(const std::string& fajlNev, const std::string& becenev, int funkcio, const std::string& ujErtek) {
        std::ifstream input(fajlNev);
        if (!input) {
            std::cerr << "Nem sikerült megnyitni a fájlt: " << fajlNev << std::endl;
            return false;
        }

        std::ostringstream tartalomBuf;
        tartalomBuf << input.rdbuf();
        std::string tartalom = tartalomBuf.str();
        input.close();

        std::istringstream ss(tartalom);
        std::ostringstream ujTartalom;
        std::string sor;

        bool modositott = false;

        while (std::getline(ss, sor)) {
            if (sor.find("e-mail cím:") == 0) {
                std::string emailSor = sor;
                std::string becenevSor, jelszoSor, jatszottSor;

                std::getline(ss, becenevSor);
                std::getline(ss, jelszoSor);
                std::getline(ss, jatszottSor);

                std::string aktBecenev = becenevSor.substr(strlen("Becenév: "));
                if (aktBecenev == becenev) {
                    // Módosítás itt történik
                    switch (funkcio) {
                    case -1: return true;
                    case 1:
                        jelszoSor = "Jelszo: " + ujErtek;
                        break;
                    case 2:
                        emailSor = "e-mail cím: " + ujErtek;
                        break;
                    case 3: {
                        std::string jatszottStr = jatszottSor.substr(strlen("Jatszott: "));
                        int szam = std::stoi(jatszottStr);
                        ++szam;
                        jatszottSor = "Jatszott: " + std::to_string(szam);
                        break;
                    }
                    default:
                        std::cerr << "Ismeretlen funkció: " << funkcio << std::endl;
                        return false;
                    }

                    modositott = true;
                }

                // Írjuk vissza a blokkokat
                ujTartalom << emailSor << '\n'
                    << becenevSor << '\n'
                    << jelszoSor << '\n'
                    << jatszottSor << '\n';
            }
            else {
                ujTartalom << sor << '\n'; // ritkán, de lehet üres sorok is
            }
        }

        if (!modositott) {
            std::cerr << "Nem találtam a becenevet: " << becenev << std::endl;
            return false;
        }

        std::ofstream output(fajlNev);
        if (!output) {
            std::cerr << "Nem sikerült írni a fájlba." << std::endl;
            return false;
        }

        output << ujTartalom.str();
        output.close();

        return true;
    }



    std::string keresEmailCim(const std::string& fajlNev, const std::string& becenev) {
        std::ifstream input(fajlNev);

        std::string sor;
        while (std::getline(input, sor)) {
            if (sor.find("e-mail cím:") == 0) {
                std::string email = sor.substr(strlen("e-mail cím: "));
                std::string becenevSor;
                std::getline(input, becenevSor);

                std::string aktBecenev = becenevSor.substr(strlen("Becenév: "));
                if (aktBecenev == becenev) {
                    return email;
                }

                // Ha nem egyezik, átugorjuk a maradék két sort (Jelszo, Jatszott)
                std::string tmp;
                std::getline(input, tmp);
                std::getline(input, tmp);
            }
        }

        std::cerr << "Nem találtam a becenevet: " << becenev << std::endl;
        return "";
    }




    std::string mail(std::string cim, std::string body) {
        std::string smtpServer = "smtp.gmail.com"; // SMTP szerver
        std::string smtpPort = "587";               // Port (Gmail: 587)
        std::string username = "szilvi.egyetemi@gmail.com"; // Saját email címed
        std::string password = "ecps ivbm gnum mhrq";     // App Password, nem sima jelszó

        srand(static_cast<unsigned int>(time(0)));
        std::string key = std::to_string(rand());

        std::string recipient = cim;
        std::string subject = "CATchA email verification";
        body += key;
        body += " If you did not registered there, you can ignore this email.";

        // PowerShell parancs összeállítása
        std::string command = "powershell -Command \"";
        command += "$securePassword = ConvertTo-SecureString \\\"" + password + "\\\" -AsPlainText -Force; ";
        command += "$credentials = New-Object System.Management.Automation.PSCredential (\\\"" + username + "\\\", $securePassword); ";
        command += "Send-MailMessage -From \\\"" + username + "\\\" -To \\\"" + recipient + "\\\" -Subject \\\"" + subject + "\\\" ";
        command += "-Body \\\"" + body + "\\\" -SmtpServer \\\"" + smtpServer + "\\\" -Port " + smtpPort + " -UseSsl -Credential $credentials\"";

        //Debug kiírás
        std::cout << "Futtatott parancs: " << command << std::endl;

        //int result = system(command.c_str());
        #ifdef system
        #undef system
        #endif

        int result = ::system(command.c_str());


        if (result != 0) {
            key = "abc";
        }
        else {
            std::cout << "E-mail sikeresen elküldve!" << std::endl;
        }

        return key;
    }



    bool vanuser(const std::string keresett) {

        std::ifstream file("jatekos.txt");
        std::string sor;
        while (std::getline(file, sor)) {
            if (sor.rfind("Becenév:", 0) == 0) { // ha a sor "Becenév:"-vel kezdõdik
                std::string becenev = sor.substr(9); // 8 karaktert kihagy ("Becenév: ")
                //std::cout << "Az aktualisan nezett becenev " << becenev << "mig a keresett " << keresett << "!\n";
                if (becenev == keresett) {
                    return true;
                }
            }
        }
        return false;
    }



    bool ervenyes_felhasznalo(const std::string& fajlnev, const std::string& becenev, const std::string& jelszo) {
        std::ifstream fajl(fajlnev);

        std::string sor;
        std::string akt_becenev;
        std::string akt_jelszo;

        while (std::getline(fajl, sor)) {
            if (sor.rfind("Becenév:", 0) == 0) {
                akt_becenev = sor.substr(9); // "Becenév: " után
            }
            else if (sor.rfind("Jelszo:", 0) == 0) {
                akt_jelszo = sor.substr(8); // "Jelszo: " után

                // Ekkor már van egy párunk — ellenõrzés
                if (akt_becenev == becenev && akt_jelszo == jelszo) {
                    return true;
                }

                // Ellenkezõ esetben tovább megyünk a következõ blokkra
                akt_becenev.clear();
                akt_jelszo.clear();
            }
        }

        return false;
    }


    std::string szovegbekeres(std::string fajlnev) {

        std::string szoveg;
        std::fstream fajl(fajlnev);
        std::string fajlsor;
        while (std::getline(fajl, fajlsor)) std::cout << "\n" << fajlsor;
        fajl.close();
        std::getline(std::cin, szoveg);
        std::cout << "              |_________________________________________________| \n \n";
        return szoveg;

    }



    int verifymail(std::string email, int counter, std::string body) {

        std::cout << "\n \n \n \n \n Verifying your e-mail account.. Please wait..";
        std::string key = mail(email, body);
        std::string userkey;

        if (key == "abc") {

            std::cout << "Ooops.. wrong email.. Try again!";
            counter = 1;

        }

        else {

            std::fstream fajl("verifytop.txt");
            std::string fajlsor;
            while (std::getline(fajl, fajlsor)) std::cout << "\n" << fajlsor;
            fajl.close();
            std::cout << email << ". Please follow the steps there! ";

            userkey = szovegbekeres("verifybottom.txt");
        }

        if (userkey == key) counter = 5;
        else {

            counter--;

        }
        return counter;

    }


    bool jelszomodositas(User user) {

        int counter = 3;
        while (counter != 5)
        {
            counter = verifymail(keresEmailCim("jatekos.txt", user.getname()), counter, "If you requested the chnge of password, the verification number is ");
        }

        std::string password = szovegbekeres("password.txt");
        std::string repass;
        while (repass != password) repass = szovegbekeres("repass.txt");

        return modositFelhasznalo("jatekos.txt", user.getname(), 1, password);

    }





    User regisztracio() {

        bool vanilyen = true;
        std::string user;
        while (vanilyen) {
            for (int i = 0; i < 50; i++) std::cout << "\n";
            user = szovegbekeres("username.txt");
            vanilyen = vanuser(user);
        }
        for (int i = 0; i < 5; i++) std::cout << "\n";
        std::string email = szovegbekeres("email.txt");

        int counter = 3;
        while (counter != 5) {

            counter = verifymail(email, counter, "If you registered to CATcha your verification code is ");
            if (counter == 0) { email = szovegbekeres("email.txt"); counter = 3; }

        }

        std::string password = szovegbekeres("password.txt");
        std::string repass;
        while (repass != password) repass = szovegbekeres("repass.txt");

        std::fstream file_example("jatekos.txt", std::ofstream::out | std::ofstream::app);
        file_example << "e-mail cím: " << email << "\nBecenév: " << user << "\nJelszo: " << password << "\nJatszott: 0\n\n";
        return User(email, user, password);
    }




    User bejelentkezes() {

        std::string user;
        std::string pass;
        bool helyes = false;
        while (not helyes) {

            for (int i = 0; i < 50; i++) std::cout << "\n";
            user = szovegbekeres("nickname.txt");
            pass = szovegbekeres("pass.txt");
            helyes = ervenyes_felhasznalo("jatekos.txt", user, pass);
            if (not helyes) {

                std::cout << "\n \n \n \n Uhh something went wrong.. Maybe you did a typeo? \n \n \n";
                bool nextstep = bipolar("loginparos.txt", "loginparatlan.txt");
                if (nextstep) jelszomodositas(User(keresEmailCim("jatekos.txt", user), user, "..."));

            }

        }
        return User(keresEmailCim("jatekos.txt", user), user, pass);
    }


    bool usermodosit() {

        User user = bejelentkezes();

        int funkcio = arrowfind(4, 3, "nextstep.txt", 6);
        if (funkcio == 1) return jelszomodositas(user);
        if (funkcio == 0) {

            std::string email = szovegbekeres("email.txt");

            int counter = 3;
            while (counter != 5) {

                counter = verifymail(email, counter, "If you registered to CATcha your verification code is ");
                if (counter == 0) { email = szovegbekeres("email.txt"); counter = 3; }

            }
            return modositFelhasznalo("jatekos.txt", user.getname(), 2, email);


        }
        return false;
    }

    double leftright(double start, double diff, std::function<void(double, bool)> muvelet, double min, double max, bool funchoz) {

        muvelet(start, funchoz);
        econio_rawmode();

        while (true) {

            int key = econio_getch();
            if (key == KEY_RIGHT) {

                if (start < max) start += diff;
                muvelet(start, funchoz);

            }
            if (key == KEY_LEFT) {

                if (start > min) start -= diff;
                muvelet(start, funchoz);

            }
            if (key == KEY_ENTER) break;

        }
        econio_normalmode();
        return start;

    }


    void ertekel() {

        User user = bejelentkezes();
        double star = leftright(0.1, 0.1, [this](double s, bool b) { this->csillag(s, b); }, 0.1, 5, true);

        for (int i = 0; i < 50; i++) std::cout << "\n";
        fajlkiolvas("specify.txt");
        for (int i = 0; i < 5; i++) std::cout << "\n";
        std::string specizett;
        std::getline(std::cin, specizett);

        std::fstream file_example("velemenyek.txt", std::ofstream::out | std::ofstream::app);
        file_example << user.getname() << "\n" << star << " csillag\n" << specizett << "\n\n";

        std::ifstream osszesites("osszesito.txt");
        int ertekelok; double csillag;
        osszesites >> ertekelok >> csillag;
        double newnum = (ertekelok * csillag + star) / (ertekelok + 1);
        ertekelok += 1;

        std::ofstream osszesitett("osszesito.txt");
        osszesitett << ertekelok << "\n" << newnum << "\n";

    }





    comment** read_comments(size_t& count, const std::string& filename = "velemenyek.txt") {
        std::ifstream file(filename);
        if (!file) {
            count = 0;
            return nullptr;
        }

        // First, count the number of comments (each comment is 3 lines, skip empty lines)
        size_t comment_lines = 0;
        std::string tmp;
        while (std::getline(file, tmp)) {
            if (!tmp.empty()) ++comment_lines;
        }
        file.clear();
        file.seekg(0);

        size_t max_comments = comment_lines / 3 + 1;
        comment** comments = new comment * [max_comments];
        count = 0;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue; // skip empty lines

            std::string nev = line;

            // Read rating line
            if (!std::getline(file, line)) break;
            std::istringstream iss(line);
            double csillag;
            iss >> csillag;

            // Read text line
            if (!std::getline(file, line)) break;
            std::string szoveg = line;

            // Skip possible empty line between comments
            std::getline(file, line);

            // Use your constructor
            if (count < max_comments - 2) 
                comments[count++] = new comment(nev, csillag, szoveg);
        }

        return comments;
    }



    void walkcomments(Kiolvasando** allcomments, int count) {

        int idx = 0;
        fajlkiolvas("commentsection.txt");
        bool kilepett = false;
        econio_rawmode();
        while (not(kilepett)) {

            int key = econio_getch();
            if (key == KEY_RIGHT) { if (idx >= count - 1) idx = 0; else idx++; }
            if (key == KEY_LEFT) { if (idx <= 0) idx = count - 1; else idx--; }
            if (allcomments[idx] != nullptr) {
                allcomments[idx]->prnt();
                fajlkiolvas("commentsection.txt");
            }
            else {
                std::cout << "nullptr";
            }

            if (key == KEY_ESCAPE) {

                for (int i = 0; i < count; ++i) {
                    delete allcomments[i];
                    allcomments[i] = nullptr;
                }
                delete[] allcomments;
                allcomments = nullptr;
                kilepett = true;

            }

        }
        econio_normalmode();
    }





    void sizew(double sized, bool smth = false) {

        for (int i = 0; i < 50; i++) std::cout << "\n";
        fajlkiolvas("sizetop.txt");
        std::cout << sized;
        fajlkiolvas("sizebottom.txt");

    }


    void sizel(double sized, bool smth = false) {

        for (int i = 0; i < 50; i++) std::cout << "\n";
        fajlkiolvas("sizelength.txt");
        std::cout << sized;
        fajlkiolvas("sizebottom.txt");

    }




    User szemelyek(std::string paratlan, std::string paros, std::string kit, std::string info) {

        User szemely;
        bool signreg = bipolar(paratlan, paros);
        if (signreg) szemely = regisztracio();
        else szemely = bejelentkezes();
        for (int i = 0; i < 50; i++) std::cout << "\n";
        fajlkiolvas(kit);
        fajlkiolvas(info);
        system("pause >nul");
        return szemely;

    }



    void tablarajzol(Mezo* tabla, int width, int length, Cat cica) {

        std::cout << "  ";
        std::string betuk = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < length; i++) std::cout << " " << betuk[i] << " ";
        std::cout << "\n";
        for (int i = 0; i < length; i++) std::cout << "___";
        std::cout << "\n";

        for (int i = 0; i < width; i++) {

            for (int z = 0; z < 2; z++) {

                for (int j = 0; j < length; j++) {

                    if (z == 0) {

                        if (j == 0) std::cout << betuk[i] << " ";
                        if (cica.hol() == tabla[i * length + j]) cica.drawline();
                        else std::cout << tabla[i * length + j].drawline1();

                    }
                    else {
                        if (j == 0) std::cout << "  ";
                        std::cout << tabla[i * length + j].drawline2();
                    }

                }
                std::cout << "| \n";

            }

        }

    }



    /// <summary>
    /// Search for a neighbour of a piece in the board and returns it.
    /// </summary>
    /// <param name="tabla">
    /// The whole board
    /// </param>
    /// <param name="mezo">
    /// The reference piece 
    /// </param>
    /// <param name="xdiff">
    /// the index-differentation in the horizontal line
    /// -1, 0, 1
    /// </param>
    /// <param name="ydiff">
    /// the index-differentation in the vertical line
    /// -1, 0, 1
    /// </param>
    /// <returns>
    /// The piece moved away by the corresponding params rom the original piece, or an unexisting piece if cant find any
    /// </returns>
    Mezo keresszomszed(Mezo* tabla, Mezo mezo, int xdiff, int ydiff, int length, int width) {

        Mezo invalid;
        int keresettx = mezo.getx() + xdiff;
        int keresetty = mezo.gety() + ydiff;
        for (int i = 0; i < width * length; i++) {

            if (tabla[i].getx() == keresettx && tabla[i].gety() == keresetty && tabla[i].getfreem()) return tabla[i];

        }



        return invalid;
    }



    void tablament(std::string fajlnev, Mezo* tabla, int width, int length, Cat cat, Man man) {

        std::fstream file_example(fajlnev, std::ofstream::out | std::ofstream::app);
        file_example << "Cat was " << cat.getname() << "\n" << "Man was " << man.getname() << "\n" << "Width of table: " << width << "\n" << "Height of table: " << length << "\n" << "Fields: (id | stone | side | free)";
        for (int i = 0; i < width * length; i++) file_example << "\n" << tabla[i].getid() << tabla[i].getstone() << tabla[i].getside() << tabla[i].getfreem();
        file_example << "\n\n";

    }





    std::vector<BeolvasottTabla> tablakiolvas(std::string fajlnev) { 
        std::ifstream file(fajlnev); 
        std::vector<BeolvasottTabla> mentettek;
        std::string sor, user1, user2;
        int width = 0, height = 0;

        while (std::getline(file, sor)) {
            if (sor.rfind("Cat was ", 0) == 0) {
                user1 = sor.substr(8);
            }
            else if (sor.rfind("Man was ", 0) == 0) {
                user2 = sor.substr(8);
            }
            else if (sor.rfind("Width of table: ", 0) == 0) {
                width = std::stoi(sor.substr(sor.find(':') + 1));
            }
            else if (sor.rfind("Height of table: ", 0) == 0) {
                height = std::stoi(sor.substr(sor.find(':') + 1));
            }
            else if (sor.rfind("Fields:", 0) == 0) {
                // Read the board
                Mezo* tabla = new Mezo[width * height];
                User users(keresEmailCim("jatekos.txt", user1), user1, "");
                Cat macs = users;
                User man(keresEmailCim("jatekos.txt", user2), user2, "");
                for (int i = 0; i < width * height; ++i) {
                    //std::cout << i << std::endl; 
                    if (!std::getline(file, sor)) break;
                    if (sor.size() < 5) continue; // Defensive
                    std::string id = sor.substr(0, 2);
                    tabla[i] = Mezo(
                        sajatatoi(sor[1]), // x
                        sajatatoi(sor[0]), // y
                        id,
                        sajatatoi(sor[2]), // stone
                        1,                 // real
                        sajatatoi(sor[3]), // side
                        sajatatoi(sor[4])  // free 
                    );
                    std::cout << sajatatoi(sor[2]) << sajatatoi(sor[4]) << std::endl;
                    if (sajatatoi(sor[2]) == sajatatoi(sor[4])) macs.merre(tabla[i]);
                }
                // Create the table object and push
                mentettek.push_back(BeolvasottTabla(tabla, macs, man, width, height));
            }
        }
        return mentettek;
    }






    BeolvasottTabla** find_tables_by_username(const std::string& username, size_t& found_count, const std::string& filename = "finished.txt") {
        std::vector<BeolvasottTabla> all_tables = tablakiolvas(filename);
        std::vector<BeolvasottTabla*> matches;

        for (auto& table : all_tables) {
            if (table.getcica().getname() == username || table.getman().getname() == username) {
                // Allocate a copy on the heap
                matches.push_back(new BeolvasottTabla(table));
            }
        }

        found_count = matches.size();
        if (found_count == 0) 
            return nullptr;

        BeolvasottTabla** result = new BeolvasottTabla * [found_count];
        for (size_t i = 0; i < found_count; ++i) {
            result[i] = matches[i];
        }
        return result;
    }


    void tablakinez() {

        User user = bejelentkezes();
        size_t count = 0;
        BeolvasottTabla** tables = find_tables_by_username(user.getname(), count);
        walkcomments(reinterpret_cast<Kiolvasando**>(tables), static_cast<int>(count));
    }





    bool savechoice(User embi1, User embi2) {

        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n Please wait...";
        std::string code1 = mail(embi1.getmail(), "You or your partner seem to have chosen to quit the game. If you agree, your code is ");
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n Please wait...";
        std::string code2 = mail(embi2.getmail(), "You or your partner seem to have chosen to quit the game. If you agree, your code is ");
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n Please wait...";

        std::string inputcode1;
        std::string inputcode2;
        for (int i = 0; i < 50; i++) std::cout << "\n";
        fajlkiolvas("save.txt");
        std::cout << "The first code: ";
        std::cin >> inputcode1;
        for (int i = 0; i < 50; i++) std::cout << "\n";
        fajlkiolvas("save.txt");
        std::cout << "The other code: ";
        std::cin >> inputcode2;
        if (inputcode1 == inputcode2 || (inputcode1 != code1 && inputcode1 != code2) || (inputcode2 != code1 && inputcode2 != code2)) return false;
        return true;

    }



    bool catstepcorrect(Mezo next) {

        Mezo invalid;
        if (not(next == invalid)) return true;
        return false;

    }



    Mezo* tableuncat(Mezo* tabla, int width, int length, Mezo now, Mezo next) {

        for (int i = 0; i < width * length; i++) {

            if (tabla[i] == now) tabla[i].setfreem();
            if (tabla[i] == next) { tabla[i].catted(); }

        }
        return tabla;

    }




    bool cicanemlephet(Cat cat, Mezo* tabla, int length, int width) {

        Mezo invalid;
        Mezo next;

        for (int i = -1; i < 2; i++) {

            for (int j = -1; j < 2; j++) {

                next = keresszomszed(tabla, cat.hol(), i, j, length, width);
                if (next == invalid) continue;
                else return false;

            }

        }

        return true;
    }




    void jatsz(Mezo* tabla, Cat cat, Man man, int length, int width) {

        bool gameover = false;
        while (not(gameover))
        {
            tabla = cat.lep(tabla, width, length, man, gameover);
            if (gameover) { break; }
            tablarajzol(tabla, width, length, cat);
            fajlkiolvas("box.txt");
            std::cout << cat.hol().getid() << "\n";
            tabla = man.lep(tabla, width, length, cat, gameover);
            tablarajzol(tabla, width, length, cat);


            if (cat.hol().getside() == true) {

                fajlkiolvas("gazdafucked.txt");
                system("pause >nul");
                fajlkiolvas("cicanyert.txt");
                system("pause >nul");
                modositFelhasznalo("jatekos.txt", cat.getname(), 3, "NA");
                gameover = true;

            }


            if (cicanemlephet(cat, tabla, width, length) == true) {

                fajlkiolvas("cicasucked.txt");
                system("pause >nul");
                fajlkiolvas("gazdanyert.txt");
                system("pause >nul");
                modositFelhasznalo("jatekos.txt", man.getname(), 3, "NA");
                gameover = true;

            }
        }


        tablament("finished.txt", tabla, width, length, cat, man);


        delete[] tabla;
        tabla = nullptr;
    }






    void ujjatek() {
        Man man;
        Cat cat;

        cat = szemelyek("catplaersinin.txt", "catplaerregist.txt", "cica-line-art.txt", "oswald.txt");
        man = szemelyek("manplayersignin.txt", "manplayerregist.txt", "gazda-line-art.txt", "spencer.txt");

        bool shape = bipolar("shapesquare.txt", "shapepolygon.txt");
        if (shape) std::cout << "Yaey its a squareeeee";
        else std::cout << "Interesting! Could it be a 4-pointed polygon?";

        int length = 0;
        int width = 0;
        while (length < 5 || width < 5) {
            length = static_cast<int>(leftright(8, 1, [this](double s, bool b) { this->sizew(s, b); }, 8, 43, false));
            width = static_cast<int>(leftright(8, 1, [this](double s, bool b) { this->sizel(s, b); }, 8, 18, false));
        }

        std::cout << width << ", " << length;

        int maxIndex = width * length;
        if (width <= 0 || length <= 0) 
            return; // Defensive: never allocate zero or negative

        Mezo* pontok = new Mezo[maxIndex];

        std::string szamok = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                std::string id;
                id += szamok[i];
                id += szamok[j];
                int idx = i * length + j;
                if (idx >= 0 && idx < maxIndex) {
                    pontok[idx] = Mezo(i, j, id, false, true, false, true);
                }
            }
        }

        int coor = (width / 2) * length + (length / 2);
        if (coor >= 0 && coor < maxIndex) cat.merre(pontok[coor]);
        srand(static_cast<unsigned int>(time(0)));

        if (pontok != nullptr) {
            for (int i = 0; i < maxIndex; i++) {
                // Only access pontok[i] if i is in range
                if (i >= 0 && i < maxIndex) {
                    if (pontok[i].getx() == 0) pontok[i].sides();
                    if (pontok[i].gety() == 0) pontok[i].sides();
                    if (pontok[i].getx() == width - 1) pontok[i].sides();
                    if (pontok[i].gety() == length - 1) pontok[i].sides();

                    int random = rand() % 10;
                    if (random < 4 && !(cat.hol() == pontok[i])) {
                        pontok[i].stoned();
                    }
                }
            }
        }

        std::cout << "\n \n \n \n \n \n \n \n";
        tablarajzol(pontok, width, length, cat);
        jatsz(pontok, cat, man, length, width);
    }
};












//ez egy teszt teszt itt

// other test comment

//test-test