#include "Boss.h"

Boss::Boss(int id, string name, int pid)
{
    this->m_id = id;
    this->m_name = name;
    this->m_pid = pid;
}

void Boss::showInfo()
{
    cout << "职工编号：" << this->m_id
         << "\t职工姓名：" << this->m_name
         << "\t职工岗位：" << this->getDeptName()
         << "\t岗位职责：给经理下达命令" << endl;
}

string Boss::getDeptName()
{
    return string("老板");
}