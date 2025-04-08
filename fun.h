#ifndef FUN_H
#define FUN_H

#include"variable.h"

void ClearLine(int line);//清除行
void Save(void);//数据保存
Employees *CreatAndRead_employees(int i);//创建链表与读取数据
void Init_company(void);//初始化公司数组
void Complete_job_num(void);//完成工号
Employees * LoginAndUi(void);//登录系统
void Select_clock(Employees *emp);//打卡选择
void Information_Inquiry_Individual(Employees *emp);//个人信息查询
void Information_Inquiry_Department(Employees *emp);//部门信息查询
void Staff_And_Ui(Employees *emp);// 员工功能
void Vacation_Management(Employees *emp);//请假申请管理
void ChangePassword(Employees *emp);//修改密码函数
void RequestVacation(Employees *emp); //假期申请函数


void InputStaff(void);//添加员工
void DeleteStaff(void);//删除员工
void ModifyStaff(void);//修改员工信息
void ModifyMultipleFields(Employees *emp);//实现对员工多种信息修改的工具函数（辅助 modifyStaff函数实现其功能,modifyStaff函数已经包含该函数无需再次调用）
void Manager_And_Ui(Employees *emp); //部门经理功能
void Admin_And_Ui(Employees *emp);//管理员功能


#endif



