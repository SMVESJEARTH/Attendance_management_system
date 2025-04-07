#include"variable.h"
#include"fun.h"

void Save(void)//数据保存
{
	char line[101] = { '\0' };

	FILE *newFile = fopen("temp.txt", "w");
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
			fprintf(newFile, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d %d %d\n",
				emp->name, emp->job_num, emp->id_department, emp->id_identity, emp->age, emp->age_of_work, emp->stage, emp->password, emp->Whether_clock,
				emp->time_of_clock, emp->time_of_leave, emp->Whether_be_late, emp->num_late,emp->num_clock,emp->num_ask_vacation, emp->total_annual_vacation, emp->taken_annual_vacation,
				emp->remaining_annual_leave,emp->vacation_status);
			emp = emp->next;
		}
	}
	fclose(newFile);
	remove("data.txt");
	int useless = rename("temp.txt", "data.txt");
	printf("-数据已保存\n");
}

Employees * CreatAndRead_employees(int i)//创建链表与读取数据
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
    char tm_of_c[20] = { '\0' };//打卡时间
	char tm_of_l[20] = { '\0' };//离开时间
    int w_be_l = 0;//是否迟到
    int n_be_l = 0;//迟到数
	int n_c = 0;//打卡次数
	int n_a_v = 0;//请假次数
    int t_v = 0;//总年假
    int h_v = 0;//已用年假
    int r_v = 0;//剩余年假
	int v_s = 0;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝

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
		&w_clock, tm_of_c, tm_of_l,&w_be_l,&n_be_l,&n_c,&n_a_v,&t_v,&h_v,&r_v,&v_s) == 19)//每一行有19个数据 所以fscanf返回值为19
	{
		if (department_num == i + 1)//程序中的部门索引是0~3 而文件和手动输入的部门索引是1~4，故加1
		{
			p1 = (Employees *)malloc(sizeof(Employees));//开辟内存
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
            p1->taken_annual_vacation = h_v;//已用年假
            p1->remaining_annual_leave = r_v;//剩余年假
			p1->vacation_status = v_s;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝

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
		for (int j=0;emp != NULL;j++)
		{
            strcpy(emp->job_num, emp->name);
            emp->job_num[3] = emp->id_department + '0';
            emp->job_num[4] = emp->id_identity + '0';
			if (j < 9)
			{
				emp->job_num[5] ='0';
				emp->job_num[6] = j + 1 + '0';
				emp->job_num[7] = '\0';
			}
			else
			{
				int temp = j + 1;
				emp->job_num[6] = temp%10 + '0';
				temp = temp / 10;
				emp->job_num[5] = temp + '0';
				emp->job_num[7] = '\0';
			}
			emp = emp->next;
		}
	}
	
}

Employees *LoginAndUi(void)//登录系统
{
	system("cls");
	char j_n[8] = { '\0' };
	char pass[6] = { '\0' };
	printf("请登录\n");
	printf("工号：");
	gets(j_n);
	for(int j=0;j<3;j++)
	{
		printf("密码：");
		gets(pass);
		bool flag = 0;
		for (int i = 0; i < 4; i++)
		{
			Employees *emp = com[i].head;
			while (emp != NULL)
			{
				if (!strcmp(emp->job_num, j_n)&& !strcmp(emp->password, pass))
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
		printf("密码错误,请重新输入");
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
	printf("连续错误三次，请联系管理员核对工号或密码\n");
	exit(1);
}

void Select_clock(Employees *emp)//打卡选择
{
	int pick;
	system("cls");
	while (1)
	{
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

				int temp = sprintf(emp->time_of_leave, "%d-%02d-%02d.%d:%02d",
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
			if (emp->Whether_clock == 1)
			{
				time_t current_time = time(NULL);
				struct tm *local_tm;
				local_tm = localtime(&current_time);
				printf("下班时间：%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
					local_tm->tm_hour, local_tm->tm_min);

				int temp = sprintf(emp->time_of_leave, "%d-%02d-%02d.%d:%02d",
					local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday, local_tm->tm_hour, local_tm->tm_min);

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

		case 0:	system("cls"); flag = 1; break;

		}
		if (flag == 1)
			break;
	}
}

void Information_inquiry(Employees *emp)//信息查询
{
	int flag = 1;
	system("cls");

	FILE *fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("无法data文件\n");
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
	int h_v = 0;//已用年假
	int r_v = 0;//剩余年假
	int v_s = 0;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝

	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d %d %d",
		name, j_num, &department_num, &identity_num, &age, &age_w, &stage, pass,
		&w_clock, tm_of_c, tm_of_l, &w_be_l, &n_be_l, &n_c, &n_a_v, &t_v, &h_v, &r_v, &v_s) == 19)
	{
		if (strcmp(emp->job_num, j_num) == 0)
			break;
	}

	while (1)
	{
		printf("以下为你的个人信息；\n");
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
		printf("已用年假：%d\n", h_v);
		printf("剩余年假：%d\n", r_v);
		printf("请假状态：%d\n", v_s);

		printf("--输入'p'显示密码--\n");
		printf("--输入0退出--\n");
		while (1)
		{
			while (!_kbhit()){}
			char ch = _getch();
			if (ch == 'p')
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD coord1 = { (SHORT)6, (SHORT)7 };
				SetConsoleCursorPosition(hConsole, coord1);
				printf("%s", pass);
				Sleep(commmon_time);
				COORD coord2 = { (SHORT)6, (SHORT)7 };
				SetConsoleCursorPosition(hConsole, coord1);
				printf("****");
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

void StaffAndUi(Employees *emp)//员工
{
	system("cls");
	int pick = 0;
	int flag = 0;
	while (1)
	{
		if (flag == 1)
			break;
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
			case 1:Select_clock(emp); break;
			case 2:Information_inquiry(emp); break;
			case 0:flag = 1; system("cls"); printf("退出登录成功\n");Sleep(commmon_time); break;
		}
	}
}


    


