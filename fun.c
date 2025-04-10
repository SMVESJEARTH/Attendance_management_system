#include"variable.h"
#include"fun.h"

void Set_Cursor_And_Position(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}

int Exit_with_Flag(int flag)
{
	while (1)
	{
		printf("�����˳�\n");
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			flag = 1;
		if (flag == 1)
			break;
	}
	return flag;
}

void ClearLine(int line)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	COORD coord;
	coord.X = 0;
	coord.Y = (SHORT)line;
	SetConsoleCursorPosition(hConsole, coord);

	DWORD written;
	FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, coord, &written);
	SetConsoleCursorPosition(hConsole, coord);
}

void Save(void)//���ݱ���
{
	char line[101] = { '\0' };

	FILE* newFile = fopen("temp.txt", "w");
	if (newFile == NULL)
	{
		printf("�޷�����ʱ�ļ�\n");
		Sleep(error_time);
		exit(1);
	}
	for (int i = 0; i < 4; i++)
	{
		Employees* emp = com[i].head;
		while (emp != NULL)
		{
			fprintf(newFile, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d %d %d\n",
				emp->name, emp->job_num, emp->id_department, emp->id_identity, emp->age, emp->age_of_work, emp->stage, emp->password, emp->Whether_clock,
				emp->time_of_clock, emp->time_of_leave, emp->Whether_be_late, emp->num_late, emp->num_clock, emp->num_ask_vacation, emp->total_annual_vacation, emp->taken_vacation,
				emp->remaining_annual_vacation, emp->ask_vacation_status);
			emp = emp->next;
		}
	}
	fclose(newFile);
	remove("data.txt");
	int useless = rename("temp.txt", "data.txt");
}

Employees* CreatAndRead_employees(int i)//�����������ȡ����
{
	char name[4] = { '\0' };//����
	char j_num[8] = { '\0' };//����
	int department_num = 0;//�������ű��
	int identity_num = 0;// ְλ���
	int age = 0;//����
	int age_w = 0;//����
	int stage = 0;//����״̬ 1Ϊ�������� 0Ϊ������
	char pass[5] = { '\0' };//��λ����
	int w_clock = 0;//�Ƿ�� 1�� 0��
	char tm_of_c[20] = { "1111111111111111" };//��ʱ��
	char tm_of_l[20] = { "1111111111111111" };//�뿪ʱ��
	int w_be_l = 0;//�Ƿ�ٵ�
	int n_be_l = 0;//�ٵ���
	int n_c = 0;//�򿨴���
	int n_a_v = 0;//��ٴ���
	int t_v = 0;//�����
	int h_v = 0;//�������
	int r_v = 0;//ʣ�����
	int a_v_s = 0;// ���״̬��0 - δ���룬1 - �������������2 - ����׼��3 - �Ѿܾ�

	Employees* head = NULL, * p1 = NULL, * p2 = NULL;
	FILE* fp = fopen("data.txt", "r");//ֻ����data.txt
	if (fp == NULL)
	{
		printf("�ļ�������");
		Sleep(error_time);
		exit(1);
	}

	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d %d %d",
		name, j_num, &department_num, &identity_num, &age, &age_w, &stage, pass,
		&w_clock, tm_of_c, tm_of_l, &w_be_l, &n_be_l, &n_c, &n_a_v, &t_v, &h_v, &r_v, &a_v_s) == 19)//ÿһ����19������ ����fscanf����ֵΪ19

	{
		if (department_num == i + 1)//�����еĲ���������0~3 ���ļ����ֶ�����Ĳ���������1~4���ʼ�1
		{
			p1 = (Employees*)malloc(sizeof(Employees));//�����ڴ�
			if (p1 == NULL)
			{
				fclose(fp); // �ڴ����ʧ�ܣ��ر��ļ�
				Sleep(error_time);
				exit(1);
			}

			//���ݶ���
			strcpy(p1->name, name);//����
			strcpy(p1->job_num, j_num);//����
			if (department_num >= 1 && department_num <= 4)//�������ű��
				strcpy(p1->department, departments[i]);
			p1->id_department = department_num;
			if (identity_num >= 1 && identity_num <= 3)//ְλ���
				strcpy(p1->identity, identities[identity_num - 1]);
			p1->id_identity = identity_num;
			p1->age = age;//����
			p1->age_of_work = age_w;//����
			p1->stage = stage; //����״̬
			strcpy(p1->password, pass);//��λ����
			p1->Whether_clock = w_clock;//�Ƿ��
			strcpy(p1->time_of_clock, tm_of_c);//��ʱ��
			strcpy(p1->time_of_leave, tm_of_l);//�뿪ʱ��
			p1->Whether_be_late = w_be_l;//�Ƿ�ٵ�
			p1->num_late = n_be_l;//�ٵ���
			p1->num_clock = n_c;//�򿨴���
			p1->num_ask_vacation = n_a_v;//��ٴ���
			p1->total_annual_vacation = t_v;//�����
			p1->taken_vacation = h_v;//���ü���
			p1->remaining_annual_vacation = r_v;//ʣ�����
			p1->ask_vacation_status = a_v_s;// ���״̬��0 - δ���룬1 - �������������2 - ����׼��3 - �Ѿܾ�


			if (head == NULL)
				head = p1;
			else
				p2->next = p1;
			p2 = p1;
			p2->next = NULL;
			com[i].num_of_staff++;//����Ա��������
		}
	}
	fclose(fp);
	return head;
}

void Init_company(void)//��ʼ����˾����
{
	for (int i = 0; i < 4; i++)
	{
		com[i].order = i + 1;
		strcpy(com[i].department, departments[i]);
		com[i].num_of_staff = 0;//��ʼ����������
		com[i].head = CreatAndRead_employees(i);//i��0~3����ͬ��˾����
	}
}

void Complete_job_num(void)//��ɹ���
{
	for (int i = 0; i < 4; i++)
	{
		Employees* emp = com[i].head;
		for (int j = 0; emp != NULL; j++)
		{
			strcpy(emp->job_num, emp->name);
			emp->job_num[3] = emp->id_department + '0';
			emp->job_num[4] = emp->id_identity + '0';
			if (j < 9)
			{
				emp->job_num[5] = '0';
				emp->job_num[6] = j + 1 + '0';
				emp->job_num[7] = '\0';
			}
			else
			{
				int temp = j + 1;
				emp->job_num[6] = temp % 10 + '0';
				temp = temp / 10;
				emp->job_num[5] = temp + '0';
				emp->job_num[7] = '\0';
			}
			emp = emp->next;
		}
	}

}

Employees* LoginAndUi(void)//��¼ϵͳ
{
	system("cls");
	char j_num[8] = { '\0' };
	char pass[6] = { '\0' };
	printf("���¼\n");
	printf("���ţ�");
	int temp = scanf("%s", j_num);
	temp = getchar();
	for (int j = 0; j < 3; j++)
	{
		printf("���룺");
		temp = scanf("%s", pass);
		temp = getchar();
		bool flag = 0;
		for (int i = 0; i < 4; i++)
		{
			Employees* emp = com[i].head;
			while (emp != NULL)
			{
				if (!strcmp(emp->job_num, j_num) && !strcmp(emp->password, pass))
				{
					printf("%s %s ��֤ͨ������ӭ��¼\n", emp->identity, emp->name);
					Sleep(commmon_time);
					return emp;
				}
				emp = emp->next;
			}
			if (flag == 1)
				break;
		}
		printf("�������,����������");
		Sleep(commmon_time);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord1 = { (SHORT)0, (SHORT)2 };
		SetConsoleCursorPosition(hConsole, coord1);
		printf("                     ");
		COORD coord2 = { (SHORT)0, (SHORT)3 };
		SetConsoleCursorPosition(hConsole, coord2);
		printf("                     ");
		COORD coord3 = { (SHORT)0, (SHORT)2 };
		SetConsoleCursorPosition(hConsole, coord3);
	}
	printf("�����������Σ�����ϵ����Ա�˶Թ��Ż�����\n");
	exit(1);
}

void Select_clock(Employees* emp)//��ѡ��
{
	int pick;
	system("cls");
	while (1)
	{
		printf("------------------------------\n");
		printf("|         1.�ϰ��          |\n");
		printf("|         2.�°��          |\n");
		printf("|         0.�˳���          |\n");
		printf("------------------------------\n");
		int flag = 0;
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1:
		{
			if (emp->Whether_clock == 1)
			{
				printf("�����Ѵ򿨣������ظ���");
				Sleep(commmon_time);
				system("cls");
				break;
			}
			time_t current_time = time(NULL);
			struct tm* local_tm;
			local_tm = localtime(&current_time);//��ʱ���תΪ����ʱ��
			if (emp->Whether_clock != 1 && local_tm->tm_hour > 6)
			{
				emp->Whether_clock = 1;
				printf("�򿨳ɹ�\n");

				printf("��ʱ�䣺%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
					local_tm->tm_hour, local_tm->tm_min);

				int temp = sprintf(emp->time_of_clock, "%d-%02d-%02d.%d:%02d",
					local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday, local_tm->tm_hour, local_tm->tm_min);

				if (local_tm->tm_hour < time_of_start_hour)
				{
					emp->Whether_be_late = 0;
					printf("δ�ٵ�\n");
				}
				else
				{
					emp->Whether_be_late = 1;
					emp->num_late++;
					printf("�ѳٵ�\n");
				}
				Sleep(commmon_time);
				system("cls");
			}
			else if (local_tm->tm_hour < 6)
			{
				printf("δ����ʱ��(6:00),��ʧ��\n");
				Sleep(commmon_time);
				system("cls");
			}
		}break;

		case 2:
		{
			if (emp->Whether_clock == 1)
			{
				time_t current_time = time(NULL);
				struct tm* local_tm;
				local_tm = localtime(&current_time);
				printf("�°�ʱ�䣺%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
					local_tm->tm_hour, local_tm->tm_min);

				int temp = sprintf(emp->time_of_leave, "%d-%02d-%02d.%d:%02d",
					local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday, local_tm->tm_hour, local_tm->tm_min);

				Sleep(commmon_time);
				system("cls");
			}
			else
			{
				printf("���ջ�δ�ϰ��");
				Sleep(commmon_time);
				system("cls");
			}
		}break;

		case 0:	system("cls"); flag = 1; Save(); break;

		}
		if (flag == 1)
			break;
	}
}

void Information_Inquiry_Individual(Employees* emp)//��Ϣ��ѯ
{
	int flag = 1;
	system("cls");

	FILE* fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("�޷���data�ļ�\n");
		Sleep(error_time);
		exit(1);
	}

	char name[4] = { '\0' };//����
	char j_num[8] = { '\0' };//����
	int department_num = 0;//�������ű��
	int identity_num = 0;// ְλ���
	int age = 0;//����
	int age_w = 0;//����
	int stage = 0;//����״̬ 1Ϊ�������� 0Ϊ������
	char pass[5] = { '\0' };//��λ����
	int w_clock = 0;//�Ƿ�� 1�� 0��
	char tm_of_c[20] = { '\0' };//��ʱ��
	char tm_of_l[20] = { '\0' };//�뿪ʱ��
	int w_be_l = 0;//�Ƿ�ٵ�
	int n_be_l = 0;//�ٵ���
	int n_c = 0;//�򿨴���
	int n_a_v = 0;//��ٴ���
	int t_v = 0;//�����
	int h_v = 0;//�������
	int r_v = 0;//ʣ�����
	int a_v_s = 0;// ���״̬��0 - δ���룬1 - �������������2 - ����׼��3 - �Ѿܾ�

	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d %d %d",
		name, j_num, &department_num, &identity_num, &age, &age_w, &stage, pass,
		&w_clock, tm_of_c, tm_of_l, &w_be_l, &n_be_l, &n_c, &n_a_v, &t_v, &h_v, &r_v, &a_v_s) == 19)
	{
		if (strcmp(emp->job_num, j_num) == 0)
			break;
	}

	while (1)
	{
		printf("����Ϊ%s�ĸ�����Ϣ:\n", emp->name);
		printf("������%s\n", name);
		printf("���ţ�%s\n", j_num);
		printf("���ţ�%s\n", departments[department_num - 1]);
		printf("ְ��%s\n", identities[identity_num - 1]);
		printf("���䣺%d\n", age);
		printf("���䣺%d\n", age_w);
		printf("���룺****\n");
		printf("����״̬��");
		if (stage)
			printf("������...\n");
		else
			printf("�ݼ���\n");
		printf("�Ƿ�򿨣�");
		if (w_clock)
			printf("�Ѵ�...\n");
		else
			printf("δ��O.o\n");

		if (strcmp(tm_of_c, "1111111111111111") == 0)
			printf("�ϰ�ʱ�䣺��δ�����ϰ��\n");
		else
			printf("��ʱ�䣺%s\n", tm_of_c);

		if (strcmp(tm_of_l, "1111111111111111") == 0)
			printf("�°�ʱ�䣺��δ�����°��\n");
		else
			printf("�°�ʱ�䣺%s\n", tm_of_l);
		printf("�Ƿ�ٵ���");
		if (w_be_l)
			printf("�ѳٵ����n��\n");
		else
			printf("δ�ٵ�\n");
		printf("�ٵ�����%d\n", n_be_l);
		printf("������%d\n", n_c);
		printf("�������%d\n", n_a_v);
		printf("����٣�%d\n", t_v);
		printf("������٣�%d\n", h_v);
		printf("ʣ����٣�%d\n", r_v);
		printf("���״̬��%d\n", a_v_s);
		printf("--����'p'��ʾ����--\n");
		printf("--����0�˳�--\n");
		while (1)
		{
			while (!_kbhit());
			char ch = _getch();
			if (ch == 'p')
			{
				ClearLine(7);
				printf("���룺%s", pass);
				Sleep(commmon_time);
				ClearLine(7);
				printf("���룺****");
			}
			else if (ch - '0' == 0)
				flag = 0;
			if (flag == 0)
				break;
		}
		if (flag == 0)
		{
			system("cls");
			break;
		}
	}

}

void Information_Inquiry_Department(Employees* emp)
{
	Employees* emp_s;
	int pick = -1, flag = 0;

	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.���Ų�ѯ          |\n");
		printf("|         2.������ѯ          |\n");
		printf("|         3.ְλ��ѯ          |\n");
		printf("|         4.�����ѯ          |\n");
		printf("|         5.״̬��ѯ          |\n");
		printf("|         0.�˳���ѯ          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		temp = getchar();
		switch (pick)
		{
		case 1:
		{
			emp_s = com[emp->id_department - 1].head;
			int flag = 0, judge = 0;
			system("cls");
			printf("������Ҫ��ѯ�Ĺ��ţ�");
			char j_num[8] = { '\0' };//����
			int temp = scanf("%s", j_num);
			while (emp_s != NULL)
			{
				if (strcmp(emp_s->job_num, j_num) == 0)
				{
					judge = 1;
					break;
				}
				emp_s = emp_s->next;
			}
			if (judge == 1)
			{
				system("cls");
				printf("��Ϣ����:\n");
				printf("������%s\n", emp_s->name);
				printf("���ţ�%s\n", j_num);
				printf("���ţ�%s\n", departments[emp_s->id_department - 1]);
				printf("ְ��%s\n", identities[emp_s->id_identity - 1]);
				printf("���䣺%d\n", emp_s->age);
				printf("���䣺%d\n", emp_s->age_of_work);
				printf("����״̬��");
				if (emp_s->stage)
					printf("������...\n");
				else
					printf("�ݼ���\n");
				printf("�Ƿ�򿨣�");
				if (emp_s->Whether_clock)
					printf("�Ѵ�...\n");
				else
					printf("δ��O.o\n");

				if (strcmp(emp_s->time_of_clock, "1111111111111111") == 0)
					printf("�ϰ�ʱ�䣺��δ�����ϰ��\n");
				else
					printf("��ʱ�䣺%s\n", emp_s->time_of_clock);

				if (strcmp(emp_s->time_of_leave, "1111111111111111") == 0)
					printf("�°�ʱ�䣺��δ�����°��\n");
				else
					printf("�°�ʱ�䣺%s\n", emp_s->time_of_leave);
				printf("�Ƿ�ٵ���");
				if (emp_s->Whether_be_late)
					printf("�ѳٵ����n��\n");
				else
					printf("δ�ٵ�\n");
				printf("�ٵ�����%d\n", emp_s->num_late);
				printf("������%d\n", emp_s->num_clock);
				printf("�������%d\n", emp_s->num_ask_vacation);
				printf("����٣�%d\n", emp_s->total_annual_vacation);
				printf("������٣�%d\n", emp_s->taken_vacation);
				printf("ʣ����٣�%d\n", emp_s->remaining_annual_vacation);
				printf("���״̬��%d\n", emp_s->ask_vacation_status);
				printf("--����0�˳�--\n");
				flag = Exit_with_Flag(flag);
			}
			else
			{
				printf("���޴���\n");
				Sleep(commmon_time);
				system("cls");
			}
		}break;
		case 2:
		{
			emp_s = com[emp->id_department - 1].head;
			int flag = 0, judge = 0;
			system("cls");
			printf("������Ҫ��ѯ��������");
			char name[5] = { '\0' };//����
			int temp = scanf("%s", name);
			printf("------------------------------\n");
			while (emp_s != NULL)
			{
				if (strcmp(emp_s->name, name) == 0)
				{
					judge = 1;
					printf("���ţ�%s\n", emp_s->job_num);
					printf("ְλ��%s\n", emp_s->identity);
					printf("���䣺%d\n", emp_s->age);
					printf("״̬��%d\n", emp_s->stage);
					printf("------------------------------\n");
				}
				emp_s = emp_s->next;
			}
			if (judge == 0)
				printf("���޴���\n");
			flag = Exit_with_Flag(flag);
		}break;
		case 3:
		{
			emp_s = com[emp->id_department - 1].head;
			int flag = 0, judge = 0;
			system("cls");
			printf("������Ҫ��ѯ��ְλ��ţ�");
			int identity_num = 0;// ְλ���
			int temp = scanf("%d", &identity_num);
			printf("------------------------------\n");
			while (emp_s != NULL)
			{
				if (emp_s->id_identity == identity_num)
				{
					judge = 1;
					printf("������%s\n", emp_s->job_num);
					printf("���ţ�%s\n", emp_s->job_num);
					printf("���䣺%d\n", emp_s->age);
					printf("״̬��%d\n", emp_s->stage);
					printf("------------------------------\n");
				}
				emp_s = emp_s->next;
			}
			if (judge == 0)
				printf("���޴���\n");
			flag = Exit_with_Flag(flag);
		}break;
		case 4:
		{
			emp_s = com[emp->id_department - 1].head;
			int flag = 0, judge = 0;
			system("cls");
			printf("������Ҫ��ѯ�����䣺");
			int age = 0;//����
			int temp = scanf("%d", &age);
			printf("------------------------------\n");
			while (emp_s != NULL)
			{
				if (emp_s->age == age)
				{
					judge = 1;
					printf("������%s\n", emp_s->job_num);
					printf("���ţ�%s\n", emp_s->job_num);
					printf("ְλ��%s\n", emp_s->identity);
					printf("״̬��%d\n", emp_s->stage);
					printf("------------------------------\n");
				}
				emp_s = emp_s->next;
			}
			if (judge == 0)
				printf("���޴���\n");
			flag = Exit_with_Flag(flag);
		}break;
		case 5:
		{
			emp_s = com[emp->id_department - 1].head;
			int flag = 0, judge = 0;
			system("cls");
			printf("������Ҫ��ѯ�Ĺ���״̬��");
			int stage = 0;//����״̬ 1Ϊ�������� 0Ϊ������
			int temp = scanf("%d", &stage);
			printf("------------------------------\n");
			while (emp_s != NULL)
			{
				if (emp_s->stage == stage)
				{
					judge = 1;
					printf("������%s\n", emp_s->job_num);
					printf("���ţ�%s\n", emp_s->job_num);
					printf("ְλ��%s\n", emp_s->identity);
					printf("���䣺%d\n", emp_s->age);
					printf("------------------------------\n");
				}
				emp_s = emp_s->next;
			}
			if (judge == 0)
				printf("���޴���\n");
			flag = Exit_with_Flag(flag);
		}break;
		case 0:flag = 1; printf("�˳���¼�ɹ�\n"); Sleep(commmon_time); system("cls"); break;
		}
		if (flag == 1)
			break;
	}
}

void Staff_And_Ui(Employees* emp)//Ա������
{
	system("cls");
	int pick = 0;
	int flag = 0;
	while (1)
	{
		if (flag == 1)
			break;
		printf("------------------------------\n");
		printf("|         1.��ѡ��          |\n");
		printf("|         2.��Ϣ��ѯ          |\n");
		printf("|         3.���ϵͳ          |\n");
		printf("|         4.�޸�����          |\n");
		printf("|         0.�˳���¼          |\n");

		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1:Select_clock(emp); break;
		case 2:Information_Inquiry_Individual(emp); break;
		case 3: RequestVacation(emp); break;
		case 4:ChangePassword(emp); break;
		case 0:flag = 1; printf("�˳���¼�ɹ�\n"); Sleep(commmon_time); system("cls"); ; Save(); break;


		}
	}
}

void Manager_And_Ui(Employees* emp) //���ž�����
{
	system("cls");
	int pick = 0;
	int flag = 0;
	int days = 0;
	while (1)
	{
		printf("-------------------------------\n");
		printf("|         1.��ѡ��          |\n");
		printf("|         2.���˲�ѯ          |\n");
		printf("|         3.���Ų�ѯ          |\n");
		printf("|         4.��Ϣ����          |\n");
		printf("|         5.�������          |\n");
		printf("|         6.��Ϣͳ��          |\n");
		printf("|         7.�޸�����          |\n");
		printf("|         0.�˳���¼          |\n");
		printf("-------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1: Select_clock(emp); break;
		case 2: Information_Inquiry_Individual(emp); break;
		case 3: Information_Inquiry_Department(emp); break;
		case 4: ManagerSort(emp); break;
		case 5: Vacation_Management(emp); break;
		case 6: Stats(emp); break;
		case 7: ChangePassword(emp); break;
		case 0:flag = 1; printf("�˳���¼�ɹ�\n"); Sleep(commmon_time); system("cls"); Save(); break;
		}
		if (flag == 1)
			break;
	}
}

void Admin_And_Ui(Employees* emp)//����Ա����
{

	int flag = 0, pick = 0;
	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.ϵͳά��          |\n");
		printf("|         2.��ѡ��          |\n");
		printf("|         3.���˲�ѯ          |\n");
		printf("|         4.���Ų�ѯ          |\n");
		printf("|         5.��Ϣ����          |\n");
		printf("|         6.��Ϣ����          |\n");
		printf("|         7.�޸�����          |\n");
		printf("|         0.�˳���¼          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1:  System_maintenance(); break;
		case 2: Select_clock(emp); break;
		case 3: Information_Inquiry_Individual(emp); break;
		case 4: Information_Inquiry_Department(emp); break;
		case 5: AdminSort(); break;
		case 6: Information_Management(emp); break;
		case 7: ChangePassword(emp); break;
		case 0:flag = 1; printf("�˳���¼�ɹ�\n"); Sleep(commmon_time); system("cls"); Save(); break;
		}
		if (flag == 1)
			break;
	}
}

void InputStaff() //���Ա��
{
	system("cls");
	int flag = 1;
	while (1)
	{
		char name[4] = { '\0' };//����
		char j_num[8] = { '\0' };//����
		int department_num = 0;//�������ű��
		int identity_num = 0;// ְλ���
		int age = 0;//����
		int age_w = 0;//����
		int stage = 0;//����״̬ 1Ϊ�������� 0Ϊ������
		char pass[5] = { '\0' };//��λ����
		int w_clock = 0;//�Ƿ�� 1�� 0��
		int w_be_l = 0;//�Ƿ�ٵ�
		int n_be_l = 0;//�ٵ���
		int n_c = 0;//�򿨴���
		int n_a_v = 0;//��ٴ���
		int t_v = 0;//�����
		int r_v = 0;//ʣ�����
		int h_v = 0;//���ü���
		int a_v_s = 0;// ���״̬��0 - δ���룬1 - �������������2 - ����׼��3 - �Ѿܾ�
		int temp;

		printf("������Ա����Ϣ\n");
		while (1)
		{
			printf("������������3���ַ�����");
			temp = scanf("%s", name);
			if (strlen(name) != 3 || name[0] < 'A' || name[0]>'Z' || name[1] < 'A' || name[1]>'Z' || name[2] < 'A' || name[2]>'Z')
			{
				printf("������Ч �밴1���������0�˳�\n");
			}
			else
				break;
			while (!_kbhit());
			char ch = _getch();
			if (ch - '0' == 0)
				flag = 0;
			if (flag == 0)
				break;
			if (ch - '0' == 1)
			{
				ClearLine(2);
				ClearLine(3);
			}
		}
		if (flag == 0)
			break;
		while (1)
		{
			printf("���ű�ţ�1-Purchase, 2-Produce, 3-Sale, 4-Manage����");
			temp = scanf("%d", &department_num);
			if (department_num < 1 || department_num > 4)
			{
				printf("���ű����Ч �밴1���������0�˳�\n");
			}
			else
				break;
			while (!_kbhit());
			char ch = _getch();
			if (ch - '0' == 0)
				flag = 0;
			if (flag == 0)
				break;
			if (ch - '0' == 1)
			{
				ClearLine(3);
				ClearLine(4);
			}
		}
		if (flag == 0)
			break;
		while (1)
		{
			printf("ְλ��ţ�1-Admin, 2-Manager, 3-Staff����");
			temp = scanf("%d", &identity_num);
			if (identity_num < 1 || identity_num > 3)
			{
				printf("ְλ�����Ч �밴1���������0�˳�\n");
			}
			else
				break;
			while (!_kbhit());
			char ch = _getch();
			if (ch - '0' == 0)
				flag = 0;
			if (flag == 0)
				break;
			if (ch - '0' == 1)
			{
				ClearLine(4);
				ClearLine(5);
			}
		}
		if (flag == 0)
			break;
		while (1)
		{
			printf("���䣺");
			temp = scanf("%d", &age);
			if (age < 18 || age > 60)
			{
				printf("������Ч �밴1���������0�˳�\n");
			}
			else
				break;
			while (!_kbhit());
			char ch = _getch();
			if (ch - '0' == 0)
				flag = 0;
			if (flag == 0)
				break;
			if (ch - '0' == 1)
			{
				ClearLine(5);
				ClearLine(6);
			}
		}
		if (flag == 0)
			break;
		// ������Ա���ڵ�
		Employees* newEmp = (Employees*)malloc(sizeof(Employees));
		if (newEmp == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			exit(1);
		}

		// ����Ա����Ϣ
		strcpy(newEmp->name, name);
		strcpy(newEmp->department, departments[department_num - 1]);
		newEmp->id_department = department_num;
		strcpy(newEmp->identity, identities[identity_num - 1]);
		newEmp->id_identity = identity_num;
		newEmp->age = age;
		newEmp->age_of_work = age_w;
		newEmp->stage = stage;
		strcpy(newEmp->password, pass);
		newEmp->Whether_clock = w_clock;
		newEmp->Whether_be_late = w_be_l;
		newEmp->num_late = n_be_l;
		newEmp->num_clock = n_c;
		newEmp->num_ask_vacation = n_a_v;
		newEmp->total_annual_vacation = t_v;
		newEmp->taken_vacation = h_v;
		newEmp->remaining_annual_vacation = r_v;
		newEmp->ask_vacation_status = a_v_s;

		newEmp->next = NULL;

		// ���뵽��Ӧ���ŵ�������
		Employees* move = com[department_num - 1].head;

		// �������Ϊ�գ�ֱ�ӽ��½ڵ���Ϊͷ�ڵ�
		if (move == NULL)
		{
			com[department_num - 1].head = newEmp;
		}
		else
		{
			// �����������½ڵ���뵽����ĩβ
			while (move->next != NULL)
			{
				move = move->next;
			}
			move->next = newEmp;
		}

		// ���²���Ա����
		com[department_num - 1].num_of_staff++;

		printf("Ա����Ϣ�ѳɹ���ӵ����� %s\n", departments[department_num - 1]);
		Complete_job_num();
		Save();
		flag = 0;
		if (flag = 0)
		{
			system("cls");
			break;
		}
	}
	Save();
}

void DeleteStaff() // ɾ��Ա��
{
	system("cls");
	char j_num[8] = { '\0' };
	printf("������Ҫɾ����Ա���Ĺ���: ");
	int temp = scanf("%s", j_num);

	int found = 0; // ����Ƿ��ҵ�Ա��
	for (int i = 0; i < 4; i++) // �������в���
	{
		Employees* prev = NULL; // ǰ���ڵ�
		Employees* curr = com[i].head; // ��ǰ�ڵ�

		while (curr != NULL) // ������ǰ���ŵ�Ա������
		{
			if (strcmp(curr->job_num, j_num) == 0) // �ҵ�ƥ���Ա��
			{
				found = 1; // ����ҵ�Ա��
				if (prev == NULL) // ���Ҫɾ����Ա��������ͷ�ڵ�
				{
					com[i].head = curr->next; // ��������ͷΪ��һ���ڵ�
				}
				else // ���Ҫɾ����Ա����������ͷ�ڵ�
				{
					prev->next = curr->next; // ��ǰ���ڵ��nextָ��ǰ�ڵ����һ���ڵ�
				}
				free(curr); // �ͷŵ�ǰ�ڵ��ڴ�
				com[i].num_of_staff--; // ����Ա��������1
				printf("Ա������Ϊ %s �������ѳɹ�ɾ����\n", j_num);
				break; // �ҵ���ɾ�����˳�ѭ��
			}
			prev = curr; // ����ǰ���ڵ�
			curr = curr->next; // �ƶ�����һ���ڵ�
		}
		if (found) // ������ҵ���ɾ��Ա�����˳�����ѭ��
		{
			break;
		}
	}

	if (!found) // ������������в�����δ�ҵ�Ա��
	{
		printf("δ�ҵ�����Ϊ %s ��Ա�����ݡ�\n", j_num);
	}
	Save();
}

void Modify_Seek(Companys com) // �޸�Ա����Ϣ
{
	system("cls");
	char j_num[8] = { '\0' };
	int find = 0;
	printf("������Ҫ�޸ĵ�Ա�����ţ�");
	int temp = scanf("%s", j_num);
	temp = getchar();
	Employees* emp = com.head;
	while (emp != NULL)
	{
		if (strcmp(emp->job_num, j_num) == 0)
		{
			find = 1;
			break;
		}
		emp = emp->next;
	}
	if (find == 0)
		printf("���޴���");
	else
		Modify(emp);
}

void Modify(Employees* emp)//�޸�Ա����Ϣ���޸ģ�
{
	system("cls");
	char name[4] = { '\0' };//����
	char j_num[8] = { '\0' };//����
	int department_num = 0;//�������ű��
	int identity_num = 0;// ְλ���
	int age = 0;//����
	int age_w = 0;//����
	int stage = 0;//����״̬ 1Ϊ�������� 0Ϊ������
	char pass[5] = { '\0' };//��λ����
	int w_clock = 0;//�Ƿ�� 1�� 0��
	int w_be_l = 0;//�Ƿ�ٵ�
	int n_be_l = 0;//�ٵ���
	int n_c = 0;//�򿨴���
	int n_a_v = 0;//��ٴ���
	int t_v = 0;//�����
	int r_v = 0;//ʣ�����
	int h_v = 0;//���ü���
	int a_v_s = 0;// ���״̬��0 - δ���룬1 - �������������2 - ����׼��3 - �Ѿܾ�

	printf("������%s\n", emp->name);
	printf("���ţ�%s\n", emp->job_num);
	printf("���ţ�%s\n", emp->department);
	printf("ְλ��%s\n", emp->identity);
	printf("���䣺%d\n", emp->age);
	printf("���䣺%d\n", emp->age_of_work);
	printf("����״̬��%d\n", emp->stage);
	printf("���룺%s\n", emp->password);
	printf("�Ƿ�򿨣�%d\n", emp->Whether_clock);
	printf("�Ƿ�ٵ���%d\n", emp->Whether_be_late);
	printf("�ٵ�������%d\n", emp->num_late);
	printf("�򿨴�����%d\n", emp->num_clock);
	printf("��ٴ�����%d\n", emp->num_ask_vacation);
	printf("����٣�%d\n", emp->total_annual_vacation);
	printf("ʣ����٣�%d\n", emp->remaining_annual_vacation);
	printf("���ü��ڣ�%d\n", emp->taken_vacation);
	printf("���״̬��%d\n", emp->ask_vacation_status);

	Set_Cursor_And_Position(25, 0);
	printf("���Ҫ�޸ĵ�ǰ����Ϣ�밴��1�������밴��0");

	Set_Cursor_And_Position(25, 1);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 1);
			int temp = scanf("%s", name);
			temp = getchar();
		}
		if (strlen(name) != 3 || name[0] < 'A' || name[0]>'Z' || name[1] < 'A' || name[1]>'Z' || name[2] < 'A' || name[2]>'Z')
		{
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 1);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 2);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 2);
			int temp = scanf("%s", j_num);
			temp = getchar();
		}
		if (strlen(name) != 3 || name[0] < 'A' || name[0]>'Z' || name[1] < 'A' || name[1]>'Z' || name[2] < 'A' || name[2]>'Z')
		{
			Set_Cursor_And_Position(25, 1);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 1);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 1);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 3);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 3);
			int temp = scanf("%d", &department_num);
			temp = getchar();
		}
		if (department_num < 1 || department_num>4)
		{
			Set_Cursor_And_Position(25, 2);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 2);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 2);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 4);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 4);
			int temp = scanf("%d", &identity_num);
			temp = getchar();
		}
		if (identity_num < 1 || identity_num>3)
		{
			Set_Cursor_And_Position(25, 3);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 3);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 3);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 5);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 5);
			int temp = scanf("%d", &age);
			temp = getchar();
		}
		if (age < 18 || age>60)
		{
			Set_Cursor_And_Position(25, 4);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 4);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 4);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 6);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 6);
			int temp = scanf("%d", &age_w);
			temp = getchar();
		}
		if (age_w < 0)
		{
			Set_Cursor_And_Position(25, 5);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 5);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 5);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 7);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 7);
			int temp = scanf("%d", &stage);
			temp = getchar();
		}
		if (stage < 0 || stage > 1)
		{
			Set_Cursor_And_Position(25, 6);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 6);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 6);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 8);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 8);
			int temp = scanf("%s", pass);
			temp = getchar();
		}
		if (strlen(pass) != 4)
		{
			Set_Cursor_And_Position(25, 7);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 7);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 7);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 9);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 9);
			int temp = scanf("%d", &w_clock);
			temp = getchar();
		}
		if (w_clock < 0 || w_clock >1)
		{
			Set_Cursor_And_Position(25, 8);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 8);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 8);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 10);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 10);
			int temp = scanf("%d", &w_be_l);
			temp = getchar();
		}
		if (w_be_l < 0 || w_be_l > 1)
		{
			Set_Cursor_And_Position(25, 9);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 9);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 9);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 11);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 11);
			int temp = scanf("%d", &n_be_l);
			temp = getchar();
		}
		if (n_be_l != 1 || n_be_l)
		{
			Set_Cursor_And_Position(25, 10);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 10);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 10);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 12);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 12);
			int temp = scanf("%d", &n_c);
			temp = getchar();
		}
		if (n_c < 0 || n_c >1)
		{
			Set_Cursor_And_Position(25, 11);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 11);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 11);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 12);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 12);
			int temp = scanf("%d", &n_a_v);
			temp = getchar();
		}
		if (n_a_v < 0 || n_a_v >1)
		{
			Set_Cursor_And_Position(25, 12);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 12);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 12);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 13);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 13);
			int temp = scanf("%d", &t_v);
			temp = getchar();
		}
		if (t_v < 0)
		{
			Set_Cursor_And_Position(25, 13);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 13);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 13);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 14);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 14);
			int temp = scanf("%d", &r_v);
			temp = getchar();
		}
		if (r_v < 0)
		{
			Set_Cursor_And_Position(25, 14);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 14);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 14);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 15);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 15);
			int temp = scanf("%d", &h_v);
			temp = getchar();
		}
		if (h_v < 0)
		{
			Set_Cursor_And_Position(25, 15);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 15);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 15);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}

	Set_Cursor_And_Position(25, 16);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 0)
			break;
		if (ch - '0' == 1)
		{
			Set_Cursor_And_Position(25, 16);
			int temp = scanf("%d", &a_v_s);
			temp = getchar();
		}
		if (a_v_s < 0 || a_v_s >3)
		{
			Set_Cursor_And_Position(25, 16);
			printf("������Ч �밴1���������0�˳�\n");
			Set_Cursor_And_Position(25, 16);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 16);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}
	while (1)
	{
		int flag = 0;
		Set_Cursor_And_Position(0, 17);
		printf("�밴��1ȷ���޸ģ�����0ȡ���޸�");
		while (!_kbhit());
		char ch = _getch();
		if (ch - '0' == 1)
		{
			strcpy(emp->name, name);//����
			strcpy(emp->job_num, j_num);//����
			strcpy(emp->department, departments[department_num - 1]);
			emp->id_department = department_num;
			strcpy(emp->identity, identities[identity_num - 1]);
			emp->id_identity = identity_num;
			emp->age = age;//����
			emp->age_of_work = age_w;//����
			emp->stage = stage; //����״̬
			strcpy(emp->password, pass);//��λ����
			emp->Whether_clock = w_clock;//�Ƿ��
			emp->Whether_be_late = w_be_l;//�Ƿ�ٵ�
			emp->num_late = n_be_l;//�ٵ���
			emp->num_clock = n_c;//�򿨴���
			emp->num_ask_vacation = n_a_v;//��ٴ���
			emp->total_annual_vacation = t_v;//�����
			emp->remaining_annual_vacation = r_v;//ʣ�����
			emp->taken_vacation = h_v;//���ü���
			emp->ask_vacation_status = a_v_s;// ���״̬��0 - δ���룬1 - �������������
			Save();
		}
		if (ch - '0' == 0)
			break;
	}
}

void ChangePassword(Employees* emp)//�����޸�
{
	system("cls");
	int flag = 0;
	while (1)
	{
		char pass1[5] = { '\0' }, pass2[5] = { '\0' };
		printf("������ԭ���룺\n");
		int temp = scanf("%s", pass1);
		temp = getchar();
		if (strcmp(pass1, emp->password) == 0)
		{
			printf("�����������룺\n");
			int temp = scanf("%s", pass1);
			temp = getchar();

			printf("���ٴ����������룺\n");
			temp = scanf("%s", pass2);
			temp = getchar();

			if (strcmp(pass1, pass2) == 0)
			{
				strcpy(emp->password, pass1);
				printf("�����޸ĳɹ���\n");
				Sleep(commmon_time);
				flag = 1;
			}
			else
			{
				printf("�������������벻ͬ��\n");
				printf("�밴r�����0�˳�\n");
				Sleep(commmon_time);
				while (!_kbhit());
				char ch = _getch();
				if (ch - '0' == 0)
				{
					flag = 1;
				}
				else if (ch == 'r')
				{
					system("cls");
					continue;
				}
			}
		}
		else
		{
			printf("ԭ�������\n");
			printf("�밴r�����0�˳�\n");
			Sleep(commmon_time);
			while (!_kbhit());
			char ch = _getch();
			if (ch - '0' == 0)
			{
				flag = 1;
			}
			else if (ch == 'r')
			{
				system("cls");
				continue;
			}
		}
		if (flag == 1)
			break;
	}
	Save();
	system("cls");
}

void RequestVacation(Employees* emp) //�������뺯��
{
	while (1)
	{
		int pick, flag = 0;
		system("cls");
		printf("------------------------------\n");
		printf("|         1.�������          |\n");
		printf("|         2.ȡ������          |\n");
		printf("|         0.�˳���          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1:
		{
			int flag = 0;
			if (emp->stage == 0)
			{
				printf("%s %s �Ѿ��ڼ����У��޷��ٴ�������ڡ�\n", emp->identity, emp->name);
				return;
			}
			if (emp->ask_vacation_status == 0)
			{
				while (1)
				{
					int pick1 = -1;
					system("cls");
					printf("-------------------------------\n");
					printf("|         1.����              |\n");
					printf("|         2.�¼�              |\n");
					printf("|         0.�˳�              |\n");
					printf("-------------------------------\n");
					int temp1 = scanf("%d", &pick1);
					if (pick1 == 1)
					{
						emp->ask_vacation_status = 11; // ����Ϊ�����������״̬
						flag = 1;
						printf("%s %s �ѳɹ����벡��\n", emp->identity, emp->name);
					}
					if (pick1 == 2)
					{
						emp->ask_vacation_status = 12; // ����Ϊ�����������״̬
						flag = 1;
						printf("%s %s �ѳɹ������¼١�\n", emp->identity, emp->name);
					}
					if (pick1 == 0)
						flag = 1;
					if(flag==1)
						break;
				}
			}
			
			else if (emp->ask_vacation_status == 11 || emp->ask_vacation_status == 12)
			{
				printf("%s %s ����������С�\n", emp->identity, emp->name);
			}
			
			else if (emp->ask_vacation_status == 2)
			{
				emp->stage = 0;
				printf("%s %s ����ͨ����\n", emp->identity, emp->name);
			}
			else if (emp->ask_vacation_status == 3)
			{
				emp->stage = 0;
				printf("%s %s ���뱻�ܾ���\n", emp->identity, emp->name);
			}
		}Sleep(commmon_time); system("cls"); break;
		case 2:emp->ask_vacation_status = 0; printf("�ѳɹ�ȡ�����롣\n"); Sleep(commmon_time); system("cls"); break;
		case 0:flag = 1; printf("�˳���¼�ɹ�\n"); Sleep(commmon_time); Save(); break;
		}
		if (flag == 1)
		{
			system("cls");
			break;
		}
	}

}

void Vacation_Management(Employees* emp) //��׼ְԱ���������
{
	system("cls");
	Employees* emp_s;
	int flag = 0, judge;
	emp_s = com[emp->id_department - 1].head;
	while (emp_s != NULL)
	{
		if (emp->ask_vacation_status == 11 || emp->ask_vacation_status == 12)
		{
			if (emp_s->id_identity != 2)
			{
				printf("���ͬ�����룬������1\n");
				printf("����ܾ����룬������2\n");
				printf("���Ҫ�˳�������������0\n");
				printf("������%s\n", emp_s->name);
				printf("���ţ�%s\n", emp_s->job_num);
				printf("ְ��%s\n", identities[emp_s->id_identity - 1]);
				printf("����٣�%d\n", emp_s->total_annual_vacation);
				printf("������٣�%d\n", emp_s->taken_vacation);
				printf("ʣ����٣�%d\n", emp_s->remaining_annual_vacation);
				int temp = scanf("%d", &judge);
				switch (judge)
				{
				case 1:emp_s->ask_vacation_status = 2; printf("��ͬ������=\n"); system("cls"); ; break;
				case 2:emp_s->ask_vacation_status = 3; printf("�Ѿܾ�����=\n"); system("cls"); ; break;
				case 0:flag = 1; printf("�˳���������ɹ�\n"); Sleep(commmon_time); system("cls");  break;
				}
			}
		}
		if (flag == 1)
			break;
		emp_s = emp_s->next;
	}
	Save();
	printf("��ȫ������\n");
	Sleep(commmon_time);
	system("cls");
}

Employees* createNewNode(Employees* originalNode) //�����µ�����ڵ㣬�����������
{
	Employees* newNode = (Employees*)malloc(sizeof(Employees));
	if (newNode == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	*newNode = *originalNode;  // ����ԭ�ڵ������
	newNode->next = NULL;      // �½ڵ�� next ָ���ʼ��Ϊ NULL
	return newNode;
}

Employees* getMiddle(Employees* head)// �ҵ�������м�ڵ�
{
	if (head == NULL) return head;

	Employees* slow = head;        // ��ָ�룬ÿ���ƶ�һ��
	Employees* fast = head;        // ��ָ�룬ÿ���ƶ�����

	while (fast->next != NULL && fast->next->next != NULL) {
		slow = slow->next;          // ��ָ���ƶ�һ��
		fast = fast->next->next;    // ��ָ���ƶ�����
	}

	return slow;  // ����ָ�뵽������ĩβʱ����ָ��ָ���м�ڵ�
}

Employees* mergeByClockTimes(Employees* left, Employees* right) // �鲢�����������򿨴������򣨴򿨵ĵ�һ����
{
	if (left == NULL) return right; // ���������Ϊ�գ�����������
	if (right == NULL) return left; // ���������Ϊ�գ�����������

	if (left->num_clock <= right->num_clock) {
		Employees* newNode = createNewNode(left); // �����½ڵ�
		newNode->next = mergeByClockTimes(left->next, right); // �ݹ�ϲ�
		return newNode;
	}
	else {
		Employees* newNode = createNewNode(right); // �����½ڵ�
		newNode->next = mergeByClockTimes(left, right->next); // �ݹ�ϲ�
		return newNode;
	}

}

Employees* mergeSortByClockTimes(Employees* head) // �鲢���������������򿨴�������

{
	if (head == NULL || head->next == NULL) {
		return createNewNode(head); // �������Ϊ�ջ�ֻ��һ���ڵ㣬ֱ�ӷ����½ڵ�
	}

	Employees* middle = getMiddle(head); // �ҵ�������м�ڵ�
	Employees* nextOfMiddle = middle->next;

	middle->next = NULL; // ��������м�ڵ㴦�ָ��������

	Employees* left = mergeSortByClockTimes(head); // �ݹ�ض���벿�ֽ�������
	Employees* right = mergeSortByClockTimes(nextOfMiddle); // �ݹ�ض��Ұ벿�ֽ�������

	return mergeByClockTimes(left, right); // �ϲ�������������
}

Employees* mergeByVacationTimes(Employees* left, Employees* right) //�鲢������������ٴ���������ٵĵ�һ����
{
	if (left == NULL) return right; // ���������Ϊ�գ�����������
	if (right == NULL) return left; // ���������Ϊ�գ�����������

	if (left->num_ask_vacation <= right->num_ask_vacation) {
		Employees* newNode = createNewNode(left); // �����½ڵ�
		newNode->next = mergeByVacationTimes(left->next, right); // �ݹ�ϲ�
		return newNode;
	}
	else {
		Employees* newNode = createNewNode(right); // �����½ڵ�
		newNode->next = mergeByVacationTimes(left, right->next); // �ݹ�ϲ�
		return newNode;
	}
}

Employees* mergeSortByVacationTimes(Employees* head)////�鲢������������ٴ���������ٵĵ�һ����
{
	if (head == NULL || head->next == NULL) {
		return createNewNode(head); // �������Ϊ�ջ�ֻ��һ���ڵ㣬ֱ�ӷ����½ڵ�
	}

	Employees* middle = getMiddle(head); // �ҵ�������м�ڵ�
	Employees* nextOfMiddle = middle->next;

	middle->next = NULL; // ��������м�ڵ㴦�ָ��������

	Employees* left = mergeSortByVacationTimes(head); // �ݹ�ض���벿�ֽ�������
	Employees* right = mergeSortByVacationTimes(nextOfMiddle); // �ݹ�ض��Ұ벿�ֽ�������

	return mergeByVacationTimes(left, right); // �ϲ�������������
}

Employees* mergeByMultipleAttributes(Employees* left, Employees* right) // �鲢�������������ٴ�����ͬ���ٰ��򿨴�������,����ٰ���������
{
	if (left == NULL) return right; // ���������Ϊ�գ�����������
	if (right == NULL) return left; // ���������Ϊ�գ�����������

	Employees* result = NULL; // ���ڴ洢�ϲ��������ͷָ��

	// �Ƚ���ٴ���
	if (left->num_ask_vacation < right->num_ask_vacation) {
		result = createNewNode(left); // �����½ڵ�
		result->next = mergeByMultipleAttributes(left->next, right); // �ݹ�ϲ�
	}
	else if (left->num_ask_vacation > right->num_ask_vacation) {
		result = createNewNode(right); // �����½ڵ�
		result->next = mergeByMultipleAttributes(left, right->next); // �ݹ�ϲ�
	}
	else {
		// ��ٴ�����ȣ��Ƚϴ򿨴���
		if (left->num_clock < right->num_clock) {
			result = createNewNode(left); // �����½ڵ�
			result->next = mergeByMultipleAttributes(left->next, right); // �ݹ�ϲ�
		}
		else if (left->num_clock > right->num_clock) {
			result = createNewNode(right); // �����½ڵ�
			result->next = mergeByMultipleAttributes(left, right->next); // �ݹ�ϲ�
		}
		else {
			// �򿨴���Ҳ��ȣ��Ƚ�����
			if (strcmp(left->name, right->name) < 0) {
				result = createNewNode(left); // �����½ڵ�
				result->next = mergeByMultipleAttributes(left->next, right); // �ݹ�ϲ�
			}
			else {
				result = createNewNode(right); // �����½ڵ�
				result->next = mergeByMultipleAttributes(left, right->next); // �ݹ�ϲ�
			}
		}
	}
	return result;
}

Employees* mergeSortByMultipleAttributes(Employees* head)
{
	if (head == NULL || head->next == NULL) {
		return head;
	}

	Employees* middle = getMiddle(head);
	Employees* nextOfMiddle = middle->next;

	middle->next = NULL;

	Employees* left = mergeSortByMultipleAttributes(head);
	Employees* right = mergeSortByMultipleAttributes(nextOfMiddle);

	return mergeByMultipleAttributes(left, right);
}

void ManagerSort(Employees* emp)//���ž����������
{
	int flag = 0;
	while (1)
	{
		int pick;
		system("cls");
		printf("-------------------------------\n");
		printf("|         1.�򿨴���          |\n");
		printf("|         2.��ٴ���          |\n");
		printf("|         3.��������          |\n");
		printf("|         4.���Ա��          |\n");
		printf("|         0.�˳�����          |\n");
		printf("-------------------------------\n");
		int temp = scanf("%d", &pick);

		switch (pick)
		{
		case 1:
		{
			system("cls");
			com[emp->id_department - 1].head = mergeSortByClockTimes(com[emp->id_department - 1].head);
			printf("������Ա����Ϣ�Ѱ��򿨴�����������\n");
			Manager_Sorted_Print(com[emp->id_department - 1].head, "�򿨴���");
		}break;
		case 2:
		{
			// ����ٴ�������
			system("cls");
			com[emp->id_department - 1].head = mergeSortByVacationTimes(com[emp->id_department - 1].head);
			printf("������Ա����Ϣ�Ѱ���ٴ�����������\n");
			Manager_Sorted_Print(com[emp->id_department - 1].head, "��ٴ���");

		} break;
		case 3:
		{
			// ����ٴ������򿨴�������������
			system("cls");
			com[emp->id_department - 1].head = mergeSortByMultipleAttributes(com[emp->id_department - 1].head);
			printf("������Ա����Ϣ�Ѱ���ٴ������򿨴�������������\n");
			Manager_Sorted_Print(com[emp->id_department - 1].head, "��١��򿨴���������");
			
		} break;

		case 4:
		{
			// ���Ҳ���ӡ���Ա��
			system("cls");
			Find_And_Print_BestEmployees(com[emp->id_department - 1].head);
		} break;
		case 0:system("cls"); flag = 1; break;
		}
		if (flag == 1)
			break;
	}
}

void Manager_Sorted_Print(Employees* head, const char* sortBy)//���ž��� ��ӡ��������Ϣ
{
	int flag = 0;
	if (head == NULL)
	{
		printf("û��Ա����Ϣ����ʾ��\n");
		flag = 1;
	}
	else
	{
		while (1)
		{
			if (strcmp(sortBy, "��١��򿨴���������") == 0)
			{
				printf("-------------------------------------\n");
				printf("| ���� | %s       |\n", sortBy);
				printf("-------------------------------------\n");

				Employees* current = head;
				while (current != NULL)
				{
					if (strcmp(sortBy, "�򿨴���") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_clock);
					}
					else if (strcmp(sortBy, "��ٴ���") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_ask_vacation);
					}
					else if (strcmp(sortBy, "��١��򿨴���������") == 0)
					{
						printf("| %-4s | ��ٴ���: %-3d �򿨴���: %-3d|\n", current->name, current->num_ask_vacation, current->num_clock);
					}
					current = current->next;
				}
				printf("-------------------------------------\n");
				while (1)
				{
					printf("�����˳�\n");
					while (!_kbhit());
					char ch = _getch();
					if (ch - '0' == 0)
						flag = 1;
					if (flag == 1)
						break;
				}
				if (flag == 1)
					break;
			}
			else
			{
				printf("-------------------\n");
				printf("| ���� | %s |\n", sortBy);
				printf("-------------------\n");

				Employees* current = head;
				while (current != NULL)
				{
					if (strcmp(sortBy, "�򿨴���") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_clock);
					}
					else if (strcmp(sortBy, "��ٴ���") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_ask_vacation);
					}
					else if (strcmp(sortBy, "��١��򿨴���������") == 0)
					{
						printf("| %-4s | ��ٴ���: %-3d �򿨴���: %-3d ����: %-4s |\n", current->name, current->num_ask_vacation, current->num_clock, current->name);
					}
					current = current->next;
				}
				printf("-------------------\n");
				while (1)
				{
					printf("�����˳�\n");
					while (!_kbhit());
					char ch = _getch();
					if (ch - '0' == 0)
						flag = 1;
					if (flag == 1)
						break;
				}
				if (flag == 1)
					break;
			}
		}
	}
}

void AdminPrintSortedEmployees(const char* sortBy)//����Ա�������ӡ��������ӡ����������
{
	printf("------------------------------\n");
	printf("| ���� | ���� | %s |\n", sortBy);
	printf("------------------------------\n");

	for (int i = 0; i < 4; i++)
	{
		Employees* current = com[i].head;
		while (current != NULL)
		{
			if (strcmp(sortBy, "�򿨴���") == 0) {
				printf("| %-6s | %-4s | %-8d |\n", com[i].department, current->name, current->num_clock);
			}
			else if (strcmp(sortBy, "��ٴ���") == 0) {
				printf("| %-6s | %-4s | %-8d |\n", com[i].department, current->name, current->num_ask_vacation);
			}
			else if (strcmp(sortBy, "��١��򿨴���������") == 0) {
				printf("| %-6s | %-4s | ��ٴ���: %-3d �򿨴���: %-3d ����: %-4s |\n", com[i].department, current->name, current->num_ask_vacation, current->num_clock, current->name);
			}
			current = current->next;
		}
	}
	printf("------------------------------\n");
}

void AdminSort(void)//����Ա��������
{
	int flag = 0;
	int sortOption;
	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.�򿨴���          |\n");
		printf("|         2.��ٴ���          |\n");
		printf("|         3.��������          |\n");
		printf("|         4.���Ա��          |\n");
		printf("|         0.�˳�����          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &sortOption);

		switch (sortOption)
		{
		case 1:
		{
			int flag = 0;
			while (1)
			{
				// ���򿨴�������
				for (int i = 0; i < 4; i++) {
					Employees* sortedHead = mergeSortByClockTimes(com[i].head); // �����µ���������
					AdminPrintSortedEmployees("�򿨴���"); // ��ӡ����������
				}
				printf("���в��ŵ�Ա����Ϣ�Ѱ��򿨴�����������\n");
				flag = Exit_with_Flag(flag);
			}

		} break;
		case 2: {
			// ����ٴ�������
			for (int i = 0; i < 4; i++) {
				Employees* sortedHead = mergeSortByVacationTimes(com[i].head); // �����µ���������
				AdminPrintSortedEmployees("��ٴ���"); // ��ӡ����������
			}
			printf("���в��ŵ�Ա����Ϣ�Ѱ���ٴ�����������\n");

		} break;
		case 3: {
			// ����١��򿨴�������������
			for (int i = 0; i < 4; i++) {
				com[i].head = mergeSortByMultipleAttributes(com[i].head);
				AdminPrintSortedEmployees("��١��򿨴���������");
			}
			printf("���в��ŵ�Ա����Ϣ�Ѱ���ٴ������򿨴�������������\n");

		} break;
		case 4: {// ���Ҳ���ӡ���Ա��
			Employees* allEmployees = NULL;
			for (int i = 0; i < 4; i++)
			{
				Employees* temp = com[i].head;
				while (temp != NULL) {
					Employees* newNode = createNewNode(temp);
					newNode->next = allEmployees;
					allEmployees = newNode;
					temp = temp->next;
				}
			}
			Find_And_Print_BestEmployees(allEmployees);
			// �ͷ���ʱ����
			while (allEmployees != NULL) {
				Employees* temp = allEmployees;
				allEmployees = allEmployees->next;
				free(temp);
			}
		}break;
		case 0:flag = 1; system("cls"); break;
		}
		if (flag)
			break;
	}
}

void Find_And_Print_BestEmployees(Employees* head)// ���Ҳ���ӡ�������Ա��
{
	int flag = 0;
	while (1)
	{
		int maxClock = 0;
		int minVacation = 200;
		Employees* emp = head;
		int bestEmployeeCount = 0;

		// ��һ�α������ҵ����򿨴�������С��ٴ���
		while (emp != NULL)
		{
			if (emp->num_late == 0)
			{ // �ٵ���Ϊ0
				if (emp->num_clock > maxClock)
				{
					maxClock = emp->num_clock;
					minVacation = emp->num_ask_vacation;
				}
				else if (emp->num_clock == maxClock && emp->num_ask_vacation < minVacation)
				{
					minVacation = emp->num_ask_vacation;
				}
			}
			emp = emp->next;
		}

		// �ڶ��α�������ӡ���з������������Ա��
		emp = head;
		printf("���Ա����Ϣ��\n");
		printf("------------------------------------------------\n");
		printf("|����\t����\t    �򿨴���\t��ٴ���       |\n");
		while (emp != NULL)
		{
			if (emp->num_late == 0 && emp->num_clock == maxClock && emp->num_ask_vacation == minVacation)
			{
				printf("|%s\t%s\t    %d\t\t%d              |\n", emp->name, emp->job_num, emp->num_clock, emp->num_ask_vacation);
				bestEmployeeCount++;
			}
			emp = emp->next;
		}
		printf("------------------------------------------------\n");
		if (bestEmployeeCount == 0)
		{
			printf("û�з������������Ա����\n");
		}
		else
		{
			printf("���ҵ� %d �����Ա����\n", bestEmployeeCount);
		}
		flag = Exit_with_Flag(flag);
		if (flag == 1)
			break;
	}
}

void Information_Management(Employees* emp)
{
	char pass[5] = { '\0' };
	printf("���ٴ��������룺");
	int temp = scanf("%s", pass);
	if (strcmp(emp->password, pass) == 0)
	{
		int flag = 0, pick = -1;
		while (1)
		{
			system("cls");
			printf("------------------------------\n");
			printf("|         1.�ɹ�����          |\n");
			printf("|         2.��������          |\n");
			printf("|         3.���۲���          |\n");
			printf("|         4.������          |\n");
			printf("|         0.�˳�����          |\n");
			printf("------------------------------\n");
			int temp = scanf("%d", &pick);
			switch (pick)
			{
			case 1:Information_Management_1(com[0]); break;
			case 2:Information_Management_1(com[1]); break;
			case 3:Information_Management_1(com[2]); break;
			case 4:Information_Management_1(com[3]); break;
			case 0:flag = 1; printf("�˳��ɹ�"); Sleep(commmon_time); system("cls"); break;
			}
			if (flag == 1)
				break;
		}
	}
	else
	{
		printf("�������\n");
		Sleep(commmon_time);
		system("cls");
	}
}

void Information_Management_1(Companys com)
{

	int flag = 0, pick = -1;
	while (1)
	{
		system("cls");
		printf("%s��\n", com.department);
		printf("Ա������%d\n", com.num_of_staff);
		printf("------------------------------\n");
		printf("|         1.�޸���Ϣ          |\n");
		printf("|         2.���Ա��          |\n");
		printf("|         3.ɾ��Ա��          |\n");
		printf("|         0.�˳�����          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1:Modify_Seek(com); break;
		case 2:InputStaff(); break;
		case 3:DeleteStaff();
		case 0:flag = 1; printf("�˳��ɹ�"); Sleep(commmon_time); system("cls"); break;
		}
		if (flag == 1)
			break;
	}
}

void System_maintenance(void)//ϵͳά��
{
	system("cls");
	Save();
	char filename[20] = { '\0' };
	FILE* newFile = fopen("new.txt", "w");
	if (newFile == NULL)
	{
		printf("�޷�����ʱ�ļ�\n");
		Sleep(error_time);
		exit(1);
	}
	for (int i = 0; i < 4; i++)
	{
		Employees* emp = com[i].head;
		while (emp != NULL)
		{
			fprintf(newFile, "%s %s %d %d %d %d %d %s 0 1111111111111111 1111111111111111 0 %d %d %d %d %d %d %d\n",
				emp->name, emp->job_num, emp->id_department, emp->id_identity, emp->age, emp->age_of_work, emp->stage, emp->password,
				emp->num_late, emp->num_clock, emp->num_ask_vacation, emp->total_annual_vacation, emp->taken_vacation,
				emp->remaining_annual_vacation, emp->ask_vacation_status);
			emp = emp->next;
		}
	}
	fclose(newFile);

	time_t current_time = time(NULL);
	struct tm* local_time = localtime(&current_time);
	snprintf(filename, sizeof(filename), "data%d.%d.txt", local_time->tm_mon + 1, local_time->tm_mday);
	int team = rename("data.txt", filename);
	team = rename("new.txt", "data.txt");
	printf("�ɹ����浱������");
	Sleep(commmon_time);
}

void Annual_leave_allocation(void)//�������
{
	for (int i = 0; i < 4; i++)
	{
		Employees* emp;
		emp = com[i].head;
		while (emp != NULL)
		{
			if (emp->age_of_work < 10)
			{
				emp->total_annual_vacation = 5;
			}
			else if (emp->age_of_work < 20)
			{
				emp->total_annual_vacation = 10;
			}
			else
			{
				emp->total_annual_vacation = 15;
			}
			emp = emp->next;
		}
	}
}

void Stats(Employees* emp_m)
{
	int flag = 0, pick = -1;
	Employees* emp;
	emp = com[emp_m->id_department - 1].head;
	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.��ͳ��          |\n");
		printf("|         2.�ٵ�ͳ��          |\n");
		printf("|         3.����ͳ��          |\n");
		printf("|         4.״̬ͳ��          |\n");
		printf("|         0.�˳�ͳ��          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		temp = getchar();
		switch (pick)
		{
		case 1:
		{
			int count = 0;
			emp = com[emp_m->id_department - 1].head;
			while (emp != NULL)
			{
				if (emp->Whether_clock != 1)
					count++;
				emp = emp->next;
			}
			printf("���ձ�������%d��δ��", count);
			Sleep(commmon_time);
		}break;
		case 2:
		{
			int count = 0;
			emp = com[emp_m->id_department - 1].head;
			while (emp != NULL)
			{
				if (emp->Whether_be_late == 1)
					count++;
				emp = emp->next;
			}
			printf("���ձ�������%d�˳ٵ�", count);
			Sleep(commmon_time);
		}break;
		case 3:
		{
			int age = 0;
			printf("������һ���ֽ�����");
			int temp = scanf("%d", &age);
			int count_less = 0, count_more = 0, count = 0;
			emp = com[emp_m->id_department - 1].head;
			while (emp != NULL)
			{
				if (emp->age == age)
					count++;
				else if (emp->age < age)
					count_less++;
				else
					count_more++;
				emp = emp->next;
			}
			printf("����%d�������%d��\n", age, count);
			printf("С��%d�������%d��\n", age, count_less);
			printf("����%d�������%d��\n", age, count_more);
			Sleep(commmon_time);
		}break;
		case 4:
		{
			int count = 0;
			emp = com[emp_m->id_department - 1].head;
			while (emp != NULL)
			{
				if (emp->stage == 0)
					count++;
				emp = emp->next;
			}
			printf("���ձ�������%d���ݼ�", count);
			Sleep(commmon_time);
		}break;
		case 0:flag = 1; system("cls"); break;
		}
		if (flag == 1)
			break;
	}
}