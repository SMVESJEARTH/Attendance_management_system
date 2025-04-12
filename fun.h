#ifndef FUN_H
#define FUN_H

#include"variable.h"

//1.系统相关2.员工3.部门经理4.管理员

//运行顺序
//Init_company -> CreatAndRead_employees -> Complete_job_num -> Annual_leave_allocation -> LoginAndUi
//                                                                                            /|\
//                                                                                           / | \
//                                                                                          /  |  \
//                                                                                         /   |   \
//                                                                                        /    |    \
//                                                                                       /     |     \
//                                                                                      /      |      \
//                                                                                     /       |       \
//                                                                                    /        |        \
//                                                                        Staff_And_Ui   Manager_And_Ui  Admin_And_Ui
//                                                                           |                 |               |
//                                                                        下属功能          下属功能            下属功能





//以下内容可根据缩进判断从属关系
// 
//系统相关：不被用户调用，而在程序运行过程中自动被调用，辅助进行系统的运行
void Init_company(void);//初始化公司数组 初始化部门人数 编号和名称
    Employees *CreatAndRead_employees(int i);//创建链表与读取数据 从文件读入职工信息，并根据读入信息的多少创建相应数目的链表节点
void Complete_job_num(void);//完成工号 根据姓名 部门 职位 以及在部门中的排序自动生成工号
void Annual_leave_allocation(void);//分配年假 
Employees *LoginAndUi(void);//登录系统 绘制登录界面并进行账号密码的正误判断
void Set_Cursor_And_Position(int x, int y);//改变光标位置 改变控制台中光标位置以改变输出位置
int Exit_with_Flag(int flag);//将输入值置为1以退出循环 检测有无字符按下 若有则将flag置为1并返回
void ClearLine(int line);//清除行 清除控制台中某一行输出
void Save(void);//数据保存 将所有职工信息按部门顺序保存到data文件中


//员工 员工登录系统后可使用的功能模块，主要涉及个人的日常操作，如打卡、请假和修改密码等。
void Staff_And_Ui(Employees *emp);// 员工功能 打印员工功能界面 并在switch中进行员工功能选择
    void RequestVacation(Employees *emp); //假期申请 可以请事假病假 也可取消假期申请

//部门经理 部门经理登录系统后可使用的功能模块，除了具备员工的部分功能外，还拥有部门管理相关的功能，如审批请假和部门信息排序等。
void Manager_And_Ui(Employees *emp); //部门经理功能 打印经理功能界面 并在switch中进行经理功能选择
    void Manger_Information_Inquiry_Department(Employees *emp);//部门信息查询
    void Vacation_Management(Employees *emp);//请假申请管理 根据员工请假类型选择是否准假
    void ManagerSort(Employees *emp);//部门经理的排序函数 信息排序 可根据打卡数，请假数进行排序，也可寻找最佳员工
        void Manager_Sorted_Print(Employees *head, const char *sortBy);//部门经理 打印排序后的信息

//管理员 管理员登录系统后可使用的功能模块，拥有最高权限，可对整个系统进行全面管理，包括系统维护、员工信息管理和数据排序等。
void Admin_And_Ui(Employees *emp);//管理员功能 打印管理员功能界面 并在switch中进行管理员功能选择
    void System_maintenance(void);//系统维护 将今日data文件根据日期进行重命名并保存，然后生成第二天要使用的data文件
    void Admin_Information_Inquiry_Department(void);//部门信息查询
    void Information_Management(Employees *emp);//信息管理 修改员工信息 添加员工 删除员工
        void Information_Management_1(Companys com);
            void Modify_Seek(Companys com);//修改员工信息（寻找）修改前查找待修改员工
                void Modify(Employees *emp);//修改员工信息（修改）信息修改
            void InputStaff(Companys com);//添加员工 
            void DeleteStaff(void);//删除员工

void AdminSort(void);//管理员的排序函数 信息排序 可根据打卡数，请假数进行排序，也可寻找最佳员工
    void AdminPrintSortedEmployees(Employees *head, const char *sortBy);//管理员 打印排序后的数据
    void Find_And_Print_BestEmployees(Employees *head); // 查找并打印所有最佳员工


//管理员功能的辅助函数
Employees *mergeSortByClockTimes(Employees *head); // 归并排序，按打卡次数升序
    Employees *createNewNode(Employees *originalNode); //创建新的链表节点，用来排序输出
    Employees *getMiddle(Employees *head);// 找到链表的中间节点,返回需要的指针
    Employees *mergeByClockTimes(Employees *left, Employees *right); // 归并两个链表，按打卡次数升序
    Employees *mergeByMultipleAttributes(Employees *left, Employees *right); // 归并两个链表，如果请假次数相同，再按打卡次数排序


//三种身份共用
void Select_clock(Employees *emp);//打卡选择
void Information_Inquiry_Individual(Employees *emp);//个人信息查询
void ChangePassword(Employees *emp);//修改密码 修改个人密码

//管理员 部门经理共用
void Find_And_Print_BestEmployees(Employees *head); // 查找并打印所有最佳员工
void Stats(Employees *emp_m);//信息统计

#endif