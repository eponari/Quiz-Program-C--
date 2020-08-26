//create 2 streams in order to not confuse them and open as many files as we want
ifstream read_data;
ofstream save_data;

//used prototypes to tell the compiler these functions exist but it hasn't complied them yet
test get_test();
user get_user();
void load_data();
void saving_data();

//some databases we can use for users, admins and tests
//vectors are default structures that we get from libraries and with them come different default methods like .begin(),.end(),.size()
vector <test> curriculum;
vector <user> users;
string admins[3][2]={
    {"admin","admin"},
    {"administator","1234567890"},
    {"owner","ponari"}
};

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
