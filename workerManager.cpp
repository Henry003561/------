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
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}
void WorkManager::del_emp()
{
    if (this->m_EmpNum == 0)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        int id = 0;
        cout << "请输入要删除的职工编号：";
        cin >> id;
        int index = isExist(id);
        if (index == -1)
        {
            cout << "该职工不存在" << endl;
        }
        else
        {
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;
            // 同步更新到文件
            this->save();
            cout << "用户删除成功" << endl;
        }
    }
    system("pause");
    system("cls");
}

void WorkManager::mod_emp()
{
    if (this->m_EmpNum == 0)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        int id = 0;
        cout << "请输入要修改的职工编号:";
        cin >> id;
        int index = this->isExist(id);
        if (index == -1)
        {
            cout << "该职工不存在" << endl;
        }
        else
        {
            delete this->m_EmpArray[index];
            int newId = 0;
            string name;
            int dSelect = 0;
            cout << "查到第" << id << "号职工，请输入职工号：";
            cin >> newId;
            cout << "请输入新姓名：";
            cin >> name;
            cout << "请输入新岗位" << endl;
            cout << "1-普通员工 2-经理 3-老板 ：";
            cin >> dSelect;
            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newId, name, 1);
                break;

            case 2:
                worker = new Manager(newId, name, 2);
                break;
            case 3:
                worker = new Boss(newId, name, 3);
                break;
            default:
                break;
            }
            this->m_EmpArray[index] = worker;
            cout << "第" << id << "号职工信息修改成功" << endl;
            this->save();
        }
    }
    system("pause");
    system("cls");
}

int WorkManager::isExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void WorkManager::find_emp()
{
    if (this->m_EmpNum == 0)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        int select = 0;
        cout << "请输入查找方式" << endl;
        cout << "1-按照编号查找 2-按照姓名查找 :";
        cin >> select;
        if (select == 1)
        {
            int id = 0;
            cout << "请输入要查找职工编号:";
            cin >> id;
            int index = this->isExist(id);
            if (index == -1)
            {
                cout << "该职工不存在" << endl;
            }
            else
            {
                cout << "查找成功,职工信息如下" << endl;
                this->m_EmpArray[index]->showInfo();
            }
        }
        if (select == 2)
        {
            string name;
            cout << "请输入要查找职工姓名：";
            cin >> name;
            bool flag = false;
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_name == name)
                {
                    flag = true;
                    cout << "查到此人，职工编号是" << this->m_EmpArray[i]->m_id
                         << "信息如下：" << endl;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (flag == false)
            {
                cout << "查无此人" << endl;
            }
        }
        else
        {
            cout << "输入有误" << endl;
        }
    }
    system("pause");
    system("cls");
}

void WorkManager::sort_emp()
{
    if (this->m_EmpNum == 0)
    {
        cout << "文件不存在或者记录为空" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        int select = 0;
        cout << "请输入排序方式" << endl;
        cout << "1-按职工编号进行升序  2-按职工编号进行降序 ：";
        cin >> select;
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int MinOrMax = i;
            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1)
                {
                    if (this->m_EmpArray[MinOrMax]->m_id > this->m_EmpArray[j]->m_id)
                    {
                        MinOrMax = j;
                    }
                }
                else
                {
                    if (this->m_EmpArray[MinOrMax]->m_id < this->m_EmpArray[j]->m_id)
                    {
                        MinOrMax = j;
                    }
                }
            }
            if (MinOrMax != i)
            {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[MinOrMax];
                this->m_EmpArray[MinOrMax] = temp;
            }
        }
        cout << "排序成功，排序后结果为:" << endl;
        this->save();
        this->show_Emp();
    }
}

void WorkManager::Clean_File()
{
    int select = 0;
    cout << "是否删除" << endl;
    cout << "1-确认 2-返回：";
    cin >> select;
    if (select == 1)
    {
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc);
        ofs.close();
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                    this->m_EmpArray[i] = NULL;
                }
            }
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FIleIsEmpt = true;
            cout << "清空成功" << endl;
        }
    }
    system("pause");
    system("cls");
}
WorkManager::~WorkManager()
{
    if (this->m_EmpArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if (this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
