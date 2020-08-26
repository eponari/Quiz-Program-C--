#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
//all functions are in header files in order to get the functions
#include "structures.h"
#include "save_read_data.h"
#include "user_creation.h"
#include "authentication.h"
#include "admin_user_functions.h"
#include "panel_controls.h"


//the main function
int main()
{
    //loads databases
    load_data();
    //takes us to the main page where we can operate
    mainpage();
    //saves databases
    saving_data();
    return 0;
}

