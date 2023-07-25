#include <iostream>
#include <string>
using namespace std;
#include "workerManager.h"

int main()
{
    WorkManager wm;
    int choice = 0;
    while (true)
    {
        wm.showMenu();
        cout << "请输入你的选择：";
        cin >> choice;
        switch (choice)
        {
        case 0: // 退出系统
            system("cls");
            wm.QuitSystem();
            system("pause");
            break;
        case 1: // 添加职工
            wm.addEmp();
            break;
        case 2: // 显示职工
            wm.show_Emp();
            break;
        case 3: // 删除职工信息
            wm.del_emp();
            break;
        case 4: // 修改职工信息
            wm.mod_emp();
            break;
        case 5: // 查找职工信息
            wm.find_emp();
            break;
        case 6: // 按照编号排序
            wm.sort_emp();
            break;
        case 7: // 清空系统
            wm.Clean_File();
            break;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}