#include "worker.h"
#include <iostream>
#include <string>
using namespace std;

class Manager : public Worker
{
public:
    Manager(int id, string name, int pid);
    void showInfo();
    string getDeptName();
};