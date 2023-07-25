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
    bool m_FIleIsEmpt; // 判断文件是否为空
    int getEmpNum();   // 统计文件中的人数
    void initEmp();
    void show_Emp();
    void del_emp();
    int isExist(int id);
    void mod_emp();
    void find_emp();
    void sort_emp();
    void Clean_File();
    ~WorkManager();
};