#include "workerManager.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

void WorkManager::initEmp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int pid;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> pid)
    {
        Worker *worker = NULL;
        if (pid == 1)
        {
            worker = new Employee(id, name, pid);
        }
        else if (pid == 2)
        {
            worker = new Manager(id, name, pid);
        }
        else
        {
            worker = new Boss(id, name, pid);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}

WorkManager::WorkManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        // cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FIleIsEmpt = true;
        ifs.close();
        return;
    }
    // 文件存在，数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        // cout << "文件为空" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FIleIsEmpt = true;
        ifs.close();
        return;
    }
    // 文件存在，数据不为空
    int num = this->getEmpNum();
    cout << "职工人数：" << num << endl;
    this->m_EmpNum = num;

    // 开辟空间
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    this->initEmp();
}
void WorkManager::showMenu()
{
    cout << "****************************************" << endl;
    cout << "*********欢迎使用职工管理系统***********" << endl;
    cout << "*************0.退出管理系统*************" << endl;
    cout << "*************1.增加职工信息*************" << endl;
    cout << "*************2.显示职工信息*************" << endl;
    cout << "*************3.删除职工信息*************" << endl;
    cout << "*************4.修改职工信息*************" << endl;
    cout << "*************5.查找职工信息*************" << endl;
    cout << "*************6.按照编号排序*************" << endl;
    cout << "*************7.清空所有文档*************" << endl;
    cout << "****************************************" << endl;
    cout << endl;
}
void WorkManager::QuitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
void WorkManager::addEmp()
{
    cout << "请输入添加职工的数量:";
    int addNum;
    cin >> addNum;
    if (addNum > 0)
    {
        // 计算新添加空间的大小
        int newSpaceSize = this->m_EmpNum + addNum; // 新空间的大小 = 原来空间的大小+新添加员工的大小
        // 开辟新空间
        Worker **newSpace = new Worker *[newSpaceSize];
        if (m_EmpArray != NULL)
        {
            for (int i = 0; i < m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;
            cout << "请输入第" << i + 1 << "个职工编号：";
            cin >> id;
            cout << "请输入第" << i + 1 << "个职工姓名：";
            cin >> name;
            cout << "请输入第" << i + 1 << "个职工部门编号" << endl;
            cout << "1-普通员工 2-经理 3-老板 ：";
            cin >> dSelect;
            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = newSpace;
        this->m_EmpNum = newSpaceSize;
        this->m_FIleIsEmpt = false;
        this->save();
        cout << "成功添加" << addNum << "名职工" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "输入有误" << endl;
    }
}

void WorkManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_id << " " << this->m_EmpArray[i]->m_name << " " << this->m_EmpArray[i]->m_pid << endl;
    }
    ofs.close();
}

int WorkManager::getEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int pid;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> pid)
    {
        num++;
    }
    ifs.close();
    return num;
}
void WorkManager::show_Emp()
{
    if (this->m_EmpNum == 0)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        for(int i =0; i<this->m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo();
        }

    }
    system("pause");
    system("cls");
}

WorkManager::~WorkManager()
{
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
