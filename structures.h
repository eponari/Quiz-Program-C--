
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
    //method of a structure
    bool is_correct(){
        return user_answer==correct;
    }
};

struct test{
    question questions[20];
    int score=0;
    date date_taken;
};

struct user{
    string name,surname,username,password;
    //default parameters when a user is created
    int id,score=0,total=0,age;
    vector <test> tests;
};
