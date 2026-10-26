#include "MyForm.h"
#include <windows.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Project1::MyForm form; 
    Application::Run(% form);
    return 0;
}