
//prototype from another library that has a pointer parameter
void user_login(user* main_user);
//template,recursion,searching,parsing arrays in functions(2D arrays and dynamic arrays) and function overload examples (5 in one) :P
//to be honest couldn't find a good place to use them since most of my work is based in global variables but pointers could be used in every function when it came to users and admins
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
