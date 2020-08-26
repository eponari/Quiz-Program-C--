//enum used for switch cases for all types of users
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
