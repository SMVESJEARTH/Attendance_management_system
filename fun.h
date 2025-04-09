#ifndef FUN_H
#define FUN_H

#include"variable.h"

void Set_Cursor_And_Position(int x, int y);//改变光标位置
int Exit_with_Flag(int flag);//将输入值置为1以退出循环
void ClearLine(int line);//清除行
void Save(void);//数据保存

Employees *CreatAndRead_employees(int i);//创建链表与读取数据
void Init_company(void);//初始化公司数组
void Complete_job_num(void);//完成工号
Employees *LoginAndUi(void);//登录系统
void Staff_And_Ui(Employees *emp);// 员工功能
void Manager_And_Ui(Employees *emp); //部门经理功能
void Admin_And_Ui(Employees *emp);//管理员功能
void Select_clock(Employees *emp);//打卡选择
void Information_Inquiry_Individual(Employees *emp);//个人信息查询
void Information_Inquiry_Department(Employees *emp);//部门信息查询
void RequestVacation(Employees *emp); //假期申请
void Vacation_Management(Employees *emp);//请假申请管理
void ChangePassword(Employees *emp);//修改密码
void InputStaff(void);//添加员工
void DeleteStaff(void);//删除员工
void Modify_Seek(Companys com);//修改员工信息（寻找）
void Modify(Employees *emp);//修改员工信息（修改）
void Find_And_Print_BestEmployees(Employees *head); // 查找并打印所有最佳员工
Employees *createNewNode(Employees *originalNode); //创建新的链表节点，用来排序输出
Employees *getMiddle(Employees *head);// 找到链表的中间节点,返回需要的指针
Employees *mergeByClockTimes(Employees *left, Employees *right); // 归并两个链表，按打卡次数升序
Employees *mergeSortByClockTimes(Employees *head); // 归并排序，按打卡次数升序
Employees *mergeByMultipleAttributes(Employees *left, Employees *right); // 归并两个链表，如果请假次数相同，再按打卡次数排序
void ManagerSort(Employees *emp);//部门经理的排序函数
void Manager_Sorted_Print(Employees *head, const char *sortBy);//部门经理 打印排序后的信息
void AdminPrintSortedEmployees(const char *sortBy);//管理员 打印排序后的数据
void AdminSort(void);//管理员的排序函数
void Information_Management(Employees *emp);//信息管理
void Information_Management_1(Companys com);
void System_maintenance(void);//系统维护
void Annual_leave_allocation(void);//分配年假
void Stats(Employees *emp_m);//统计

#endif