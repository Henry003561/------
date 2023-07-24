#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker
{
public:
    virtual void showInfo() = 0;
    virtual string getDeptName() = 0;


    int m_id;// 职工编号
    string m_name;
    int m_pid; // 部门编号
};