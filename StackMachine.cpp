// StackMachine.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"Program.h"

void print(Stack* st)
{
    std::cout << st->peek() << std::endl;
    return;
}


int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 2)
    {
        std::cout << "Invalid command line parameters.";
        throw std::exception();
    }
    Stack* stack = new Stack();
    Logger* log = NULL;
    if (argc == 3)
    {
        if (std::strcmp(argv[2], "-debug") == 0)
        {
            log = new Logger();
        }
        else
        {
            std::cout << "Invalid second argument.";
            throw std::exception();
        }
    }
    Program go(log);
    try
    {
        go.lexer("file.txt");
        go.add_extern_func("print", print);
        go.run(go.get_index_of_main(), stack);
        std::cout << "Result stack:" << std::endl;
        stack->print();
    }
    catch (const std::exception& ex)
    {
        std::cout << "Exception:" << ex.what() << std::endl;
    }
    
   
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
