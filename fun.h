﻿#ifndef FUN_H
#define FUN_H

#include"variable.h"

Employees *CreatAndRead_employees(int i);//在每个公司数组中读取data.txt中的数据并创建链表存储员工数据
void init_company(void);//初始化公司数组
void complete_job_num(void);
void Main_UI(void);

#endif