#include<iostream>
#include<initializer_list>

#define finish return 0
#define loop(_variable,_start,_end,_step)   for(auto _variable = _start;_variable<_end;_variable+=_step)
#define NOT !
#define elif else if

using namespace std;

string endline = "\n";

void setEndl(string endlineString){
    endline = endlineString;
}

template <typename T>
void out(T t) 
{
    cout << t << endline;
}

template<typename T, typename... Args>
void out(T t, Args... args)
{
    cout << t <<" " ;

    out(args...) ;
}


template <typename T>
void in(T *t) 
{
    cin >> *t;
}

template<typename T, typename... Args>
void in(T *t, Args... args)
{
    cin >> *t;

    in(args...) ;
}