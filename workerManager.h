#pragma once
#include <iostream>
#include <string>
#include <fstream>
#define FILENAME "empFile.txt"
using namespace std;
#include "worker.h"

class WorkManager
{
public:
    WorkManager();
    void showMenu();
    void QuitSystem();
    int m_EmpNum;
    Worker **m_EmpArray;
    void addEmp();
    void save();
    ~WorkManager();
};