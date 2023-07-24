#include "Manager.h"

Manager::Manager(int id, string name, int pid)
{
    this->m_id = id;
    this->m_name = name;
    this->m_pid = pid;
}

void Manager::showInfo()
{
    cout << "职工编号：" << this->m_id
         << "\t职工姓名：" << this->m_name
         << "\t职工岗位：" << this->getDeptName()
         << "\t岗位职责：完成老板交给的任务" << endl;
}

string Manager::getDeptName()
{
    return string("经理");
}