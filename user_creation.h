//used prototypes to tell the compiler these functions exist but it hasn't complied them yet
void mainpage();
void admin_page();

//function to get and push_back in a vector a new user that just registered
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
