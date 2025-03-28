#ifndef FUN_H
#define FUN_H

#include"variable.h"

void Save(void);//数据保存
Employees *CreatAndRead_employees(int i);//创建链表与读取数据
void init_company(void);//初始化公司数组
void complete_job_num(void);//完成工号
Employees * LoginAndUi(void);//登录系统
void select_clock(Employees *emp);//打卡选择
void StaffAndUi(Employees *emp);
#endif