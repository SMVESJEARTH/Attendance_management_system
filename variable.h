#ifndef VARIABLE_h
#define VARIABLE_h

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>
#include <time.h>
#include <conio.h>
#include<limits.h>

//MWL 1 1 20 1 1234  MWL1201 依据此格式产生20个数据，第一个数字为随机中文名，不超过四个字，第二个职位数据只能属于1至3，
// 第三个部门数据只能属于1至4，第四个工龄数据只能属于1到60，第五个状态数据只能为1，第六个数字密码为随机四位数，
// 第七个数据是工号(姓名+部门+职位+在部门里的序号)

struct Employees//雇员结构
{
	char name[4];//姓名
	char job_num[8];//工号
	char department[8];//所属部门
	int id_department;//所属部门编号
	char identity[7];//职位
	int id_identity;// 职位编号
	int age;//年龄
	short age_of_work;//工龄
	int stage;//工作状态 1为正常工作 0为假期中
	char password[5];//四位密码
	int Whether_clock;//是否打卡 1是 0否
	char time_of_clock[20];//打卡时间
	char time_of_leave[20];//离开时间
	int Whether_be_late;//是否迟到 1是 0否
	int num_late;//迟到数
	int num_clock;//打卡次数
	int num_ask_vacation;//请假次数
	int total_annual_vacation;//总年假
	int remaining_annual_vacation;//剩余年假
	int taken_vacation;//已用假期
	int ask_vacation_status; // 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝
	struct Employees *next;//员工类型指针
};
typedef struct Employees Employees;

struct Companys
{
	char order;//部门编号 格式为1 2 3 4
	char department[8];//部门名
	int num_of_staff;//部门各自员工数
	Employees* head;//员工类型指针
};
typedef struct Companys Companys;

//全局变量：
Companys com[4];//四个部门
const char* departments[4];//四个部门名
const char* identities[3];//三个不同职位
const char time_of_start_hour;//规定上班时间
const char time_of_end_hour;//规定下班时间
const char time_of_end_min;
const short vacation_of_less_10;//工龄小于10年的年假数
const short vacation_of_less_20;//工龄在10~20年的年假数
const short vacation_of_more_20;//工龄大于20年的年假数
const short error_time;//错误信息显示时间
const short commmon_time;//普通信息显示时间

#endif