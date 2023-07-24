#include "worker.h"
#include <iostream>
#include <string>
using namespace std;

class Boss : public Worker
{
public:
    Boss(int id, string name, int pid);
    void showInfo();
    string getDeptName();
};