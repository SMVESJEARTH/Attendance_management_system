#include"variable.h"
#include"fun.h"

Companies com[4];//四个部门
const char *departments[4] = { "Purchar","Produce" ,"Selling","Manage " };//四个部门名
const char *identities[3] = { "Admin","Manger","Staff" };//三个职位
const char time_of_start_hour = 9;//规定上班时间
const char time_of_end_hour = 16;//规定下班时间
const char time_of_end_min = 30;
const short vacation_of_less_10 = 5;//工龄小于10年的年假数
const short vacation_of_less_20 = 10;//工龄在10~20年的年假数
const short vacation_of_more_20 = 20;//工龄大于20年的年假数
const short error_time = 1500;//错误信息显示时间
const short commmon_time = 2000;//普通信息显示时间

int main()
{
	Employees *emp;
	Init_company(); 
	Complete_job_num();
	//printf("工号已生成\n");
	Annual_leave_allocation();//分配年假
	Save();
	//Sleep(commmon_time);
	emp = LoginAndUi();
	switch (emp->id_identity)
	{
		case 1:Admin_And_Ui(emp); break;
		case 2:Manager_And_Ui(emp); break;
		case 3:Staff_And_Ui(emp); break;
	}
	return 0;
}
