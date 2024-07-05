// Your First C++ Program

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <limits>
using namespace std;

class Todo {
    private:
        string title;
        string description;
        bool completed;
    public:
        Todo(string title, string description) {
            cout << "Task created" << endl;
            this->title = title;
            this->description = description;
            this->completed = false;
        }
        void print() {
            cout << title << " - " << description << " - " << (completed ? "Completed" : "Pending") << endl;
        }
        void completeToDo() {
            completed = true;
            cout << "Todo completed" << endl;
        }
        bool isCompleted() {
            return completed;
        }

        string serialize() {
            return title + " - " + description + " - " + (completed ? "Completed" : "Pending");
        }

        Todo(string searializedTodo) {
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
};


void clearScreen(){
    cout << string(100, '\n');
}

void pressEnterToContinue(){
    cout << "Press Enter to continue...";
    getch();
    clearScreen();
}

bool stringListContains(list<string> l, const string& s) {
    return find(l.begin(), l.end(), s) != l.end();
}

string displayMainMenu() {
    string choice = "-1";
    list<string> validChoices = {"1", "2", "3", "4"};
    clearScreen();
    while (stringListContains(validChoices, choice) == false){
        cout << "Main Menu" << endl;
        cout << "---------" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. List Tasks" << endl;
        cout << "3. Complete Task" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(stringListContains(validChoices, choice) == false) {
            clearScreen();
            cout << "**Invalid choice** : \""+choice+"\"" << endl;            
        }
    }
    return choice;
}


list<Todo> loadTodos(){
    list<Todo> todos;
    ifstream file;
    file.open("todo.txt");
    bool fileExists = file.good();
    for( string line; getline( file, line ); )
    {;
        Todo todo = Todo(line);
        todos.push_back(todo);
    }
    if(fileExists == false){
        cout << "No save file found a new file will be created" << endl;
    }else{
        cout << "File Loaded" << endl;
    }
    file.close();
    cin.clear();
    cin.sync();
    pressEnterToContinue();
    return todos;
}

void save(list<Todo> todos){
    ofstream file;
    file.open("todo.txt");
    for (Todo todo : todos) {
        file << todo.serialize() << endl;
    }
    file.close();
}

int main() {
    list<Todo> todos;
    string quit = "4";
    string choice = "-1";
    todos = loadTodos();

    while (1 == 1) {
        choice = displayMainMenu();
        clearScreen();
        if(choice == quit){
            break;
        }
        if (choice == "1") {
            cout << "Add Task" << endl;
            cout << "--------" << endl;
            string title;
            string description;
            cout << "Enter title: ";
            cin >> title;
            cout << "Enter description: ";
            cin >> description;
            Todo todo = Todo(title, description);
            todos.push_back(todo);
        } else if (choice == "2") {
            cout << "List Tasks" << endl;
            cout << "----------" << endl;
            for (Todo todo : todos) {
                todo.print();
            }
        } else if (choice == "3") {
            cout << "Complete Task" << endl;
            cout << "-------------" << endl;
            int index = 1;
            for (Todo todo : todos) {
                if(todo.isCompleted() == false){
                    cout << index << ". ";
                    todo.print();
                    index++;
                }
            }
            if(index == 1){
                cout << "No pending tasks" << endl;
                continue;
            }
            int taskIndex;
            cout << "Which task would you like to complete? ";
            cin >> taskIndex;
            taskIndex--;
            if (taskIndex >= 0 && taskIndex < todos.size()) {
                list<Todo>::iterator it = todos.begin();
                advance(it, taskIndex);
                it->completeToDo();
            } else {
                cout << "Invalid task index" << endl;
            }
        }
        pressEnterToContinue();
        save(todos);
    }
    return 0;
}