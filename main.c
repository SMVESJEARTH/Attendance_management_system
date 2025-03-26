#include"variable.h"
#include"fun.h"

Companys com[4];//四个部门
const char *departments[4] = { "Purchar","Produce" ,"Sale","Manage" };//四个部门名
const char *identities[3] = { "Admin","Manger","Staff" };//三个职位
const char time_of_start[5] = "0900";//规定上班时间
const char time_of_end[5] = "1630";//规定下班时间
const short vacation_of_less_10 = 5;//工龄小于10年的年假数
const short vacation_of_less_20 = 10;//工龄在10~20年的年假数
const short vacation_of_more_20 = 20;//工龄大于20年的年假数

int main()
{
	init_company(); 
	void complete_job_num();
	printf("数据导入完成\n");
	complete_job_num();
	printf("工号生成并导入完成\n");
	Sleep(1500);
	Main_UI();
	printf("1");
	return 0;
}
