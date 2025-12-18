#pragma once

#include "filekezeles.h";
#include "ertekeles.h"


int arrowfind(int jelenlegi, int elsovalasz, int maxvalasz, const char* fajlnev, int ertekeles, int funkcio) { 

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT)); // Nyers input mód

    INPUT_RECORD input;
    DWORD count;

    for (int i = 0; i < 25; i++) std::cout << "\n"; 
    fajlkiolvas("cica line-art.txt"); 
    jelenlegi = valaszto(elsovalasz, maxvalasz, jelenlegi, fajlnev, ertekeles); 

    while (true) {
        ReadConsoleInput(hStdin, &input, 1, &count);

        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            WORD key = input.Event.KeyEvent.wVirtualKeyCode;

            switch (key) {
            case VK_DOWN:
                if (funkcio == 0) {
                    jelenlegi++;
                    for (int i = 0; i < 25; i++) std::cout << "\n";
                    fajlkiolvas("cica line-art.txt");
                    jelenlegi = valaszto(elsovalasz, maxvalasz, jelenlegi, fajlnev, ertekeles); 
                    break;
                }
                
            case VK_UP:
                if (funkcio == 0) {
                    jelenlegi--;
                    for (int i = 0; i < 25; i++) std::cout << "\n";
                    fajlkiolvas("cica line-art.txt");
                    jelenlegi = valaszto(elsovalasz, maxvalasz, jelenlegi, fajlnev, ertekeles); 
                    break;
                }
                
            case VK_RIGHT:
                if (funkcio == 1) {
                    std::cout << "megnyomták a jobb gombot";
                    jelenlegi++;
                    for (int i = 0; i < 25; i++) std::cout << "\n";
                    fajlkiolvas("ertekelj.txt");
                    jelenlegi = csillag(jelenlegi / 10);
                }
            
            case VK_LEFT:
                if (funkcio == 1) {
                    std::cout << "megnyomták a bal gombot";
                    jelenlegi--;
                    for (int i = 0; i < 25; i++) std::cout << "\n";
                    fajlkiolvas("ertekelj.txt");
                    jelenlegi = csillag(jelenlegi / 10);
                }

            case VK_RETURN:
                return jelenlegi;
            }
        }
    }

}
