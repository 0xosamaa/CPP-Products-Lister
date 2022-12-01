#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <ctime>

using namespace std;


class Menu {
    char menu_items[3][8];
    int cursor;
    int key_pressed;
    int amount_to_enter;
    char name[10];
    int price;

public:
    Menu() {
        strcpy_s(menu_items[0], "New");
        strcpy_s(menu_items[1], "Display");
        strcpy_s(menu_items[2], "Exit");
        cursor = 0;
        amount_to_enter = 0;
        key_pressed = NULL;
    }
    void showMenu() {

        for (int i = 0; i < 3; i++) {

            gotoxy(10, 7 + i);
            if (i == cursor) {
                textattr(0x70);
                cout << menu_items[i];
                textattr(0x07);
            }
            else {
                cout << menu_items[i];
            }
        }
        gotoxy(10, 7 + cursor);
    }

    void navigateMenu() { 

        do {
            showMenu();
            key_pressed = _getch();

            switch (key_pressed) {
            case 80:
                cursor++;
                gotoxy(10, 7 + cursor);
                if (cursor > 2) {
                    cursor = 0;
                }
                break;
            case 72:
                cursor--;
                gotoxy(10, 7 + cursor);
                if (cursor < 0) {
                    cursor = 2;
                }
                break;

            case 13:
                system("CLS");
                if (cursor == 0) {
                    fstream products;
                    products.open("products_data.txt", ios_base::app);
                    if (!products)
                    {
                        cout << "File creation failed";
                    }
                    else {
                        cout << "Enter number of products:" << endl;
                        cin >> amount_to_enter;
                        for (int i = 0; i < amount_to_enter; i++) {
                            cout << "Enter Product " << i + 1 << " Name:";
                            cin >> name;
                            cout << "Enter Price of product " << i + 1 << ":";
                            cin >> price;
                            products << "Product Name:" << endl;
                            products << name << endl;
                            products << "Product Price:" << endl;
                            products << price << endl;
                            cout << "Data Saved";
                        }
                        products.close();
                    }
                }
                else if (cursor == 1) {
                    std::ifstream products("products_data.txt");
                    if (products.is_open()) {
                        char file_char;
                        while (products) {
                            file_char = products.get();
                            std::cout << file_char;
                        }
                    }
                }
                else {
                    exit(EXIT_SUCCESS);
                }
                _getch();
                system("CLS");
                break;
            }
        } while (key_pressed != 27);
    }
        
    void textattr(int i)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
    }

    void gotoxy(int x, int y)
    {
        COORD coord = { 0,0 };
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

};


int main()
{
    Menu m;
    m.navigateMenu();
    _getch();




   
}

