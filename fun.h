#ifndef FUN_H
#define FUN_H

#include"variable.h"

void Set_Cursor_And_Position(int x, int y);//�ı���λ��
int Exit_with_Flag(int flag);//������ֵ��Ϊ1���˳�ѭ��
void ClearLine(int line);//�����
void Save(void);//���ݱ���

Employees* CreatAndRead_employees(int i);//�����������ȡ����
void Init_company(void);//��ʼ����˾����
void Complete_job_num(void);//��ɹ���
Employees* LoginAndUi(void);//��¼ϵͳ
void Staff_And_Ui(Employees* emp);// Ա������
void Manager_And_Ui(Employees* emp); //���ž�����
void Admin_And_Ui(Employees* emp);//����Ա����
void Select_clock(Employees* emp);//��ѡ��
void Information_Inquiry_Individual(Employees* emp);//������Ϣ��ѯ
void Information_Inquiry_Department(Employees* emp);//������Ϣ��ѯ
void RequestVacation(Employees* emp); //��������
void Vacation_Management(Employees* emp);//����������
void ChangePassword(Employees* emp);//�޸�����
void InputStaff(void);//���Ա��
void DeleteStaff(void);//ɾ��Ա��
void Modify_Seek(Companys com);//�޸�Ա����Ϣ��Ѱ�ң�
void Modify(Employees* emp);//�޸�Ա����Ϣ���޸ģ�
void Find_And_Print_BestEmployees(Employees* head); // ���Ҳ���ӡ�������Ա��
Employees* createNewNode(Employees* originalNode); //�����µ�����ڵ㣬�����������
Employees* getMiddle(Employees* head);// �ҵ�������м�ڵ�,������Ҫ��ָ��
Employees* mergeByClockTimes(Employees* left, Employees* right); // �鲢�����������򿨴�������
Employees* mergeSortByClockTimes(Employees* head); // �鲢���򣬰��򿨴�������
Employees* mergeByMultipleAttributes(Employees* left, Employees* right); // �鲢�������������ٴ�����ͬ���ٰ��򿨴�������
void ManagerSort(Employees* emp);//���ž����������
void Manager_Sorted_Print(Employees* head, const char* sortBy);//���ž��� ��ӡ��������Ϣ
void AdminPrintSortedEmployees(const char* sortBy);//����Ա ��ӡ����������
void AdminSort(void);//����Ա��������
void Information_Management(Employees* emp);//��Ϣ����
void Information_Management_1(Companys com);
void System_maintenance(void);//ϵͳά��
void Annual_leave_allocation(void);//�������
void Stats(Employees* emp_m);//ͳ��

#endif