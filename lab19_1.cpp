#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    string text;
    char format [] = "%[^:]: %d %d %d";

    ifstream source;
    source.open(filename);
    
    char s_names[100];
    int one , two , three;

    while (getline(source, text)){
        const char *cStr = text.c_str();
        sscanf(cStr, format, s_names, &one, &two, &three);
        names.push_back(string(s_names));
        scores.push_back(int(one + two + three));
        grades.push_back(score2grade(int(one + two + three)));
    }
}

void getCommand(string & command, string & key){
    string s_text;
    char s_command[100], s_key[100];
    char format [] = "%s %[^\n]";
    cout << "Please input your command: ";
    getline(cin,s_text);
    const char * sc_text = s_text.c_str();
    sscanf(sc_text, format, s_command, s_key);
    command = s_command;
    key = s_key;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int count = 0;
    cout << "---------------------------------" << endl;
    for(int i = 0; i  < int(names.size()) ; i++){
        if (toUpperStr(names.at(i)).compare(toUpperStr(key)) == 0) 
        cout << names.at(i) << "'s score = " << scores.at(i) << "\n" <<  
        names.at(i) << "'s grade = " << grades.at(i) << endl;
        else count++;
    }
    if(count == 26) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------" << endl;
    for(int i = 0; i  < int(names.size()) ; i++)
        if (grades.at(i) == (key[0])) cout << names.at(i) << " (" << scores.at(i) << ")" << endl;
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}