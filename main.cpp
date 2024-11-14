#include <iostream>
#include <string>

#include "stack.h"
#include "queue.h"
#include "Printer_Job.h"
#include "Binary_Search_Tree.h"
#include "AVL_Tree.h"

using namespace std;

void task1(string expr);
void task2();
void task3();
void task5();

int main()
{
    setlocale(LC_ALL, "RU");
    
    string task1_input = "([{}])";
    task1(task1_input);

    task2();

    task3();

    task5();
}

void task1(string expr) {
    cout << "----- task1: -----\n" << endl;

    Stack<char> stack;
    bool is_correct = true;

    for (char* ptr = &expr[0]; *ptr != '\0' && is_correct; ptr++) {
        char ch = *ptr;

        // Если это открывающая скобка, помещаем ее в стек
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        }
        // Если это закрывающая скобка
        else if (ch == ')' || ch == '}' || ch == ']') {
            // Проверяем, есть ли соответствующая открывающая скобка
            if (stack.is_empty()) {
                is_correct = false; // Нет соответствующей открывающей скобки
            }
            else {
                char top = stack.pop();

                // Проверяем соответствие
                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '[')) {
                    is_correct = false; // Неверная пара скобок
                }
            }
        }
    }

    // Если стек не пуст, скобки некорректны
    if (is_correct && !stack.is_empty()) is_correct = false;

    if (is_correct) cout << "task1: все скобки корректны.\n" << endl;
    else cout << "task1: скобки некорректны.\n" << endl;
}

void task2() {
    cout << "\n----- task2: -----\n" << endl;

    Queue<Printer_Job> printQueue; // Очередь для заданий печати
    string jobName;
    int pageCount;

    // Добавление заданий в очередь
    while (true) {
        std::cout << "Введите имя задания (или 'exit' для выхода): ";
        std::getline(std::cin, jobName);
        if (jobName == "exit") {
            break; // Выход из цикла
        }

        std::cout << "Введите количество страниц: ";
        std::cin >> pageCount;
        std::cin.ignore(); // Очистка буфера ввода

        printQueue.insert(Printer_Job(jobName, pageCount)); // Добавление задания в очередь
    }

    // Обработка заданий из очереди
    while (!printQueue.empty()) {
        Printer_Job currentJob = printQueue.get(); // Получение задания из начала очереди
        printQueue.remove(); // Удаление задания из очереди
        print_job(currentJob); // Печать задания
    }
}

void task3() {
    cout << "\n----- task3: -----\n" << endl;

    Binary_Search_Tree bst;

    Data contact_1({ 1, "Dan" });
    Data contact_2({ 2, "Andrew" });
    Data contact_3({ 3, "Vlad" });
    Data contact_4({ 4, "Oleg" });
    Data contact_5({ 5, "Alexander" });
    Data contact_6({ 6, "Daneon" });
    Data contact_7({ 7, "Vlad-Oleg" });

    bst.insert(contact_1);
    bst.insert(contact_2);
    bst.insert(contact_3);
    bst.insert(contact_4);
    bst.insert(contact_5);
    bst.insert(contact_6);
    bst.insert(contact_7);

    cout << "Inorder traversal: ";
    bst.inorder();
    cout << "Preorder traversal: ";
    bst.preorder();
    cout << "Postorder traversal: ";
    bst.postorder();

    string search_name = "Dan";
    Binary_Search_Tree::Node* result = bst.search(search_name);

    if (result) {
        cout << "Found: " << result->value.name << endl;
        cout << "Phone: " << result->value.phone << endl;
    }
    else {
        cout << "Contact " << search_name << " not found." << endl;
    }
}

void task5() {
    cout << "\n----- task5: -----\n" << endl;

    AVL_Tree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "Inorder traversal of the AVL tree is: ";
    tree.inorder();
    std::cout << "Preorder traversal of the AVL tree is: ";
    tree.preorder();
    std::cout << "Postorder traversal of the AVL tree is: ";
    tree.postorder();

    tree.delete_node(30);
    std::cout << "Inorder traversal after deletion of 30: ";
    tree.inorder();

    int search_num = 25;
    AVL_Tree::Node* result = tree.search(search_num);

    cout << endl;

    if (result) {
        cout << "Found: " << result->value << endl;
    }
    else {
        cout << "Contact " << search_num << " not found." << endl;
    }
}
