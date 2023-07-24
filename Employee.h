#include "worker.h"
#include <iostream>
#include <string>
using namespace std;
class Employee:public Worker
{
public:
    Employee(int id, string name, int pid);
    void showInfo();
    string getDeptName();
};