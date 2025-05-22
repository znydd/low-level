#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_map>

using std::cout;
using std::cin;
using std::string;
using std::transform;
using std::tolower;
using std::unordered_map;
using std::getline;
using std::stoi;


void showTodo(unordered_map<int, string>& todo_list){
    int todo_list_size = todo_list.size();
    cout << "\n";
    cout << "Your Todos: \n";
    if (todo_list_size == 0){
        cout << "Nothing to Do!\n";
        return;
    }

    
    for (int i = 1; i <= todo_list_size; ++i ){
        try{
        cout << i <<". " << todo_list.at(i) << " ⬜\n";
        }catch(const std::out_of_range& e){
        cout << "Todo Not Found\n";
        cout << "Exception "<< e.what() << "\n";
        }
    }
    cout << "\n";
}

void showDone(unordered_map<int, string>& done_list){
    int done_list_size = done_list.size();
    cout << "\n";
    cout << "Task Done: \n";
    if (done_list_size == 0){
        cout << "Nothing finished!\n";
        return;
    }

    
    for (int i = 1; i <= done_list_size; ++i ){
        try{
        cout << i <<". " << done_list.at(i) << " ✅\n";
        }catch(const std::out_of_range& e){
        cout << "Done Not Found\n";
        cout << "Exception "<< e.what() << "\n";
        }
    }
    cout << "\n";
}

void addTodo(unordered_map<int, string>& todo_list){
    int todo_list_size = todo_list.size();
    string todo_input;
    cout << "Enter your Todo:\n";
    getline(cin, todo_input);
    if (todo_input.length() > 100){
        todo_input = todo_input.substr(0, 100);
    }
    todo_list[todo_list_size+1] = todo_input;
}

void addDone(unordered_map<int, string>& done_list, unordered_map<int, string>& todo_list, int todo_no){
    int todo_list_size = todo_list.size();
    if (todo_no > todo_list_size){
        cout << "Out of List!";
        return;
    }

    if (todo_list.find(todo_no) != todo_list.end()) {
        done_list[done_list.size()+1] =  todo_list[todo_no];
        todo_list.erase(todo_no);
        for (int i = todo_no+1; i <= todo_list_size; ++i){
            string tmp = todo_list[i];
            todo_list.erase(i);
            todo_list.insert({i-1, tmp});
        }
        
    } else {
        cout << "Not found on Todo list!\n";
    }
}

int main(){
    cout << "\n";
    cout << "Welcome to TODO CLI 📜\n";
    cout << "======================\n";
    cout << "(+)             -> Add Todo\n";
    cout << "(1-99)          -> Mark as Done\n";
    cout << "(exit/quit/e/q) -> Exit\n";

    string inp;
    unordered_map<int, string> todo_list;
    unordered_map<int, string> done_list;

    while(true){
    showTodo(todo_list);
    showDone(done_list);

    cout << "\nCMD: ";
    getline(cin, inp);

    // input to lower_case
    transform(inp.begin(), inp.end(), inp.begin(),[](unsigned char c){ return static_cast<unsigned char>(tolower(c)); });
    // exit comand
    if (inp == "exit" || inp == "quit" || inp == "e" || inp == "q"){
        break;
    } else if (inp == "+"){
        // add task and save that to todo list
        addTodo(todo_list);
    } else if (inp >= "1" && inp <= "99"){
        // search the task and bring that to the done list
        int todo_no = stoi(inp);
        addDone(done_list, todo_list, todo_no);
    } else {
        cout<< "Wrong Command!⚠️\n";
    }

    }


    return 0;
}