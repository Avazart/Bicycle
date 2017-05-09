#include <iostream>

#include "Win/Process/Process.h"

int main()
{
    using namespace std;
    using namespace Bicycle;
    try
    {
        Process process;
        process.start(L"",L"calc"); // Запускаем калькулятор
        process.waitForInputIdle(); // Ждем готовности калькулятора
        cout<<"Process ready."<<endl;

        // Ждем 5 сек и закрываем программу
        Sleep(5000);
        process.closeWindows(); // Шлем WM_CLOSE окну
        process.waitForFinished(); // Ждем завершения калькулятора
        cout<<"Process finished with exit code #"<< process.exitCode() <<endl;
    }
    catch(const Exception& e)
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        cerr<< e.message()<<endl;
    }
    getchar();
    return 0;
}
