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



struct Employees//��Ա�ṹ
{
	char name[4];//����
	char job_num[8];//����
	char department[8];//��������
	int id_department;//�������ű��
	char identity[7];//ְλ
	int id_identity;// ְλ���
	int age;//����
	short age_of_work;//����
	int stage;//����״̬ 1Ϊ�������� 0Ϊ������
	char password[5];//��λ����
	int Whether_clock;//�Ƿ�� 1�� 0��
	char time_of_clock[20];//��ʱ��
	char time_of_leave[20];//�뿪ʱ��
	int Whether_be_late;//�Ƿ�ٵ� 1�� 0��
	int num_late;//�ٵ���
	int num_clock;//�򿨴���
	int num_ask_vacation;//��ٴ���
	int total_annual_vacation;//�����
	int remaining_annual_vacation;//ʣ�����
	int taken_vacation;//���ü���
	int ask_vacation_status; // ���״̬��0 - δ���룬1 - �������������2 - ����׼��3 - �Ѿܾ�
	struct Employees* next;//Ա������ָ��
};
typedef struct Employees Employees;

struct Companys
{
	char order;//���ű�� ��ʽΪ1 2 3 4
	char department[8];//������
	int num_of_staff;//���Ÿ���Ա����
	Employees* head;//Ա������ָ��
};
typedef struct Companys Companys;

//ȫ�ֱ�����
Companys com[4];//�ĸ�����
const char* departments[4];//�ĸ�������
const char* identities[3];//������ְͬλ
const char time_of_start_hour;//�涨�ϰ�ʱ��
const char time_of_end_hour;//�涨�°�ʱ��
const char time_of_end_min;
const short vacation_of_less_10;//����С��10��������
const short vacation_of_less_20;//������10~20��������
const short vacation_of_more_20;//�������20��������
const short error_time;//������Ϣ��ʾʱ��
const short commmon_time;//��ͨ��Ϣ��ʾʱ��

#endif