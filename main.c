#include"variable.h"
#include"fun.h"

Companys com[4];//�ĸ�����
const char* departments[4] = { "Purchar","Produce" ,"Sale","Manage" };//�ĸ�������
const char* identities[3] = { "Admin","Manger","Staff" };//����ְλ
const char time_of_start_hour = 9;//�涨�ϰ�ʱ��
const char time_of_end_hour = 16;//�涨�°�ʱ��
const char time_of_end_min = 30;
const short vacation_of_less_10 = 5;//����С��10��������
const short vacation_of_less_20 = 10;//������10~20��������
const short vacation_of_more_20 = 20;//�������20��������
const short error_time = 1500;//������Ϣ��ʾʱ��
const short commmon_time = 2000;//��ͨ��Ϣ��ʾʱ��

int main()
{
	Employees* emp;
	Init_company();
	Complete_job_num();
	printf("����������\n");
	Annual_leave_allocation();//�������
	Save();
	Sleep(commmon_time);
	emp = LoginAndUi();
	switch (emp->id_identity)
	{
	case 1:Admin_And_Ui(emp); break;
	case 2:Manager_And_Ui(emp); break;
	case 3:Staff_And_Ui(emp); break;
	}
	return 0;
}
