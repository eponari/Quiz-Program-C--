//standart libraries we need for some functions and objects.
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

ifstream read_data;
ofstream save_data;

//enum used for switch cases.
enum sorting_methods{
    sort_by_id,
    sort_by_name,
    sort_by_avg
};

enum admin_functions{
    show_sorted,
    find_user_by_name,
    change_question,
    exiting_admin
};

enum user_functions{
    testing,
    history,
    score,
    exiting_user
};

enum subjects{
    algebra,
    physics,
    programming
};

enum status{
    admin,
    normal_user,
    regist
};

//structures for organizing the data
//default parameters for structure
struct date{
    int year=2020,month=1,day=1;
};

struct question{
    string question;
    string answer_1;
    string answer_2;
    int correct,user_answer,id;
    //method for a quick check
    bool is_correct(){
        return user_answer==correct;
    }
};
//each test has 20 questions and a score
struct test{
    question questions[20];
    int score=0;
    date date_taken;
};

struct user{
    string name,surname,username,password;
    int id,score=0,total=0,age;
    //dynamic array for a unknown number of tests
    vector <test> tests;
};

//some databases we can use for admins,users and tests
//vectors are default structures that we get from libraries and with them come different default methods like .begin(),.end(),.size()
vector <test> curriculum;
vector <user> users;
string admins[3][2]={
    {"admin","admin"},
    {"administator","1234567890"},
    {"owner","ponari"}
};

//prototypes of functions I will write below
void admin_login();
void user_login(user* main_user);
test get_test();
user get_user();
void load_data();
void saving_data();
void new_user();
void mainpage();
void admin_page();
void user_authentication();
void take_test(user*,test);
void show_history(test);
void show_all_users();

//function to use for sorting operator
bool compare_by_avg(user a,user b);
bool compare_by_id(user a,user b);
bool compare_by_name(user a,user b);

//template,recursion,searching,parsing arrays in functions(2D arrays and dynamic arrays) and function overload examples (5 in one) :P
//to be honest couldn't find a good place to use them since most of my work is based in global variables but pointers could be used 
//in every function when it came to users and admins
template<class T>
int user_exists(T name,vector <user> users,int pos=0){
    if(pos==int(users.size())){
        return -1;
    }
    if(name==users[pos].username){
        return pos;
    }
    return user_exists(name,users,pos+1);
}

int user_exists(string name,string admins[][2],int pos=0){
    if(pos==3){
        return -1;
    }
    if(name==admins[pos][0]){
        return pos;
    }
    return user_exists(name,admins,pos+1);
}

//the main function
int main()
{
    //loads databases
    load_data();
    mainpage();
    //saves databases
    saving_data();
    return 0;
}

//function to show up the options users have
void mainpage(){
    system("CLS");
    cout<<"Welcome to Check Your Knowledge!\nPlease login or register.\n1.Login as admin.\n2.Login as user\n3.Register.\n";
    int option;
    cin>>option;
    //uses enum for switch cases
    status login_status=status(option-1);
    switch(login_status){
        case admin:
            admin_login();
            break;
        case normal_user:
            user_authentication();
            break;
        case regist:
            cout<<"Welcome new user!\n";
            new_user();
            break;
    }
}

//function to check for an admin from a 2D array in another file and uses the searching function above.
void admin_login(){
    system("CLS");
    string username,password;
    cout<<"Enter your admin username: (hint:if you don't have any, try admin)\n";
    cin>>username;
    cout<<"Enter your admin password: (hint:if you don't have any, try admin)\n";
    cin>>password;
    int position=user_exists(username,admins);
    if(position>=0&&admins[position][1]==password){
        admin_page();
    }
    else{
        cout<<"Sorry, this password isn't valid. Try to register as a user if you are not a admin.\n";
        cout<<"\nPress y to continue. Anything else to exit.\n";
        char ans;
        cin>>ans;
        if(ans=='y'){
            mainpage();
        }
    }
}

//page for admins and their functions
void admin_page(){
    system("CLS");
    cout<<"Welcome Admin!\n";
    int option;
    char answer;
    while(1){
        cout<<"Do you want to:\n1.Show all users.\n2.Find user by username.\n3.Edit a question by ID.\n4.Exit application.\n";
        cin>>option;
        admin_functions choice=admin_functions(option-1);
        switch(choice){
            case show_sorted:
                {
                    system("CLS");
                    cout<<"Do you want them sorted by:\n1.ID\n2.Name\n3.Average score.\n";
                    cin>>option;
                    sorting_methods method=sorting_methods(option-1);
                    switch(method){
                        case sort_by_id:
                            //sort the vector by this function that we use as a operator(default function from algorithms library)
                            sort(users.begin(),users.end(),compare_by_id);
                            break;
                        case sort_by_name:
                            //sort the vector by this function that we use as a operator(default function from algorithms library)
                            sort(users.begin(),users.end(),compare_by_name);
                            break;
                        case sort_by_avg:
                            //sort the vector by this function that we use as a operator(default function from algorithms library)
                            sort(users.begin(),users.end(),compare_by_avg);
                            break;
                    }
                    show_all_users();
                    //asks if the user wants to continue to redirect him to main page
                    cout<<"\nTo continue press y. Press any other button to exit.\n";
                    cin>>answer;
                    if(answer!='y'){
                        return;
                    }
                }
            break;
            case find_user_by_name:
                {
                system("CLS");
                string username;
                cout<<"Enter the username of the user you want to find:\n";
                cin>>username;
                int position=user_exists(username,users);
                //uses searching algorithm to detect the user and if he doesn't exist he has a index of -1
                if(position>=0){
                    user main_user=users[position];
                    int test_number;
                    cout<<"This user has "<<int(main_user.tests.size())<<" tests. Which one do you want to see?\n";
                    cin>>test_number;
                    if(test_number>=1&&test_number<=int(main_user.tests.size())){
                        show_history(main_user.tests[test_number-1]);
                    }
                    //if test isn't in range
                    else{
                        cout<<"Sorry this test doesn't exist. Try a different test.\n";
                    }
                }
                //if index==-1
                else{
                    cout<<"Sorry this user doesn't exist.Try again.";
                }
                cout<<"\nTo continue press y. Press any other button to exit.\n";
                cin>>answer;
                if(!(answer=='y')){
                    return;
                }
                break;
                }
            case change_question:
                {
                int id;
                string white;
                cout<<"Enter the ID of the question you want to modify:\n";
                cin>>id;
                getline(cin,white);
                system("CLS");
                if(id<=int(curriculum.size())*20){
                    //each test has 20 questions. since index starts from 0 we can do this formula to find in what test this question is by using / . then with % we see the position in this tests of our question
                    //use pointer to effect the value in this address
                    question *edit_question=&curriculum[(id-1)/20].questions[(id-1)%20];
                    string change;
                    int correct;
                    //asks for each property of a question and gives the user the chance to not do any change to a property
                    cout<<"HINT: Type _ if you don't want to change a field in the question!(Doesn't work for correct answer you should give a input there.)\n";
                    cout<<"Current question: "<<edit_question->question<<endl;
                    getline(cin,change);
                    if(change!="_"){
                        edit_question->question=change;
                    }
                    cout<<"Current alternative 1: "<<edit_question->answer_1<<endl;
                    getline(cin,change);
                    if(change!="_"){
                        edit_question->answer_1=change;
                    }
                    cout<<"Current alternative 2: "<<edit_question->answer_2<<endl;
                    getline(cin,change);
                    if(change!="_"){
                        edit_question->answer_2=change;
                    }
                    cout<<"Current correct alternative: "<<edit_question->correct<<endl;
                    cin>>correct;
                    edit_question->correct=correct;
                }
                //question is out of index
                else{
                    cout<<"This question does not exist. Try again for a different question.";
                }
                break;
                }
            case exiting_admin:
            {
            system("CLS");
            return;
            }
        }
        system("CLS");
    }
}

//function to print all users in the vector users by a loop
void show_all_users(){
    system("CLS");
    cout<<"Id\tUsername\tName\tSurname\tAge\tScore\tTotal\tAverage\n";
    for(int i=0;i<int(users.size());i++){
        cout<<users[i].id<<"\t"
        <<users[i].username<<"\t"
        <<users[i].name<<"\t"
        <<users[i].surname<<"\t"
        <<users[i].age<<"\t"
        <<users[i].score<<"\t"
        <<users[i].total<<"\t";
        if(users[i].total){
            cout<<double(users[i].score)/users[i].total<<"\n";
            }
        else{
            //checks for the division by 0 error.
            cout<<0<<"\n";
        }
    }
}

//3 functions that act as operators for my sort function used by admins.
bool compare_by_id(user a,user b){
    return a.id<b.id;
}

bool compare_by_name(user a,user b){
    if(a.name!=b.name){
        return a.name<b.name;
    }
    return a.surname<b.surname;
}

bool compare_by_avg(user a,user b){
    //check for division by 0 and if it is true than return that the other is bigger
    if(a.total==0){
        return false;
    }
    //if total b is 0 than a is always bigger even if they both are 0
    else if(b.total==0){
        return true;
    }
    return double(a.score/a.total)>double(b.score/b.total);
}

//takes information and sees if this user is in the vector users and if their passwords match.
void user_authentication(){
    system("CLS");
    user newuser;
    cout<<"Enter your username:\n";
    cin>>newuser.username;
    cout<<"Enter your password:\n";
    cin>>newuser.password;
    int found_at=user_exists(newuser.username,users);
    //if one of these is false than this user doesn't have access
    if (found_at>=0&&users[found_at].password==newuser.password){
        user_login(&users[found_at]);
    }
    else{
        
        cout<<"The username or password is wrong. Pleases register as a new user or try again to login by pressing any character.\n";
        char ans;
        cin>>ans;
        mainpage();
    }
}
//user control panel with a pointer as parameter
void user_login(user* main_user){
    system("CLS");
    cout<<"Welcome "<<main_user->name<<".\n";
    int option;
    char answer;
    //switch case to let the user choose what he/she wants to do
    while(1){
        cout<<"Do you want to:\n1.Take a test.\n2.See history of a test.\n3.See your total score and % done right.\n4.Exit application.\n";
        cin>>option;
        user_functions choice=user_functions(option-1);
        switch(choice){
            case testing:
                {
                system("CLS");
                cout<<"Which test do you want to take?\n1.Maths\n2.Physics\n3.Programming\n";
                cin>>option;
                //enum used to make the switch case cleaner
                subjects taking_test=subjects(option-1);
                switch(taking_test){
                    case algebra:
                        take_test(main_user,curriculum[0]);
                        break;
                    case physics:
                        take_test(main_user,curriculum[1]);
                        break;
                    case programming:
                        take_test(main_user,curriculum[2]);
                        break;
                }
                }
                break;
            case history:
                system("CLS");
                int number_test;
                cout<<"You have "<<main_user->tests.size()<<" available tests.Which one do you want to choose?\n";
                cin>>number_test;
                //if the tests is within the range prints everything about it
                if(number_test>=1&&number_test<=int(main_user->tests.size())){
                    show_history(main_user->tests[number_test-1]);
                }
                //if test is out of range
                else{
                    cout<<"Sorry this tests doesn't exist.Try again.";
                }
                cout<<"\nTo continue press y. Press any other button to exit.\n";
                cin>>answer;
                if(!(answer=='y')){
                    return;
                }
                break;
            case score:
                system("CLS");
                //gives an overall view of the score of a user compared to the questions he has answered
                cout<<"You have "<<main_user->score<<" points from "<<main_user->total<<" questions taken.\n";
                cout<<"\nTo continue press y. Press any other button to exit.\n";
                cin>>answer;
                if(!(answer=='y')){
                    return;
                }
                break;
            case exiting_user:
                system("CLS");
                return;
        }
        system("CLS");
    }
}

//uses pointers and structures as parameters
void take_test(user* mainuser,test mytest){
    system("CLS");
    mainuser->total+=20;
    for(int i=0;i<20;i++){
        system("CLS");
        //each question takes an answer and checks with the structures method if the answer is right.
        cout<<"HINT: Only press 1 or 2 for alternatives please!\n";
        cout<<i+1<<")"<<mytest.questions[i].question<<"\n";
        cout<<mytest.questions[i].answer_1<<"\t"<<mytest.questions[i].answer_2<<"\n";
        cin>>mytest.questions[i].user_answer;
        if(mytest.questions[i].is_correct()){
            mainuser->score++;
            mytest.score++;
        }
    }
    mainuser->tests.push_back(mytest);
    cout<<"Congrats! For results go to history in your profile!"<<endl;
    cout<<"Press any character to continue to continue"<<endl;
    char ans;
    cin>>ans;
}

//prints every information possible for 20 questions of a test
void show_history(test mytest){
    system("CLS");
    cout<<"Date: "<<mytest.date_taken.day<<"."<<mytest.date_taken.month<<"."<<mytest.date_taken.year<<"\n";
    for(int i=0;i<20;i++){
        cout<<mytest.questions[i].question<<"\n";
        cout<<mytest.questions[i].answer_1<<"  "<<mytest.questions[i].answer_2<<"\n";
        cout<<"Your answer:"<<mytest.questions[i].user_answer<<"  Correct answer:"<<mytest.questions[i].correct<<"\n";
    }
}

void new_user(){
    system("CLS");
    cout<<"Enter your full name:\n";
    user newuser;
    newuser.id=int(users.size())+1;
    cin>>newuser.name>>newuser.surname;
    cout<<"Enter the username you want to use:\n";
    cin>>newuser.username;
    cout<<"Enter your password:\n";
    cin>>newuser.password;
    cout<<"Enter your age:\n";
    cin>>newuser.age;
    users.push_back(newuser);
    cout<<"You are now registered!Enter y to continue.\n";
    char response;
    cin>>response;
    if(response=='y'){
        system("CLS");
        mainpage();
    }
}

void load_data(){
    //opens the file questions to read data
    read_data.open("questions.txt");
    int number_tests,number_users;
    //get the number of tests
    read_data>>number_tests;
    for(int i=0;i<number_tests;i++){
        //for each test get the test by function and push it in the vector
        curriculum.push_back(get_test());
    }
    //close the file
    read_data.close();
    //open the file to read user data
    read_data.open("users.txt");
    //get the number of users
    read_data>>number_users;
    for(int i=0;i<number_users;i++){
        //for each user get the user and push it in the vector
        users.push_back(get_user());
    }
    //close the file
    read_data.close();
}

void saving_data(){
    //open file and overwrite it(sorting would create problems with appending)
    save_data.open("questions.txt");
    //write the number of tests by the method .size()
    save_data<<int(curriculum.size())<<"\n";
    for(int i=0;i<int(curriculum.size());i++){
        for(int j=0;j<20;j++){
            //for each question,for each of its 20 questions take information
            save_data<<curriculum[i].questions[j].id<<"\n"
            <<curriculum[i].questions[j].question<<"\n"
            <<curriculum[i].questions[j].answer_1<<"\n"
            <<curriculum[i].questions[j].answer_2<<"\n"
            <<curriculum[i].questions[j].correct<<"\n"
            <<curriculum[i].questions[j].user_answer<<"\n";
        }
        save_data<<curriculum[i].date_taken.day<<" "
        <<curriculum[i].date_taken.month<<" "
        <<curriculum[i].date_taken.year<<"\n";
    }
    //close the file
    save_data.close();
    //open the users file and overwrite it for the same reason as above
    save_data.open("users.txt");
    //write the number of users by using the method .size() of vectors
    save_data<<int(users.size())<<" ";
    for(int i=0;i<int(users.size());i++){
        //for each user provide their data
        save_data<<users[i].id<<" "
        <<users[i].name<<" "
        <<users[i].surname<<" "
        <<users[i].username<<" "
        <<users[i].password<<" "
        <<users[i].age<<"\n";
        save_data<<" "<<users[i].score<<" "
        <<users[i].total<<" "
        <<int(users[i].tests.size())<<"\n";
        for(int j=0;j<int(users[i].tests.size());j++){
            for(int k=0;k<20;k++){
                //for each test of the user,for each 20 question it has save it on the file
                save_data<<users[i].tests[j].questions[k].id<<"\n"
                <<users[i].tests[j].questions[k].question<<"\n"
                <<users[i].tests[j].questions[k].answer_1<<"\n"
                <<users[i].tests[j].questions[k].answer_2<<"\n"
                <<users[i].tests[j].questions[k].correct<<"\n"
                <<users[i].tests[j].questions[k].user_answer<<"\n";
            }
            save_data<<users[i].tests[j].date_taken.day<<" "
            <<users[i].tests[j].date_taken.month<<" "
            <<users[i].tests[j].date_taken.year<<"\n";
        }
    }
    save_data.close();
}

test get_test(){
    test newtest;
    int id,correct,user_answer;
    string white;
        for(int i=0;i<20;i++){
            //gets data for the test
            read_data>>id;
            newtest.questions[i].id=id;
            //this was something that annoyed me and apparently if you read something and then use getline? it gets nothing because it doesn't understand that the line is just a "\n" character. we can get this in this variable white and continue
            getline(read_data,white);
            getline(read_data,newtest.questions[i].question);
            getline(read_data,newtest.questions[i].answer_1);
            getline(read_data,newtest.questions[i].answer_2);
            read_data>>correct;
            newtest.questions[i].correct=correct;
            read_data>>user_answer;
            newtest.questions[i].user_answer=user_answer;

        }
    read_data>>newtest.date_taken.day
    >>newtest.date_taken.month
    >>newtest.date_taken.year;
    return newtest;
}

user get_user(){
    user newuser;
    //get all the data of a user
    int number_tests;
    read_data>>newuser.id
    >>newuser.name
    >>newuser.surname
    >>newuser.username
    >>newuser.password
    >>newuser.age;
    read_data>>newuser.score
    >>newuser.total
    >>number_tests;
    for(int i=0;i<number_tests;i++){
        //uses the function for each test the user has
        newuser.tests.push_back(get_test());
    }
    return newuser;
}

