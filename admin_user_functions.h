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



