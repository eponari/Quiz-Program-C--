Project: “Check your Knowledge”

Epoka University 
Faculty of Architecture and Engineering 
CEN 110 - C PROGRAMMING / CEN A
Spring Semester 2019-2020
Student: Edison Ponari

Project idea:
You are a new user that wants to test your knowledge in math, physics, or programming. If you are not registered, you can register on the spot by providing some data 
about yourself. Each test has 20 questions with alternatives  with some bonus questions for comic relief XD. Once you take a test you can review the history of that 
test and learn from your mistake. Also, you can see your overall score and how many questions you have answered. Admins on the other hand can read everything from 
users and choose methods to review their data sorted in different methods. They can change questions and also see the progress of individual users.

My goals:

-create a user interface

-create a database from scratch and write and read from it

-create changeable tests that can be edited by users

-make the app scalable by dividing it into functions and then in header files

-use advanced techniques to organize my data (structures and files)

-making it possible for new users to use this app without having to find an account that already exists.

-have fun and collaborate in groups to exchange ideas and perspectives.

Requirements:

-Standard functions: functions of algorithms,fstream, vector, and iostream libraries

-2D Arrays and passing arrays to functions: created a 2D array in "save_read_data.h" to save admin usernames and passwords. 
Passed arrays in function in "authentication.h" at user_exist function to pass the admins 2D array and also to pass the user vector.

-Default parameters: multiple functions and also most structures in the project in case the user creates a new profile with 0 points and 0 tests in the memory.

-Templates and Function Overloading: to be honest I didn't find a lot of uses for this function in my project but I used it in searching users or admins. 
When you pass a vector it searches for users, when you pass a 2D array, it searches for an admin.

-Enumeration: Every switch case in "control_panel.h" has its enums to make the code readable even from people who aren't experienced in programming.

-Recursion: used it in the search algorithm with a base condition that the position doesn't pass the range of array and if you find what you are looking for just 
return that position. Else just recall yourself with position+1

-Pointers: those are used in the user interface most to display the data of a user from a function and also to modify its data.
Something that truly amazed me was the number of uses you could give to these pointers.

Problems:

-Hard to include everything that we have learned equally: The points distribution for this topic wasn't 100% fair. Topics like Templates and Function Overload 
are indeed a very good practice in programming, but in this project their use was hard to implement because you had to go out of your way to accomplish it.

-Data saving and low-level database implementation: Saving data was something that I hadn't done before and it took me a long time to get used to it. 
One little mistake? The compiler will save gibberish in your files and crush the whole thing. Very stressful to get ruined from a whitespace that getline took 
as a question and destroyed everything below.

-Implementing everything from scratch. This was a problem but I for sure enjoyed it. The problem is that is this project had a shorter deadline and was for an 
important client, it wouldn't be efficient enough time-wise.

-Scalability and time to fix something once my project got big: My original unfinished project was over 550 lines of code. One little change took my minutes to 
implement because it was hard to find where the function I wanted to change was and how that change would impact my whole all. Thanks to something you professor 
has repeated over 1000 times :P, I remembered that we can use header files to make a program more scaleable and also understandable. After 30 minutes of putting 
my functions to header files, I had over 100 errors. The problem? Functions would compile before the functions they depend on and nothing would get done. 
I fixed it with some prototype functions and everything worked out. Now at least if I want to add or delete something I know where to write this function and 
how to connect it without searching 600 lines of code.

Things I would do differently:

-Project planning: This project took around 8-9 days to finish. 2-3 hours per day and for the first 2 days I didn't do anything productive. On the third day I made 
a schematic view of what I wanted to do. Then every day I added something to that scheme. Most productive days turned out to be 3 days after 
I started to do real planning. After that the 3 last days were just me implementing ideas and cleaning up code.

-Use more libraries about databases: These libraries exist in C++ and I found a number of them. If I had like 3 months to do this project I would try to learn more 
about them but in 2 weeks you can't learn SQL databases, a new ideology of programming, and a library you haven't used, so I just saved and used data in the old 
fashion way.

-Use alternative technology: If somebody asked me to recreate this project in the summer for a job interview, I would most probably consider another programming 
language to use. The reason is their higher and the automation they provide. Python and C# would be perfect candidates for this project since I don't know anything 
about Java. Still my favorite programming language remains C++ but if I was asked to recreate this project in the least amount of time possible, I would choose Python 
because of its libraries and frameworks.
