#ifndef FUN_H
#define FUN_H

#include"variable.h"

Employees *CreatAndRead_employees(int i);//在每个公司数组中读取data.txt中的数据并创建链表存储员工数据
void init_company(void);//初始化公司数组
void complete_job_num(void);
void Main_UI(void);
void inputStaff(void);//添加员工
void deleteStaff(void);//删除员工
void modifyStaff(void);//修改员工信息
void modifyMultipleFields(Employees* emp);//实现对员工多种信息修改的工具函数（辅助 modifyStaff函数实现其功能,modifyStaff函数已经包含该函数无需再次调用）
#endif  