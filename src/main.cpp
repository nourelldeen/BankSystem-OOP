#include "../include/clsLoginScreen.h"
#include <iostream>

int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
            break;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}