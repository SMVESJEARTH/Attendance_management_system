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

int main()
{
	Employees *emp;
	init_company(); 

	void complete_job_num();
	printf("数据导入完成\n");

	complete_job_num();
	printf("工号生成并导入完成\n");

	Sleep(1500);
	emp=LoginAndUi();

	switch (emp->job_num[4])
	{
		case '3':
			StaffAndUi(emp);
	}
	return 0;
}
