// Your First C++ Program

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <limits>
using namespace std;

class Todo
{
private:
    string title;
    string description;
    bool completed;

public:
    // standard constructor
    Todo(string title, string description)
    {
        cout << "Task created" << endl;
        this->title = title;
        this->description = description;
        this->completed = false;
    }
    
    // constructor for loading from file
    Todo(string searializedTodo)
    {
        string delimiter = " - ";
        size_t pos = 0;
        pos = searializedTodo.find(delimiter);
        title = searializedTodo.substr(0, pos);
        searializedTodo.erase(0, pos + delimiter.length());
        pos = searializedTodo.find(delimiter);
        description = searializedTodo.substr(0, pos);
        searializedTodo.erase(0, pos + delimiter.length());
        completed = searializedTodo == "Completed";
    }

    // function to print the todo
    void print()
    {
        cout << title << " - " << description << " - " << (completed ? "Completed" : "Pending") << endl;
    }

    // function to complete the todo
    void completeToDo()
    {
        completed = true;
        cout << "Todo completed" << endl;
    }

    // function to check if the todo is completed
    bool isCompleted()
    {
        return completed;
    }

    // function to serialize the todo
    string serialize()
    {
        return title + " - " + description + " - " + (completed ? "Completed" : "Pending");
    }
};

// function to clear the screen
void clearScreen()
{
    cout << string(100, '\n');
}


// function to wait for user to press enter
void pressEnterToContinue()
{
    cout << "Press Enter to continue...";
    getch();
    clearScreen();
}


// function to check if a string is in a list
bool stringListContains(list<string> l, const string &s)
{
    return find(l.begin(), l.end(), s) != l.end();
}


// function to display the main menu
string displayMainMenu()
{
    string menuChoice = "-1";
    list<string> validChoices = {"1", "2", "3", "4"};
    clearScreen();
    while (stringListContains(validChoices, menuChoice) == false)
    {
        cout << "Main Menu" << endl;
        cout << "---------" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. List Tasks" << endl;
        cout << "3. Complete Task" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> menuChoice;
        if (stringListContains(validChoices, menuChoice) == false)
        {
            cout << "**Invalid choice** : \"" + menuChoice + "\"" << endl;
        }
        clearScreen();
    }
    return menuChoice;
}


// function to load todos from file
list<Todo> loadTodos()
{
    list<Todo> todos;
    ifstream file;
    file.open("todo.txt");
    bool fileExists = file.good();
    for (string line; getline(file, line);)
    {
        Todo todo = Todo(line);
        todos.push_back(todo);
    }
    if (fileExists == false)
    {
        cout << "No save file found a new file will be created" << endl;
    }
    else
    {
        cout << "File Loaded" << endl;
    }
    file.close();
    cin.clear();
    cin.sync();
    pressEnterToContinue();
    return todos;
}


// function to save todos to file
void save(list<Todo> todos)
{
    ofstream file;
    file.open("todo.txt");
    for (Todo todo : todos)
    {
        file << todo.serialize() << endl;
    }
    file.close();
}


// main function
int main()
{
    list<Todo> todos;
    string quit = "4";
    string choice = "-1";
    todos = loadTodos();

    // main loop
    while (1 == 1)
    {
        choice = displayMainMenu();
        clearScreen();
        if (choice == quit)
            break;
        if (choice == "1")
        {
            cout << "Add Task" << endl;
            cout << "--------" << endl;
            string title;
            string description;
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter description: ";
            getline(cin, description);
            Todo todo = Todo(title, description);
            todos.push_back(todo);
        }
        else if (choice == "2")
        {
            cout << "List Tasks" << endl;
            cout << "----------" << endl;
            for (Todo todo : todos)
            {
                todo.print();
            }
        }
        else if (choice == "3")
        {
            cout << "Complete Task" << endl;
            cout << "-------------" << endl;
            int index = 1;
            for (Todo todo : todos)
            {
                if (todo.isCompleted() == false)
                {
                    cout << index << ". ";
                    todo.print();
                    index++;
                }
            }
            if (index == 1)
            {
                cout << "No pending tasks" << endl;
            }
            else
            {
                int taskIndex;
                cout << "Which task would you like to complete? ";
                cin >> taskIndex;
                if (taskIndex >= 1 && taskIndex < index)
                {
                    int currentIndex = 1;
                    for (auto it = todos.begin(); it != todos.end(); ++it)
                    {
                        if (!it->isCompleted())
                        {
                            if (taskIndex == currentIndex)
                            {
                                it->completeToDo();
                                break;
                            }
                            currentIndex++;
                        }
                    }
                }
                else
                {
                    cout << "Invalid task index" << endl;
                }
            }
        }
        pressEnterToContinue();
        save(todos);
    }
    return 0;
}