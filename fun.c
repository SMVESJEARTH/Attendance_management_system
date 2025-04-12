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
		printf("按零退出\n");
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

void Save(void)//数据保存
{
	char line[101] = { '\0' };

	FILE* newFile = fopen("temp.txt", "w");
	if (newFile == NULL)
	{
		printf("无法打开临时文件\n");
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
				emp->time_of_clock, emp->time_of_leave, emp->Whether_be_late, emp->num_late,emp->num_clock,emp->num_ask_vacation, emp->total_annual_vacation, emp->taken_vacation,
				emp->remaining_annual_vacation,emp->ask_vacation_status);
			emp = emp->next;
		}
	}
	fclose(newFile);
	remove("data.txt");
	int useless = rename("temp.txt", "data.txt");
}

Employees* CreatAndRead_employees(int i)//创建链表与读取数据
{
	char name[4] = { '\0' };//姓名
    char j_num[8] = { '\0' };//工号
    int department_num = 0;//所属部门编号
	int identity_num = 0;// 职位编号
    int age = 0;//年龄
	int age_w = 0;//工龄
	int stage = 0;//工作状态 1为正常工作 0为假期中
	char pass[5] = { '\0' };//四位密码
    int w_clock = 0;//是否打卡 1是 0否
	char tm_of_c[20] = { "1111111111111111" };//打卡时间
	char tm_of_l[20] = { "1111111111111111" };//离开时间
    int w_be_l = 0;//是否迟到
    int n_be_l = 0;//迟到数
	int n_c = 0;//打卡次数
	int n_a_v = 0;//请假次数
    int t_v = 0;//总年假
    int h_v = 0;//已用假期
    int r_v = 0;//剩余年假
	int a_v_s = 0;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝

    Employees *head = NULL, *p1 = NULL, *p2 = NULL;
    FILE *fp = fopen("data.txt", "r");//只读打开data.txt
    if (fp == NULL)
    {
        printf("文件不存在");
		Sleep(error_time);
		exit(1);
    }
																 
	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d %d %d", 
        name,j_num,&department_num,&identity_num,&age,&age_w,&stage,pass,
		&w_clock, tm_of_c, tm_of_l,&w_be_l,&n_be_l,&n_c,&n_a_v,&t_v,&h_v,&r_v,&a_v_s) == 19)//每一行有19个数据 所以fscanf返回值为19

	{
		if (department_num == i + 1)//程序中的部门索引是0~3 而文件和手动输入的部门索引是1~4，故加1
		{
			p1 = (Employees*)malloc(sizeof(Employees));//开辟内存
			if (p1 == NULL)
			{
				fclose(fp); // 内存分配失败，关闭文件
				Sleep(error_time);
				exit(1);
			}

            //数据读入
			strcpy(p1->name, name);//姓名
            strcpy(p1->job_num, j_num);//工号
            if (department_num >= 1 && department_num <= 4)//所属部门编号
                strcpy(p1->department, departments[i]);
            p1->id_department = department_num;
            if (identity_num >= 1 && identity_num <=3)//职位编号
                strcpy(p1->identity, identities[identity_num - 1]);
            p1->id_identity = identity_num;
            p1->age = age;//年龄
            p1->age_of_work = age_w;//工龄
            p1->stage = stage; //工作状态
            strcpy(p1->password, pass);//四位密码
            p1->Whether_clock = w_clock;//是否打卡
            strcpy(p1->time_of_clock, tm_of_c);//打卡时间
            strcpy(p1->time_of_leave, tm_of_l);//离开时间
            p1->Whether_be_late = w_be_l;//是否迟到
            p1->num_late = n_be_l;//迟到数
			p1->num_clock = n_c;//打卡次数
			p1->num_ask_vacation = n_a_v;//请假次数
            p1->total_annual_vacation = t_v;//总年假
            p1->taken_vacation = h_v;//已用假期
            p1->remaining_annual_vacation = r_v;//剩余年假
			p1->ask_vacation_status = a_v_s;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝


			if (head == NULL)
				head = p1;
			else
				p2->next = p1;
			p2 = p1;
			p2->next = NULL;
			com[i].num_of_staff++;//部门员工数自增
		}
	}
	fclose(fp);
	return head;
}

void Init_company(void)//初始化公司数组
{
	for (int i = 0; i < 4; i++)
	{
		com[i].order = i + 1;
		strcpy(com[i].department, departments[i]);
		com[i].num_of_staff = 0;//初始化部门人数
		com[i].head = CreatAndRead_employees(i);//i从0~3代表不同公司部门
	}
}

void Complete_job_num(void)//完成工号
{
	for (int i = 0; i < 4; i++)
	{
		Employees *emp = com[i].head;
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

Employees* LoginAndUi(void)//登录系统
{
	for (int j = 0; j < 3; j++)
	{
		system("cls");
		char j_num[8] = { '\0' };
		char pass[5] = { '\0' };
		printf("请登录\n");
		printf("工号：");
		fgets(j_num, sizeof(j_num),stdin);
		char useless = getchar();
		printf("密码：");
		fgets(pass, sizeof(pass), stdin);
		useless = getchar();
		bool flag = 0;
		for (int i = 0; i < 4; i++)
		{
			Employees* emp = com[i].head;
			while (emp != NULL)
			{
				if (!strcmp(emp->job_num, j_num) && !strcmp(emp->password, pass))
				{
					printf("%s %s 验证通过，欢迎登录\n", emp->identity, emp->name);
					Sleep(commmon_time);
					return emp;
				}
				emp = emp->next;
			}
			if (flag == 1)
				break;
		}
		printf("密码或工号有误,请重新输入");
		Sleep(commmon_time);
	}
	printf("连续错误三次，请联系管理员核对工号或密码\n");
	exit(1);
}

void Select_clock(Employees *emp)//打卡选择
{
	int pick = -1;
	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.上班打卡          |\n");
		printf("|         2.下班打卡          |\n");
		printf("|         0.退出打卡          |\n");
		printf("------------------------------\n");
		int flag = 0;
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1:
		{
			if (emp->Whether_clock == 1)
			{
				printf("今日已打卡，请勿重复打卡");
				Sleep(commmon_time);
				system("cls");
				break;
			}
			time_t current_time = time(NULL);
			struct tm *local_tm;
			local_tm = localtime(&current_time);//将时间戳转为本地时间
			if (emp->Whether_clock != 1 && local_tm->tm_hour > 6)
			{
				emp->Whether_clock = 1;
				printf("打卡成功\n");

				printf("打卡时间：%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
					local_tm->tm_hour, local_tm->tm_min);

				int temp = sprintf(emp->time_of_clock, "%d-%02d-%02d.%d:%02d",
					local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday, local_tm->tm_hour, local_tm->tm_min);

				if (local_tm->tm_hour < time_of_start_hour)
				{
					emp->Whether_be_late = 0;
					printf("未迟到\n");
				}
				else
				{
					emp->Whether_be_late = 1;
					emp->num_late++;
					printf("已迟到\n");
				}
				Save();
				Sleep(commmon_time);
				system("cls");
			}
			else if (local_tm->tm_hour < 6)
			{
				printf("未到打卡时间(6:00),打卡失败\n");
				Sleep(commmon_time);
				system("cls");
			}
		}break;
		case 2:
		{
			if (strcmp(emp->time_of_leave,"1111111111111111") != 0)
			{
				printf("今日已下班打卡，请勿重复打卡");
				Sleep(commmon_time);
				system("cls");
				break;
			}
			if (emp->Whether_clock == 1)
			{
				time_t current_time = time(NULL);
				struct tm *local_tm;
				local_tm = localtime(&current_time);
				printf("下班时间：%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
					local_tm->tm_hour, local_tm->tm_min);

				int temp = sprintf(emp->time_of_leave, "%d-%02d-%02d.%d:%02d",
					local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday, local_tm->tm_hour, local_tm->tm_min);

				Save();
				Sleep(commmon_time);
				system("cls");
			}
			else
			{
				printf("今日还未上班打卡");
				Sleep(commmon_time);
				system("cls");
			}
		}break;
		case 0:	system("cls"); flag = 1; Save(); break;
		default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
			break;
	}
}

void Information_Inquiry_Individual(Employees *emp)//信息查询
{
	int flag = 1;
	system("cls");

	FILE *fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("无法打开data文件\n");
		Sleep(error_time);
		exit(1);
	}

	char name[4] = { '\0' };//姓名
	char j_num[8] = { '\0' };//工号
	int department_num = 0;//所属部门编号
	int identity_num = 0;// 职位编号
	int age = 0;//年龄
	int age_w = 0;//工龄
	int stage = 0;//工作状态 1为正常工作 0为假期中
	char pass[5] = { '\0' };//四位密码
	int w_clock = 0;//是否打卡 1是 0否
	char tm_of_c[20] = { '\0' };//打卡时间
	char tm_of_l[20] = { '\0' };//离开时间
	int w_be_l = 0;//是否迟到
	int n_be_l = 0;//迟到数
	int n_c = 0;//打卡次数
	int n_a_v = 0;//请假次数
	int t_v = 0;//总年假
	int h_v = 0;//已用假期
	int r_v = 0;//剩余年假
	int a_v_s = 0;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝

	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d %d %d",
		name, j_num, &department_num, &identity_num, &age, &age_w, &stage, pass,
		&w_clock, tm_of_c, tm_of_l, &w_be_l, &n_be_l, &n_c, &n_a_v, &t_v, &h_v, &r_v, &a_v_s) == 19)
	{
		if (strcmp(emp->job_num, j_num) == 0)
			break;
	}

	while (1)
	{
		printf("以下为%s的个人信息:\n",emp->name);
		printf("姓名：%s\n", name);
		printf("工号：%s\n", j_num);
		printf("部门：%s\n", departments[department_num - 1]);
		printf("职务：%s\n", identities[identity_num - 1]);
		printf("年龄：%d\n", age);
		printf("工龄：%d\n", age_w);
		printf("密码：****\n");
		printf("工作状态：");
		if (stage)
			printf("工作中...\n");
		else
			printf("休假中\n");
		printf("是否打卡：");
		if (w_clock)
			printf("已打卡...\n");
		else
			printf("未打卡O.o\n");

		if (strcmp(tm_of_c, "1111111111111111") == 0)
			printf("上班时间：还未进行上班打卡\n");
		else
			printf("打卡时间：%s\n", tm_of_c);

		if (strcmp(tm_of_l, "1111111111111111") == 0)
			printf("下班时间：还未进行下班打卡\n");
		else
			printf("下班时间：%s\n", tm_of_l);
		printf("是否迟到：");
		if (w_be_l)
			printf("已迟到＞﹏＜\n");
		else
			printf("未迟到\n");
		printf("迟到数：%d\n", n_be_l);
		printf("打卡数：%d\n", n_c);
		printf("请假数：%d\n", n_a_v);
		printf("总年假：%d\n", t_v);
		printf("已用假期：%d\n", h_v);
		printf("剩余年假：%d\n", r_v);
		printf("请假状态：%d\n", a_v_s);
		printf("--输入'p'显示密码--\n");
		printf("--输入0退出--\n");
		while (1)
		{
			while (!_kbhit());
			char ch = _getch();
			if (ch == 'p')
			{
				ClearLine(7);
				printf("密码：%s", pass);
				Sleep(commmon_time);
				ClearLine(7);
				printf("密码：****");
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

void Manger_Information_Inquiry_Department(Employees *emp)
{
	{
		Employees *emp_s;
		int pick = -1, flag = 0;

		while (1)
		{
			system("cls");
			printf("------------------------------\n");
			printf("|         1.工号查询          |\n");
			printf("|         2.姓名查询          |\n");
			printf("|         3.职位查询          |\n");
			printf("|         4.年龄查询          |\n");
			printf("|         5.状态查询          |\n");
			printf("|         0.退出查询          |\n");
			printf("------------------------------\n");
			int temp = scanf("%d", &pick);
			temp = getchar();
			switch (pick)
			{
				case 1:
					{
						int flag = 0, judge = 0;
						system("cls");
						printf("请输入要查询的工号：");
						char j_num[8] = { '\0' };//工号
						fgets(j_num, sizeof(j_num), stdin);
						char useless=getchar();
						emp_s = com[emp->id_department-1].head;
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
							printf("信息如下:\n");
							printf("姓名：%s\n", emp_s->name);
							printf("工号：%s\n", j_num);
							printf("部门：%s\n", departments[emp_s->id_department - 1]);
							printf("职务：%s\n", identities[emp_s->id_identity - 1]);
							printf("年龄：%d\n", emp_s->age);
							printf("工龄：%d\n", emp_s->age_of_work);
							printf("工作状态：");
							if (emp_s->stage)
								printf("工作中...\n");
							else
								printf("休假中\n");
							printf("是否打卡：");
							if (emp_s->Whether_clock)
								printf("已打卡...\n");
							else
								printf("未打卡O.o\n");

							if (strcmp(emp_s->time_of_clock, "1111111111111111") == 0)
								printf("上班时间：还未进行上班打卡\n");
							else
								printf("打卡时间：%s\n", emp_s->time_of_clock);

							if (strcmp(emp_s->time_of_leave, "1111111111111111") == 0)
								printf("下班时间：还未进行下班打卡\n");
							else
								printf("下班时间：%s\n", emp_s->time_of_leave);
							printf("是否迟到：");
							if (emp_s->Whether_be_late)
								printf("已迟到＞﹏＜\n");
							else
								printf("未迟到\n");
							printf("迟到数：%d\n", emp_s->num_late);
							printf("打卡数：%d\n", emp_s->num_clock);
							printf("请假数：%d\n", emp_s->num_ask_vacation);
							printf("总年假：%d\n", emp_s->total_annual_vacation);
							printf("已用假期：%d\n", emp_s->taken_vacation);
							printf("剩余年假：%d\n", emp_s->remaining_annual_vacation);
							printf("请假状态：%d\n", emp_s->ask_vacation_status);
							printf("--输入0退出--\n");
							flag = Exit_with_Flag(flag);
						}
						else
						{
							printf("查无此人\n");
							Sleep(commmon_time);
							system("cls");
						}
					}break;
				case 2:
					{
						int flag = 0, judge = 0;
						system("cls");
						printf("请输入要查询的姓名：");
						char name[4] = { '\0' };//姓名
						fgets(name,sizeof(name),stdin);
						char useless = getchar();
						printf("------------------------------\n");
						emp_s = com[emp->id_department - 1].head;
						while (emp_s != NULL)
						{
							if (strcmp(emp_s->name, name) == 0)
							{
								judge = 1;
								printf("工号：%s\n", emp_s->job_num);
								printf("职位：%s\n", emp_s->identity);
								printf("年龄：%d\n", emp_s->age);
								printf("状态：%d\n", emp_s->stage);
								printf("------------------------------\n");
							}
							emp_s = emp_s->next;
						}
						
						if (judge == 0)
							printf("查无此人\n");
						flag = Exit_with_Flag(flag);
					}break;
				case 3:
					{
						int flag = 0, judge = 0;
						system("cls");
						printf("请输入要查询的职位编号：");
						int identity_num = 0;// 职位编号
						int temp = scanf("%d", &identity_num);
						printf("------------------------------\n");
						emp_s = com[emp->id_department - 1].head;
						while (emp_s != NULL)
						{
							if (emp_s->id_identity == identity_num)
							{
								judge = 1;
								printf("姓名：%s\n", emp_s->job_num);
								printf("工号：%s\n", emp_s->job_num);
								printf("年龄：%d\n", emp_s->age);
								printf("状态：%d\n", emp_s->stage);
								printf("------------------------------\n");
							}
							emp_s = emp_s->next;
						}
						
						if (judge == 0)
							printf("查无此人\n");
						flag = Exit_with_Flag(flag);
					}break;
				case 4:
					{
						int flag = 0, judge = 0;
						system("cls");
						printf("请输入要查询的年龄：");
						int age = 0;//年龄
						int temp = scanf("%d", &age);
						printf("------------------------------\n");
						emp_s = com[emp->id_department - 1].head;		
						while (emp_s != NULL)
						{
							if (emp_s->age == age)
							{
								judge = 1;
								printf("姓名：%s\n", emp_s->job_num);
								printf("工号：%s\n", emp_s->job_num);
								printf("职位：%s\n", emp_s->identity);
								printf("状态：%d\n", emp_s->stage);
								printf("------------------------------\n");
							}
							emp_s = emp_s->next;
						}
						
						if (judge == 0)
							printf("查无此人\n");
						flag = Exit_with_Flag(flag);
					}break;
				case 5:
					{
						int flag = 0, judge = 0;
						system("cls");
						printf("请输入要查询的工作状态：");
						int stage = 0;//工作状态 1为正常工作 0为假期中
						int temp = scanf("%d", &stage);
						printf("------------------------------\n");
						emp_s = com[emp->id_department - 1].head;
						while (emp_s != NULL)
						{
							if (emp_s->stage == stage)
							{
								judge = 1;
								printf("姓名：%s\n", emp_s->job_num);
								printf("工号：%s\n", emp_s->job_num);
								printf("职位：%s\n", emp_s->identity);
								printf("年龄：%d\n", emp_s->age);
								printf("------------------------------\n");
							}
							emp_s = emp_s->next;
						}
						
						if (judge == 0)
							printf("查无此人\n");
						flag = Exit_with_Flag(flag);
					}break;
				case 0:flag = 1; system("cls"); break;
				default: printf("请重新选择"); Sleep(commmon_time); break;
			}
			if (flag == 1)
				break;
		}
	}
}

void Admin_Information_Inquiry_Department(void)
{
	Employees *emp;
	int pick = -1, flag = 0;

	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.工号查询          |\n");
		printf("|         2.姓名查询          |\n");
		printf("|         3.职位查询          |\n");
		printf("|         4.年龄查询          |\n");
		printf("|         5.状态查询          |\n");
		printf("|         6.模糊年龄          |\n");
		printf("|         0.退出查询          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		temp = getchar();
		switch (pick)
		{
			case 1:
				{
					int flag = 0, judge = 0;
					system("cls");
					printf("请输入要查询的工号：");
					char j_num[8] = { '\0' };//工号
					fgets(j_num, sizeof(j_num), stdin);
					char useless = getchar();
					for (int i = 0;; i++)
					{
						emp = com[i].head;
						while (emp != NULL)
						{
							if (strcmp(emp->job_num, j_num) == 0)
							{
								judge = 1;
								break;
							}
							emp = emp->next;
						}
					}
					if (judge == 1)
					{
						system("cls");
						printf("信息如下:\n");
						printf("姓名：%s\n", emp->name);
						printf("工号：%s\n", j_num);
						printf("部门：%s\n", departments[emp->id_department - 1]);
						printf("职务：%s\n", identities[emp->id_identity - 1]);
						printf("年龄：%d\n", emp->age);
						printf("工龄：%d\n", emp->age_of_work);
						printf("工作状态：");
						if (emp->stage)
							printf("工作中...\n");
						else
							printf("休假中\n");
						printf("是否打卡：");
						if (emp->Whether_clock)
							printf("已打卡...\n");
						else
							printf("未打卡O.o\n");

						if (strcmp(emp->time_of_clock, "1111111111111111") == 0)
							printf("上班时间：还未进行上班打卡\n");
						else
							printf("打卡时间：%s\n", emp->time_of_clock);

						if (strcmp(emp->time_of_leave, "1111111111111111") == 0)
							printf("下班时间：还未进行下班打卡\n");
						else
							printf("下班时间：%s\n", emp->time_of_leave);
						printf("是否迟到：");
						if (emp->Whether_be_late)
							printf("已迟到＞﹏＜\n");
						else
							printf("未迟到\n");
						printf("迟到数：%d\n", emp->num_late);
						printf("打卡数：%d\n", emp->num_clock);
						printf("请假数：%d\n", emp->num_ask_vacation);
						printf("总年假：%d\n", emp->total_annual_vacation);
						printf("已用假期：%d\n", emp->taken_vacation);
						printf("剩余年假：%d\n", emp->remaining_annual_vacation);
						printf("请假状态：%d\n", emp->ask_vacation_status);
						printf("--输入0退出--\n");
						flag=Exit_with_Flag(flag);
					}
					else
					{
						printf("查无此人\n");
						Sleep(commmon_time);
						system("cls");
					}
				}break;
			case 2: 
				{
					int flag = 0, judge = 0;
					system("cls");
					printf("请输入要查询的姓名：");
					char name[4] = { '\0' };//姓名
					fgets(name,sizeof(name),stdin);
					char useless = getchar();
					printf("------------------------------\n");
					for (int i = 0; i < 4; i++)
					{
						emp = com[i].head;
						while (emp != NULL)
						{
							if (strcmp(emp->name, name) == 0)
							{
								judge = 1;
								printf("工号：%s\n", emp->job_num);
								printf("职位：%s\n", emp->identity);
								printf("年龄：%d\n", emp->age);
								printf("状态：%d\n", emp->stage);
								printf("------------------------------\n");
							}
							emp = emp->next;
						}
					}
					if (judge == 0)
						printf("查无此人\n");
					flag=Exit_with_Flag(flag);
				}break;
			case 3:
				{
					int flag = 0, judge = 0;
					system("cls");
					printf("请输入要查询的职位编号：");
					int identity_num = 0;// 职位编号
					int temp = scanf("%d", &identity_num);
					printf("------------------------------\n");
					for (int i = 0; i < 4; i++)
					{
						emp = com[i].head;
						while (emp != NULL)
						{
							if (emp->id_identity == identity_num)
							{
								judge = 1;
								printf("姓名：%s\n", emp->job_num);
								printf("工号：%s\n", emp->job_num);
								printf("年龄：%d\n", emp->age);
								printf("状态：%d\n", emp->stage);
								printf("------------------------------\n");
							}
							emp = emp->next;
						}
					}
					if (judge == 0)
						printf("查无此人\n");
					flag=Exit_with_Flag(flag);
				}break;
			case 4:
				{
					int flag = 0, judge = 0;
					system("cls");
					printf("请输入要查询的年龄：");
					int age = 0;//年龄
					int temp = scanf("%d", &age);
					printf("------------------------------\n");
					for (int i = 0; i < 4; i++)
					{
						emp = com[i].head;
						while (emp != NULL)
						{
							if (emp->age == age)
							{
								judge = 1;
								printf("姓名：%s\n", emp->job_num);
								printf("工号：%s\n", emp->job_num);
								printf("职位：%s\n", emp->identity);
								printf("状态：%d\n", emp->stage);
								printf("------------------------------\n");
							}
							emp = emp->next;
						}
					}
					if (judge == 0)
						printf("查无此人\n");
					flag=Exit_with_Flag(flag);
				}break;
			case 5:
				{
					int flag = 0, judge = 0;
					system("cls");
					printf("请输入要查询的工作状态：");
					int stage = 0;//工作状态 1为正常工作 0为假期中
					int temp = scanf("%d", &stage);
					printf("------------------------------\n");
					for (int i = 0; i < 4; i++)
					{
						emp = com[i].head;
						while (emp != NULL)
						{
							if (emp->stage == stage)
							{
								judge = 1;
								printf("姓名：%s\n", emp->job_num);
								printf("工号：%s\n", emp->job_num);
								printf("职位：%s\n", emp->identity);
								printf("年龄：%d\n", emp->age);
								printf("------------------------------\n");
							}
							emp = emp->next;
						}
					}
					if (judge == 0)
						printf("查无此人\n");
					flag=Exit_with_Flag(flag);
				}break;
			case 6:
				{
					int Minage = 0, Maxage = 0, flag = -1;
					system("cls");
					printf("请输入要查询的年龄范围:\n");
					while (1)
					{
						flag = -1;
						ClearLine(2);
						ClearLine(3);
						Set_Cursor_And_Position(0, 1);
						printf("最小年龄：");
						scanf("%d", &Minage);
						if (Minage < 18 || Minage>60)
						{
							printf("输入错误 请输入1重新输入或输入0退出输入");
							char ch = fgetc(stdin);
							if (ch - '0' == 0)
								flag = 1;
							if (flag == 1)
								break;
						}
						else
							break;
					}
					if (flag == 1)
						break;

					while (1)
					{
						flag = -1;
						ClearLine(3);
						ClearLine(4);
						Set_Cursor_And_Position(0, 2);
						printf("最大年龄：");
						scanf("%d", &Maxage);
						if(Maxage< Minage)
						{
							printf("输入错误 请输入1重新输入或输入0退出输入");
							char ch = fgetc(stdin);
							if (ch - '0' == 0)
								flag = 1;
							else
								continue;
							if (flag == 1)
								break;
						}
						if (Maxage < 18 || Maxage>60)
						{

							printf("输入错误 请输入1重新输入或输入0退出输入");
							char ch = fgetc(stdin);
							if (ch - '0' == 0)
								flag = 1;
							if (flag == 1)
								break;
						}
						else
							break;
					}
					if (flag == 1)
						break;
					printf("------------------------------\n");
					for (int i = 0; i < 4; i++)
					{
						Employees *emp = com[i].head;
						while (emp != NULL)
						{
							if (emp->age <= Maxage && emp->age >= Minage)
							{
								printf("姓名：%s\n", emp->name);
								printf("工号：%s\n", emp->job_num);
								printf("部门：%s\n", emp->department);
								printf("职位：%s\n", emp->identity);
								printf("年龄：%d\n", emp->age);
								printf("------------------------------\n");
							}
							
							emp = emp->next;
						}
					}
					flag = Exit_with_Flag(flag);
				}
			case 0:flag = 1; system("cls"); break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
			break;
	}
}

void Staff_And_Ui(Employees *emp)//员工功能
{
	int pick = 0;
	int flag = 0;
	while (1)
	{
		if (flag == 1)
			break;
		system("cls");
		printf("------------------------------\n");
		printf("|         1.打卡选择          |\n");
		printf("|         2.信息查询          |\n");
		printf("|         3.请假系统          |\n");
		printf("|         4.修改密码          |\n");
		printf("|         0.退出登录          |\n");

		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
			case 1: Select_clock(emp); break;
			case 2: Information_Inquiry_Individual(emp); break;
			case 3: RequestVacation(emp); break;
			case 4: ChangePassword(emp); break;
			case 0: flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); system("cls"); ; Save(); break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
	}
}

void Manager_And_Ui(Employees* emp) //部门经理功能
{
	
	int pick = 0;
	int flag = 0;
	int days = 0;
	while (1)
	{
		system("cls");
		printf("-------------------------------\n");
		printf("|         1.打卡选择          |\n");
		printf("|         2.个人查询          |\n");
		printf("|         3.部门查询          |\n");
		printf("|         4.信息排序          |\n");
		printf("|         5.审批请假          |\n");
		printf("|         6.信息统计          |\n");
		printf("|         7.修改密码          |\n");
		printf("|         0.退出登录          |\n");
		printf("-------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
			case 1: Select_clock(emp); break;
			case 2: Information_Inquiry_Individual(emp); break;
			case 3: Manger_Information_Inquiry_Department(emp); break;
			case 4: ManagerSort(emp); break;
			case 5: Vacation_Management(emp); break;
			case 6: Stats(emp); break;
			case 7: ChangePassword(emp); break;
			case 0:flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); system("cls"); Save(); break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
			break;
	}
}

void Admin_And_Ui(Employees* emp)//管理员功能
{
	
	int flag = 0, pick = 0;
	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.系统维护          |\n");
		printf("|         2.打卡选择          |\n");
		printf("|         3.个人查询          |\n");
		printf("|         4.部门查询          |\n");
		printf("|         5.信息排序          |\n");
		printf("|         6.信息管理          |\n");
		printf("|         7.修改密码          |\n");
		printf("|         0.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
			case 1:  System_maintenance(); break;
			case 2: Select_clock(emp); break;
			case 3: Information_Inquiry_Individual(emp); break;
			case 4: Admin_Information_Inquiry_Department(); break;
			case 5: AdminSort(); break;
			case 6: Information_Management(emp); break;
			case 7: ChangePassword(emp); break;
			case 0: flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); system("cls"); Save(); break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
			break;
	}
}

void InputStaff(Companys com) //添加员工
{
	system("cls");
	int flag = 0;
	char name[4] = { '\0' };//姓名
	int department_num = 0;//所属部门编号
	int identity_num = 0;// 职位编号
	int age = 0;//年龄
	int age_w = 0;//工龄
	int stage = 0;//工作状态 1为正常工作 0为假期中
	char pass[5] = { '\0' };//四位密码
	int w_clock = 0;//是否打卡 1是 0否
	int w_be_l = 0;//是否迟到
	int n_be_l = 0;//迟到数
	int n_c = 0;//打卡次数
	int n_a_v = 0;//请假次数
	int r_v = 0;//剩余年假
	int h_v = 0;//已用假期
	int a_v_s = 0;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝

	char tm_of_c[20] = { "1111111111111111" };//打卡时间
	char tm_of_l[20] = { "1111111111111111" };//离开时间
	int t_v = 0;//总年假

	department_num = com.order;
	
	while(1)
	{
		printf("请输入员工信息\n");

		while (1)
		{
			printf("姓名(不超过3个字符)：");
			fgets(name, sizeof(name), stdin);
			char useless = getchar();
			if (strlen(name) != 3 || name[0] < 'A' || name[0]>'Z' || name[1] < 'A' || name[1]>'Z' || name[2] < 'A' || name[2]>'Z')
			{
				Set_Cursor_And_Position(40, 1);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 1);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 1);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;


		while (1)
		{
			printf("职位(1~3)：");
			int temp = scanf("%d", &identity_num);
			temp = getchar();
			if (identity_num < 1 || identity_num>3)
			{
				Set_Cursor_And_Position(40, 2);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 2);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 2);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("年龄(18~60)：");
			int temp = scanf("%d", &age);
			temp = getchar();
			if (age < 18 || age>60)
			{
				Set_Cursor_And_Position(40, 3);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 3);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 3);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("工龄(>0)：");
			int temp = scanf("%d", &age_w);
			temp = getchar();
			if (age_w < 0)
			{
				Set_Cursor_And_Position(40, 4);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 4);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 4);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("工作状态(0 or 1)：");
			int temp = scanf("%d", &stage);
			temp = getchar();
			if (stage < 0 || stage > 1)
			{
				Set_Cursor_And_Position(40, 5);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 5);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 5);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("密码(四位)：");
			fgets(pass,sizeof(pass),stdin);
			char useless = getchar();
			if (strlen(pass) != 4)
			{
				Set_Cursor_And_Position(40, 6);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 6);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 6);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("是否打卡(0 or 1)：");
			int temp = scanf("%d", &w_clock);
			temp = getchar();
			if (w_clock < 0 || w_clock >1)
			{
				Set_Cursor_And_Position(40, 7);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 7);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 7);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("是否迟到(0 or 1)：");
			int temp = scanf("%d", &w_be_l);
			temp = getchar();
			if (w_be_l < 0 || w_be_l > 1)
			{
				Set_Cursor_And_Position(40, 8);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 8);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 8);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("迟到数(>0)：");
			int temp = scanf("%d", &n_be_l);
			temp = getchar();
			if (n_be_l < 0)
			{
				Set_Cursor_And_Position(40, 9);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 9);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 9);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("打卡数(>0)：");
			int temp = scanf("%d", &n_c);
			temp = getchar();
			if (n_c < 0)
			{
				Set_Cursor_And_Position(40, 10);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 10);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 10);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("请假数(>0)：");
			int temp = scanf("%d", &n_a_v);
			temp = getchar();
			if (n_a_v < 0 || n_a_v >1)
			{
				Set_Cursor_And_Position(40, 11);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 11);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 11);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("剩余年假(>0)：");
			int temp = scanf("%d", &r_v);
			temp = getchar();
			if (r_v < 0)
			{
				Set_Cursor_And_Position(40, 12);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 12);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 12);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("已用假期(>0)：");
			int temp = scanf("%d", &h_v);
			temp = getchar();
			if (h_v < 0)
			{
				Set_Cursor_And_Position(40, 13);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 13);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 13);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;

		while (1)
		{
			printf("请假状态(0非请假 11事假 12病假)：");
			int temp = scanf("%d", &a_v_s);
			temp = getchar();
			if (a_v_s < 0)
			{
				Set_Cursor_And_Position(40, 14);
				printf("输入无效 请输入1重新输入或输入0退出 ");
				int judge = -1;
				int temp = scanf("%d", &judge);
				temp = getchar();
				if (judge == 0)
				{
					flag = 1;
					break;
				}
				Set_Cursor_And_Position(40, 14);
				printf("                                                   ");
				Set_Cursor_And_Position(0, 14);
			}
			else
				break;
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;
		// 创建新员工节点
		Employees *newEmp = (Employees *)malloc(sizeof(Employees));
		if (newEmp == NULL)
		{
			printf("内存分配失败！\n");
			exit(1);
		}

		// 拷贝员工信息
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
		newEmp->taken_vacation = h_v;
		newEmp->remaining_annual_vacation = r_v;
		newEmp->ask_vacation_status = a_v_s;

		strcpy(newEmp->time_of_clock, tm_of_c);
		strcpy(newEmp->time_of_leave, tm_of_l);
		newEmp->total_annual_vacation = t_v;


		newEmp->next = NULL;

		// 插入到对应部门的链表中
		Employees *move = com.head;

		// 如果链表为空，直接将新节点作为头节点
		if (move == NULL)
		{
			com.head = newEmp;
		}
		else
		{
			// 遍历链表，将新节点插入到链表末尾
			while (move->next != NULL)
			{
				move = move->next;
			}
			move->next = newEmp;
		}

		com.num_of_staff++;

		printf("员工信息已成功添加到部门 %s\n", departments[department_num - 1]);
		Complete_job_num();
		flag = Exit_with_Flag(flag);
		if (flag == 1)
		{
			system("cls");
			break;
		}
	}
	Save();
}

void DeleteStaff() // 删除员工
{
	system("cls");
	char j_num[8] = { '\0' };
	printf("请输入要删除的员工的工号: ");
	fgets(j_num, sizeof(j_num), stdin);
	char useless = getchar();
	int found = 0; // 标记是否找到员工
	for (int i = 0; i < 4; i++) // 遍历所有部门
	{
		Employees *prev = NULL; // 前驱节点
		Employees *curr = com[i].head; // 当前节点

		while (curr != NULL) // 遍历当前部门的员工链表
		{
			if (strcmp(curr->job_num, j_num) == 0) // 找到匹配的员工
			{
				found = 1; // 标记找到员工
				if (prev == NULL) // 如果要删除的员工是链表头节点
				{
					com[i].head = curr->next; // 更新链表头为下一个节点
				}
				else // 如果要删除的员工不是链表头节点
				{
					prev->next = curr->next; // 将前驱节点的next指向当前节点的下一个节点
				}
				free(curr); // 释放当前节点内存
				com[i].num_of_staff--; // 部门员工数量减1
				printf("员工工号为 %s 的数据已成功删除。\n", j_num);
				break; // 找到并删除后退出循环
			}
			prev = curr; // 更新前驱节点
			curr = curr->next; // 移动到下一个节点
		}
		if (found) // 如果已找到并删除员工，退出部门循环
		{
			break;
		}
	}

	if (!found) // 如果遍历完所有部门仍未找到员工
	{
		printf("未找到工号为 %s 的员工数据。\n", j_num);
	}
	Sleep(commmon_time);
	Save();

}

void Modify_Seek(Companys com) // 修改员工信息
{
	system("cls");
	char j_num[8] = { '\0' };
	int find = 0;
	printf("请输入要修改的员工工号：");
	fgets(j_num,sizeof(j_num),stdin);
	char useless = getchar();
	Employees *emp = com.head;
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
	{
		printf("查无此人");
		Sleep(commmon_time);
	}
	else
		Modify(emp);
}

void Modify(Employees* emp)//修改员工信息（修改）
{
	system("cls");
	char name[4] = { '\0' };//姓名
	int department_num = 0;//所属部门编号
	int identity_num = 0;// 职位编号
	int age = 0;//年龄
	int age_w = 0;//工龄
	int stage = 0;//工作状态 1为正常工作 0为假期中
	char pass[5] = { '\0' };//四位密码
	int w_clock = 0;//是否打卡 1是 0否
	int w_be_l = 0;//是否迟到
	int n_be_l = 0;//迟到数
	int n_c = 0;//打卡次数
	int n_a_v = 0;//请假次数
	int r_v = 0;//剩余年假
	int h_v = 0;//已用假期
	int a_v_s = 0;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝
	//初始化
	strcpy(name, emp->name);
	department_num = emp->id_department;
	identity_num = emp->id_identity;
	age = emp->age;
	age_w = emp->age_of_work;
	stage = emp->stage;
	strcpy(pass, emp->password);
	w_clock=emp->Whether_clock;
	w_be_l = emp->Whether_be_late;
	n_be_l = emp->num_late;
	n_c = emp->num_clock;
	n_a_v = emp->num_ask_vacation;
	r_v = emp->remaining_annual_vacation;
	h_v = emp->taken_vacation;
	a_v_s = emp->ask_vacation_status;

	printf("以下为可手动修改信息：\n");
	printf("姓名：%s\n", emp->name);
	printf("部门：%s\n", emp->department);
	printf("职位：%s\n", emp->identity);
	printf("年龄：%d\n", emp->age);
	printf("工龄：%d\n", emp->age_of_work);
	printf("工作状态：%d\n", emp->stage);
	printf("密码：%s\n", emp->password);
	printf("是否打卡：%d\n", emp->Whether_clock);
	printf("是否迟到：%d\n", emp->Whether_be_late);
	printf("迟到次数：%d\n", emp->num_late);
	printf("打卡次数：%d\n", emp->num_clock);
	printf("请假次数：%d\n", emp->num_ask_vacation);
	printf("剩余年假：%d\n", emp->remaining_annual_vacation);
	printf("已用假期：%d\n", emp->taken_vacation);
	printf("请假状态：%d\n", emp->ask_vacation_status);
	
	Set_Cursor_And_Position(25, 0);
	printf("如果要修改当前项信息请输入y，否则请输入0");

	Set_Cursor_And_Position(25, 1);
	while (1)
	{
		int flag = 0;
		while (!_kbhit());
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 1);
			fgets(name,sizeof(name),stdin);
			char useless = getchar();
		}
		if (strlen(name) != 3 || name[0] < 'A' || name[0]>'Z' || name[1] < 'A' || name[1]>'Z' || name[2] < 'A' || name[2]>'Z')
		{
			Set_Cursor_And_Position(25, 1);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 1);
			printf("                                                   ");
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 2);
			int temp = scanf("%d", &department_num);
			temp = getchar();
		}
		if (department_num < 1 || department_num>4)
		{
			Set_Cursor_And_Position(25, 2);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 2);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 2);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 3);
			int temp = scanf("%d", &identity_num);
			temp = getchar();
		}
		if (identity_num < 1 || identity_num>3)
		{
			Set_Cursor_And_Position(25, 3);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			Set_Cursor_And_Position(25, 3);
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 3);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 3);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 4);
			int temp = scanf("%d", &age);
			temp = getchar();
		}
		if (age < 18 || age>60)
		{
			Set_Cursor_And_Position(25, 4);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			Set_Cursor_And_Position(25, 4);
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 4);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 4);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 5);
			int temp = scanf("%d", &age_w);
			temp = getchar();
		}
		if (age_w < 0)
		{
			Set_Cursor_And_Position(25, 5);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 5);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 5);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 6);
			int temp = scanf("%d", &stage);
			temp = getchar();
		}
		if (stage < 0 || stage > 1)
		{
			Set_Cursor_And_Position(25, 6);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 6);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 6);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 7);
			fgets(pass, sizeof(pass), stdin);
			char useless = getchar();
		}
		if (strlen(pass) != 4)
		{
			Set_Cursor_And_Position(25, 7);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 7);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 7);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 8);
			int temp = scanf("%d", &w_clock);
			temp = getchar();
		}
		if (w_clock < 0 || w_clock >1)
		{
			Set_Cursor_And_Position(25, 8);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 8);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 8);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 9);
			int temp = scanf("%d", &w_be_l);
			temp = getchar();
		}
		if (w_be_l < 0 || w_be_l > 1)
		{
			Set_Cursor_And_Position(25, 9);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 9);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 9);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 10);
			int temp = scanf("%d", &n_be_l);
			temp = getchar();
		}
		if (n_be_l < 0)
		{
			Set_Cursor_And_Position(25, 10);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 10);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 10);
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 11);
			int temp = scanf("%d", &n_c);
			temp = getchar();
		}
		if (n_c < 0)
		{
			Set_Cursor_And_Position(25, 11);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 12);
			int temp = scanf("%d", &n_a_v);
			temp = getchar();
		}
		if (n_a_v < 0 || n_a_v >1)
		{
			Set_Cursor_And_Position(25, 12);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 13);
			int temp = scanf("%d", &r_v);
			temp = getchar();
		}
		if (r_v<0)
		{
			Set_Cursor_And_Position(25, 13);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 14);
			int temp = scanf("%d", &h_v);
			temp = getchar();
		}
		if (h_v <0)
		{
			Set_Cursor_And_Position(25, 14);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
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
		char ch;
		ch = fgetc(stdin);
		if (ch - '0' == 0)
			break;
		if (ch == 'y')
		{
			Set_Cursor_And_Position(25, 15);
			int temp = scanf("%d", &a_v_s);
			temp = getchar();
		}
		if (a_v_s < 0)
		{
			Set_Cursor_And_Position(25, 15);
			printf("输入无效 请输入1重新输入或输入0退出 ");
			int judge = -1;
			int temp = scanf("%d", &judge);
			temp = getchar();
			if (judge == 0)
				break;
			Set_Cursor_And_Position(25, 15);
			printf("                                                   ");
			Set_Cursor_And_Position(25, 15);
		}
		else
			flag = 1;
		if (flag == 1)
			break;
	}
	while (1)
	{
		Set_Cursor_And_Position(0, 16);
		printf("请输入1确认修改，输入0取消修改 ");
		int judge = -1;
		int temp = scanf("%d", &judge);
		temp = getchar();
		if (judge == 1)
		{
			strcpy(emp->name, name);//姓名
			strcpy(emp->department, departments[department_num - 1]);
			emp->id_department = department_num;
			strcpy(emp->identity, identities[identity_num - 1]);
			emp->id_identity = identity_num;
			emp->age = age;//年龄
			emp->age_of_work = age_w;//工龄
			emp->stage = stage; //工作状态
			strcpy(emp->password, pass);//四位密码
			emp->Whether_clock = w_clock;//是否打卡
			emp->Whether_be_late = w_be_l;//是否迟到
			emp->num_late = n_be_l;//迟到数
			emp->num_clock = n_c;//打卡次数
			emp->num_ask_vacation = n_a_v;//请假次数
			emp->remaining_annual_vacation = r_v;//剩余年假
			emp->taken_vacation = h_v;//已用假期
			emp->ask_vacation_status = a_v_s;// 请假状态：0 - 未申请，1 - 已申请待审批，
			Save();
			printf("修改并保存成功\n");
			Sleep(commmon_time);
			break;
		}
		if (judge == 0)
			break;
	}
}

void ChangePassword(Employees* emp)//密码修改
{
	system("cls");
	int flag = 0;
	while (1) 
	{
		char pass1[5] = { '\0' }, pass2[5] = { '\0' };
		printf("请输入原密码：\n");
		fgets(pass1, sizeof(pass1), stdin);
		char useless = getchar();
		if (strcmp(pass1, emp->password) == 0)
		{
			printf("请输入新密码：\n");
			fgets(pass1, sizeof(pass1), stdin);
			useless = getchar();
			printf("请再次输入新密码：\n");
			fgets(pass2, sizeof(pass2), stdin);
			useless = getchar();

			if (strcmp(pass1, pass2) == 0)
			{
				strcpy(emp->password, pass1);
				printf("密码修改成功。\n");
				Sleep(commmon_time);
				flag = 1;
			}
			else
			{
				printf("两次输入新密码不同。\n");
				printf("请按r重输或按0退出\n");
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
			printf("原密码错误。\n");
			printf("请按r重输或按0退出\n");
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

void RequestVacation(Employees* emp) //假期申请函数
{
	while (1)
	{
		int pick, flag = 0;
		system("cls");
		printf("------------------------------\n");
		printf("|         1.请假申请          |\n");
		printf("|         2.取消申请          |\n");
		printf("|         0.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
			case 1:
			{
				if (emp->stage == 0)
				{
					printf("%s %s 已经在假期中，无法再次申请假期。\n", emp->identity, emp->name);
					return;
				}
				if (emp->ask_vacation_status == 0)
				{
					while (1)
					{
						int pick1 = -1, flag = 0;
						system("cls");
						printf("-------------------------------\n");
						printf("|         1.病假              |\n");
						printf("|         2.事假              |\n");
						printf("|         0.退出              |\n");
						printf("-------------------------------\n");
						int temp1 = scanf("%d", &pick1);
						switch (pick1)
						{
							case 1:
								{
									emp->ask_vacation_status = 11; // 设置为已申请待审批状态
									printf("%s %s 已成功申请病假\n", emp->identity, emp->name);
									flag = 1;
								}break;
							case 2:
								{
									emp->ask_vacation_status = 12; // 设置为已申请待审批状态
									printf("%s %s 已成功申请事假。\n", emp->identity, emp->name);
									flag = 1;
								}break;
							case 3:flag = 1; system("cls"); break;
						}
						if (flag==1)
							break;
					}
				}
				else if (emp->ask_vacation_status == 11 || emp->ask_vacation_status == 12)
				{
					printf("%s %s 申请待审批中。\n", emp->identity, emp->name);
				}
				else if (emp->ask_vacation_status == 2)
				{
					emp->stage = 0;
					printf("%s %s 申请通过。\n", emp->identity, emp->name);
				}
				else if (emp->ask_vacation_status == 3)
				{
					emp->stage = 0;
					printf("%s %s 申请被拒绝。\n", emp->identity, emp->name);
				}
			}Sleep(commmon_time); system("cls"); break;
			case 2: emp->ask_vacation_status = 0; printf("已成功取消申请。\n"); Sleep(commmon_time); system("cls"); break;
			case 0: flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); Save(); break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
		{
			system("cls");
			break;
		}
	}

}

void Vacation_Management(Employees* emp) //批准职员的请假申请
{
	system("cls");
	Employees *emp_s;
	int flag = 0,judge;
	emp_s = com[emp->id_department - 1].head;
	while (emp_s != NULL)
	{
		if (emp_s->ask_vacation_status == 11 || emp_s->ask_vacation_status == 12)
		{
			if (emp_s->id_identity == 3)
			{
				printf("如果同意申请，请输入1\n");
				printf("如果拒绝申请，请输入2\n");
				printf("如果要退出审批，请输入0\n");
				printf("姓名：%s\n", emp_s->name);
				printf("工号：%s\n", emp_s->job_num);
				printf("职务：%s\n", identities[emp_s->id_identity - 1]);
				if (emp_s->ask_vacation_status == 11)
					printf("请假类型：事假\n");
				if (emp_s->ask_vacation_status == 12)
					printf("请假类型：病假\n");
				int temp = scanf("%d", &judge);
				switch (judge)
				{
					case 1:emp_s->ask_vacation_status = 2; printf("已同意申请=\n"); system("cls"); ; break;
					case 2:emp_s->ask_vacation_status = 3; printf("已拒绝申请=\n"); system("cls"); ; break;
					case 0:flag = 1; system("cls"); break;
					default: printf("请重新选择"); Sleep(commmon_time); break;
				}
			}
		}
		emp_s = emp_s->next;
		if (flag == 1)
			break;
	}
	Save();
	printf("已全部处理。\n");
	Sleep(commmon_time);
	system("cls");
}

Employees* createNewNode(Employees* originalNode) //创建新的链表节点，用来排序输出
{
	Employees* newNode = (Employees*)malloc(sizeof(Employees));
	if (newNode == NULL) {
		printf("内存分配失败！\n");
		exit(1);
	}
	*newNode = *originalNode;  // 复制原节点的数据
	newNode->next = NULL;      // 新节点的 next 指针初始化为 NULL
	return newNode;
}

Employees* getMiddle(Employees* head)// 找到链表的中间节点
{
	if (head == NULL) return head;

	Employees* slow = head;        // 慢指针，每次移动一步
	Employees* fast = head;        // 快指针，每次移动两步

	while (fast->next != NULL && fast->next->next != NULL) {
		slow = slow->next;          // 慢指针移动一步
		fast = fast->next->next;    // 快指针移动两步
	}

	return slow;  // 当快指针到达链表末尾时，慢指针指向中间节点
}

Employees* mergeByClockTimes(Employees* left, Employees* right) // 归并两个链表，按打卡次数升序（打卡的单一排序）
{
	if (left == NULL) return right; // 如果左链表为空，返回右链表
	if (right == NULL) return left; // 如果右链表为空，返回左链表

	if (left->num_clock <= right->num_clock) {
		Employees* newNode = createNewNode(left); // 创建新节点
		newNode->next = mergeByClockTimes(left->next, right); // 递归合并
		return newNode;
	}
	else {
		Employees* newNode = createNewNode(right); // 创建新节点
		newNode->next = mergeByClockTimes(left, right->next); // 递归合并
		return newNode;
	}
	
}

Employees* mergeSortByClockTimes(Employees* head) // 归并排序主函数，按打卡次数升序

{
	if (head == NULL || head->next == NULL) {
		return createNewNode(head); // 如果链表为空或只有一个节点，直接返回新节点
	}

	Employees* middle = getMiddle(head); // 找到链表的中间节点
	Employees* nextOfMiddle = middle->next;

	middle->next = NULL; // 将链表从中间节点处分割成两部分

	Employees* left = mergeSortByClockTimes(head); // 递归地对左半部分进行排序
	Employees* right = mergeSortByClockTimes(nextOfMiddle); // 递归地对右半部分进行排序

	return mergeByClockTimes(left, right); // 合并两个有序链表
}

Employees* mergeByVacationTimes(Employees* left, Employees* right) //归并两个链表，按请假次数升序（请假的单一排序）
{
	if (left == NULL) return right; // 如果左链表为空，返回右链表
	if (right == NULL) return left; // 如果右链表为空，返回左链表

	if (left->num_ask_vacation <= right->num_ask_vacation) {
		Employees* newNode = createNewNode(left); // 创建新节点
		newNode->next = mergeByVacationTimes(left->next, right); // 递归合并
		return newNode;
	}
	else {
		Employees* newNode = createNewNode(right); // 创建新节点
		newNode->next = mergeByVacationTimes(left, right->next); // 递归合并
		return newNode;
	}
}

Employees* mergeSortByVacationTimes(Employees* head)////归并主函数，按请假次数升序（请假的单一排序）
{
	if (head == NULL || head->next == NULL) {
		return createNewNode(head); // 如果链表为空或只有一个节点，直接返回新节点
	}

	Employees* middle = getMiddle(head); // 找到链表的中间节点
	Employees* nextOfMiddle = middle->next;

	middle->next = NULL; // 将链表从中间节点处分割成两部分

	Employees* left = mergeSortByVacationTimes(head); // 递归地对左半部分进行排序
	Employees* right = mergeSortByVacationTimes(nextOfMiddle); // 递归地对右半部分进行排序

	return mergeByVacationTimes(left, right); // 合并两个有序链表
}

Employees* mergeByMultipleAttributes(Employees* left, Employees* right) // 归并两个链表，如果请假次数相同，再按打卡次数排序,最后再按名字排序
{
	if (left == NULL) return right; // 如果左链表为空，返回右链表
	if (right == NULL) return left; // 如果右链表为空，返回左链表

	Employees* result = NULL; // 用于存储合并后的链表头指针

	// 比较请假次数
	if (left->num_ask_vacation < right->num_ask_vacation) {
		result = createNewNode(left); // 创建新节点
		result->next = mergeByMultipleAttributes(left->next, right); // 递归合并
	}
	else if (left->num_ask_vacation > right->num_ask_vacation) {
		result = createNewNode(right); // 创建新节点
		result->next = mergeByMultipleAttributes(left, right->next); // 递归合并
	}
	else {
		// 请假次数相等，比较打卡次数
		if (left->num_clock < right->num_clock) {
			result = createNewNode(left); // 创建新节点
			result->next = mergeByMultipleAttributes(left->next, right); // 递归合并
		}
		else if (left->num_clock > right->num_clock) {
			result = createNewNode(right); // 创建新节点
			result->next = mergeByMultipleAttributes(left, right->next); // 递归合并
		}
		else {
			// 打卡次数也相等，比较名字
			if (strcmp(left->name, right->name) < 0) {
				result = createNewNode(left); // 创建新节点
				result->next = mergeByMultipleAttributes(left->next, right); // 递归合并
			}
			else {
				result = createNewNode(right); // 创建新节点
				result->next = mergeByMultipleAttributes(left, right->next); // 递归合并
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

void ManagerSort(Employees* emp)//部门经理的排序函数
{
	int flag = 0;
	while (1)
	{
		int pick;
		system("cls");
		printf("-------------------------------\n");
		printf("|         1.打卡次数          |\n");
		printf("|         2.请假次数          |\n");
		printf("|         3.多重排序          |\n");
		printf("|         4.最佳员工          |\n");
		printf("|         0.退出排序          |\n");
		printf("-------------------------------\n");
		int temp = scanf("%d", &pick);

		switch (pick)
		{
			case 1:
				{
					system("cls");
					com[emp->id_department - 1].head = mergeSortByClockTimes(com[emp->id_department - 1].head);
					printf("本部门员工信息已按打卡次数升序排序。\n");
					Manager_Sorted_Print(com[emp->id_department - 1].head, "打卡次数");
				}break;
			case 2:
				{
					// 按请假次数排序
					system("cls");
					com[emp->id_department - 1].head = mergeSortByVacationTimes(com[emp->id_department - 1].head);
					printf("本部门员工信息已按请假次数升序排序。\n");
					Manager_Sorted_Print(com[emp->id_department - 1].head, "请假次数");
					
				} break;
			case 3:
				{
					// 按请假次数、打卡次数和名字排序
					system("cls");
					com[emp->id_department - 1].head = mergeSortByMultipleAttributes(com[emp->id_department - 1].head);
					printf("本部门员工信息已按请假次数、打卡次数和名字排序。\n");
					Manager_Sorted_Print(com[emp->id_department - 1].head, "请假、打卡次数和名字");
				} break;
			case 4:
				{
					// 查找并打印最佳员工
					system("cls");
					Find_And_Print_BestEmployees(com[emp->id_department - 1].head);
				} break;
			case 0:system("cls"); flag = 1; break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
			break;
	}
}

void Manager_Sorted_Print(Employees* head, const char* sortBy)//部门经理 打印排序后的信息
{
	int flag = 0;
	if (head == NULL)
	{
		printf("没有员工信息可显示。\n");
		flag=1;
	}
	else
	{
		while (1)
		{
			if (strcmp(sortBy, "请假、打卡次数和名字") == 0)
			{
				printf("-------------------------------------\n");
				printf("| 姓名 | %s       |\n", sortBy);
				printf("-------------------------------------\n");

				Employees *current = head;
				while (current != NULL)
				{
					if (strcmp(sortBy, "打卡次数") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_clock);
					}
					else if (strcmp(sortBy, "请假次数") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_ask_vacation);
					}
					else if (strcmp(sortBy, "请假、打卡次数和名字") == 0)
					{
						printf("| %-4s | 请假次数: %-3d 打卡次数: %-3d|\n", current->name, current->num_ask_vacation, current->num_clock);
					}
					current = current->next;
				}
				printf("-------------------------------------\n");
				while (1)
				{
					printf("按零退出\n");
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
				printf("| 姓名 | %s |\n", sortBy);
				printf("-------------------\n");

				Employees *current = head;
				while (current != NULL)
				{
					if (strcmp(sortBy, "打卡次数") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_clock);
					}
					else if (strcmp(sortBy, "请假次数") == 0)
					{
						printf("| %-4s | %-8d |\n", current->name, current->num_ask_vacation);
					}
					else if (strcmp(sortBy, "请假、打卡次数和名字") == 0)
					{
						printf("| %-4s | 请假次数: %-3d 打卡次数: %-3d 姓名: %-4s |\n", current->name, current->num_ask_vacation, current->num_clock, current->name);
					}
					current = current->next;
				}
				printf("-------------------\n");
				while (1)
				{
					printf("按零退出\n");
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

void AdminPrintSortedEmployees(Employees *head, const char *sortBy)//管理员 打印排序后的数据
{
	system("cls");
	if (head == NULL)
	{
		printf("没有员工信息可显示。\n");
		return;
	}
	int flag = 0;
	while (1)
	{
		if (strcmp(sortBy, "请假、打卡次数和名字") == 0)
		{
			printf("-------------------------------------\n");
			printf("| 姓名 | %s       |\n", sortBy);
			printf("-------------------------------------\n");

			Employees *current = head;
			while (current != NULL)
			{
				if (strcmp(sortBy, "打卡次数") == 0)
				{
					printf("| %-4s | %-8d |\n", current->name, current->num_clock);
				}
				else if (strcmp(sortBy, "请假次数") == 0)
				{
					printf("| %-4s | %-8d |\n", current->name, current->num_ask_vacation);
				}
				else if (strcmp(sortBy, "请假、打卡次数和名字") == 0)
				{
					printf("| %-4s | 请假次数: %-3d 打卡次数: %-3d|\n", current->name, current->num_ask_vacation, current->num_clock);
				}
				current = current->next;
			}
			printf("-------------------------------------\n");
			int flag1 = -1;
			while (1)
			{
				printf("按零退出\n");
				while (!_kbhit());
				char ch = _getch();
				if (ch - '0' == 0)
				{
					flag1 = 1;
					flag = 1;
				}
				if (flag1 == 1)
					break;
			}
		}
		else
		{
			printf("-----------------------------\n");
			printf("| 部门 | 姓名 | %s |\n", sortBy);
			printf("-----------------------------\n");

			Employees *current = head;
			while (current != NULL)
			{
				if (strcmp(sortBy, "打卡次数") == 0)
				{
					printf("| %-6s | %-4s | %-8d |\n", current->department, current->name, current->num_clock);

				}
				else if (strcmp(sortBy, "请假次数") == 0)
				{
					printf("| %-6s | %-4s | %-8d |\n", current->department, current->name, current->num_ask_vacation);
				}
				else if (strcmp(sortBy, "请假、打卡次数和名字") == 0)
				{
					printf("| %-6s | %-4s | 请假次数: %-3d 打卡次数: %-3d 姓名: %-4s |\n", current->department, current->name, current->num_ask_vacation, current->num_clock, current->name);
				}
				current = current->next;
			}
			printf("-----------------------------\n");
			int flag1 = -1;
			while (1)
			{
				printf("按零退出\n");
				while (!_kbhit());
				char ch = _getch();
				if (ch - '0' == 0)
				{
					flag1 = 1;
					flag = 1;
				}
				if (flag1 == 1)
					break;
			}
		}
		if (flag == 1)
			break;
	}
}

void AdminSort(void)//管理员的排序函数
{
	int flag = 0;
	int sortOption;
	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.打卡次数          |\n");
		printf("|         2.请假次数          |\n");
		printf("|         3.多重排序          |\n");
		printf("|         4.最佳员工          |\n");
		printf("|         0.退出排序          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &sortOption);

		switch (sortOption)
		{
			case 1:
				{
					// 按打卡次数排序
					Employees *allEmployees = NULL;
					Employees *tail = NULL;

					// 合并所有部门的员工信息到一个链表中
					for (int i = 0; i < 4; i++)
					{
						Employees *current = com[i].head;
						while (current != NULL)
						{
							Employees *newNode = createNewNode(current);
							if (allEmployees == NULL)
							{
								allEmployees = newNode;
								tail = newNode;
							}
							else
							{
								tail->next = newNode;
								tail = newNode;
							}
							current = current->next;
						}
					}

					// 对合并后的链表进行排序
					allEmployees = mergeSortByClockTimes(allEmployees);

					// 打印排序后的员工信息
					AdminPrintSortedEmployees(allEmployees, "打卡次数");

					// 释放临时链表
					while (allEmployees != NULL)
					{
						Employees *temp = allEmployees;
						allEmployees = allEmployees->next;
						free(temp);
					}
				} break;
			case 2:
				{
					// 按请假次数排序
					Employees *allEmployees = NULL;
					Employees *tail = NULL;

					// 合并所有部门的员工信息到一个链表中
					for (int i = 0; i < 4; i++)
					{
						Employees *current = com[i].head;
						while (current != NULL)
						{
							Employees *newNode = createNewNode(current);
							if (allEmployees == NULL)
							{
								allEmployees = newNode;
								tail = newNode;
							}
							else
							{
								tail->next = newNode;
								tail = newNode;
							}
							current = current->next;
						}
					}

					// 对合并后的链表进行排序
					allEmployees = mergeSortByVacationTimes(allEmployees);

					// 打印排序后的员工信息
					AdminPrintSortedEmployees(allEmployees, "请假次数");

					// 释放临时链表
					while (allEmployees != NULL)
					{
						Employees *temp = allEmployees;
						allEmployees = allEmployees->next;
						free(temp);
					}
				} break;
			case 3:
				{
					// 按请假次数、打卡次数和名字排序
					Employees *allEmployees = NULL;
					Employees *tail = NULL;

					// 合并所有部门的员工信息到一个链表中
					for (int i = 0; i < 4; i++)
					{
						Employees *current = com[i].head;
						while (current != NULL)
						{
							Employees *newNode = createNewNode(current);
							if (allEmployees == NULL)
							{
								allEmployees = newNode;
								tail = newNode;
							}
							else
							{
								tail->next = newNode;
								tail = newNode;
							}
							current = current->next;
						}
					}

					// 对合并后的链表进行排序
					allEmployees = mergeSortByMultipleAttributes(allEmployees);

					// 打印排序后的员工信息
					AdminPrintSortedEmployees(allEmployees, "请假、打卡次数和名字");

					// 释放临时链表
					while (allEmployees != NULL)
					{
						Employees *temp = allEmployees;
						allEmployees = allEmployees->next;
						free(temp);
					}
				} break;
			case 4:
				{
					// 查找并打印最佳员工
					Employees *allEmployees = NULL;
					for (int i = 0; i < 4; i++)
					{
						Employees *temp = com[i].head;
						while (temp != NULL)
						{
							Employees *newNode = createNewNode(temp);
							newNode->next = allEmployees;
							allEmployees = newNode;
							temp = temp->next;
						}
					}
					Find_And_Print_BestEmployees(allEmployees);
					// 释放临时链表
					while (allEmployees != NULL)
					{
						Employees *temp = allEmployees;
						allEmployees = allEmployees->next;
						free(temp);
					}
				} break;
			case 0:flag = 1;system("cls");break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag)
			break;
	}
}

void Find_And_Print_BestEmployees(Employees *head)// 查找并打印所有最佳员工
{
	int flag = 0;
	while (1)
	{
		int maxClock = 0;
		int minVacation = INT_MAX;
		Employees *emp = head;
		int bestEmployeeCount = 0;

		// 第一次遍历，找到最大打卡次数和最小请假次数
		while (emp != NULL)
		{
			if (emp->num_late == 0)
			{ // 迟到数为0
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

		// 第二次遍历，打印所有符合条件的最佳员工
		emp = head;
		system("cls");
		printf("最佳员工信息：\n");
		printf("------------------------------------------------\n");
		printf("|姓名\t工号\t    打卡次数\t请假次数       |\n");
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
			printf("没有符合条件的最佳员工。\n");
		}
		else
		{
			printf("共找到 %d 名最佳员工。\n", bestEmployeeCount);
		}
		flag = Exit_with_Flag(flag);
		if (flag == 1)
			break;
	}
}

void Information_Management(Employees *emp)
{
	char pass[5] = { '\0' };
	printf("请再次输入密码：");
	fgets(pass, sizeof(pass), stdin);
	char useless = getchar();
	if (strcmp(emp->password, pass) == 0)
	{
		int flag = 0, pick = -1;
		while (1)
		{
			system("cls");
			printf("------------------------------\n");
			printf("|         1.采购部门          |\n");
			printf("|         2.生产部门          |\n");
			printf("|         3.出售部门          |\n");
			printf("|         4.管理部门          |\n");
			printf("|         0.退出管理          |\n");
			printf("------------------------------\n");
			int temp = scanf("%d", &pick);
			switch (pick)
			{
				case 1:Information_Management_1(com[0]); break;
				case 2:Information_Management_1(com[1]); break;
				case 3:Information_Management_1(com[2]); break;
				case 4:Information_Management_1(com[3]); break;
				case 0:flag = 1; system("cls"); break;
				default: printf("请重新选择"); Sleep(commmon_time); break;
			}
			if (flag == 1)
				break;
		}
	}
	else
	{
		printf("密码错误\n");
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
		printf("%s：\n", com.department);
		printf("员工数：%d\n", com.num_of_staff);
		printf("------------------------------\n");
		printf("|         1.修改信息          |\n");
		printf("|         2.添加员工          |\n");
		printf("|         3.删除员工          |\n");
		printf("|         0.退出管理          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
			case 1:Modify_Seek(com); break;
			case 2:InputStaff(com); break;
			case 3:DeleteStaff();
			case 0:flag = 1; system("cls"); break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
			break;
	}
}

void System_maintenance(void)//系统维护
{
	system("cls");
	Save();
	char filename[20] = { '\0' };
	FILE *newFile = fopen("new.txt", "w");
	if (newFile == NULL)
	{
		printf("无法打开临时文件\n");
		Sleep(error_time);
		exit(1);
	}
	for (int i = 0; i < 4; i++)
	{
		Employees *emp = com[i].head;
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
	struct tm *local_time = localtime(&current_time);
	snprintf(filename, sizeof(filename), "data%d.%d.txt", local_time->tm_mon + 1, local_time->tm_mday);
	int team = rename("data.txt", filename);
	team = rename("new.txt", "data.txt");
	printf("成功保存当日数据");
	Sleep(commmon_time);
}

void Annual_leave_allocation(void)//分配年假
{
	for(int i=0;i<4;i++)
	{ 
		Employees *emp;
		emp = com[i].head;
		while (emp!=NULL)
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

void Stats(Employees *emp_m)
{
	int flag = 0, pick = -1;
	Employees *emp;
	emp = com[emp_m->id_department - 1].head;
	while (1)
	{
		system("cls");
		printf("------------------------------\n");
		printf("|         1.打卡统计          |\n");
		printf("|         2.迟到统计          |\n");
		printf("|         3.年龄统计          |\n");
		printf("|         4.状态统计          |\n");
		printf("|         0.退出统计          |\n");
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
					printf("今日本部门有%d人未打卡", count);
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
					printf("今日本部门有%d人迟到", count);
					Sleep(commmon_time);
				}break;
			case 3:
				{
					int age = 0;
					printf("请输入一个分界年龄");
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
					printf("等于%d岁的人有%d个\n", age,count);
					printf("小于%d岁的人有%d个\n", age, count_less);
					printf("大于%d岁的人有%d个\n", age, count_more);
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
					printf("今日本部门有%d人休假", count);
					Sleep(commmon_time);
				}break;
			case 0:flag = 1; system("cls"); break;
			default: printf("请重新选择"); Sleep(commmon_time); break;
		}
		if (flag == 1)
			break;
	}
}