/*
 * =====================================================================================
 *
 *       Filename:  sharedPtr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/03/2013 04:05:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jason.gs (), 
 *        Company:  Aliyun
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <unistd.h>
#include <tr1/memory>
#include <string>
#include <iostream>
using namespace std;

class Cat {
private:
    std::string name;

public:
    Cat(const std::string& n) {name = n;}
};

typedef std::tr1::shared_ptr<Cat> CatPtr;

int main() {
    CatPtr catPtr(new Cat("mimi"));
    CatPtr dogPtr = catPtr;
    dogPtr.reset();

    cout << "Test: reset child shared_ptr" << endl;
    if (catPtr.get() == NULL)
        cout << "catPtr is NULL when Child reset the point" << endl;
    else
        cout <<"CatPtr is still alive" << endl;

    cout << "Test: reset parent shared_ptr" << endl;
    CatPtr catPtr1(new Cat("kaka"));
    CatPtr dogPtr1 = catPtr1;
    catPtr1.reset();

    if (dogPtr1.get() == NULL)
        cout << "dogPtr1 is dead" << endl;
    else
        cout << "dogPtr1 is still alive" << endl;

    if (catPtr1.get() == NULL)
        cout << "catPtr1 is dead" << endl;
    else
        cout << "catPtr1 is still alive" << endl;
}
