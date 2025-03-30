#include"variable.h"
#include"fun.h"

Companys com[4];//四个部门
const char *departments[4] = { "Purchar","Produce" ,"Sale","Manage" };//四个部门名
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

	void Complete_job_num();
	printf("-数据导入完成\n");

	Complete_job_num();
	printf("-工号已生成\n");
	Save();
	Sleep(commmon_time);

	emp=LoginAndUi();

	switch (emp->id_department)
	{
		case 3:StaffAndUi(emp);
	}
	return 0;
}
