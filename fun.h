#ifndef FUN_H
#define FUN_H

#include"variable.h"

void Save(void);//数据保存
Employees* CreatAndRead_employees(int i);//创建链表与读取数据
void init_company(void);//初始化公司数组

void complete_job_num(void);
void Main_UI(void);
void inputStaff(void);//添加员工
void deleteStaff(void);//删除员工
void modifyStaff(void);//修改员工信息
void modifyMultipleFields(Employees* emp);//实现对员工多种信息修改的工具函数（辅助 modifyStaff函数实现其功能,modifyStaff函数已经包含该函数无需再次调用）
void complete_job_num(void);//完成工号
Employees* LoginAndUi(void);//登录系统
void select_clock(Employees* emp);//打卡选择
void StaffAndUi(Employees* emp);//员工功能
void findStaff(Employees* emp);//普通职工信息查询
void modifyStaffCode(Employees* emp);//普通职工修改密码函数
void requestVacation(Employees* emp, int days); //假期申请函数
void ManagerAndUi(Employees* emp); //部门经理功能
void AdminAndUi(Employees* emp);//管理员功能
void approveVacation(Employees* emp);//批准职员的请假申请
void rejectVacation(Employees* emp);//拒绝职员的请假申请
#endif  


