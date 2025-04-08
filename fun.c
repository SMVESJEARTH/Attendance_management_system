#include"variable.h"
#include"fun.h"


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
				emp->time_of_clock, emp->time_of_leave, emp->Whether_be_late, emp->num_late,emp->num_clock,emp->num_ask_vacation, emp->total_annual_vacation, emp->taken_annual_vacation,
				emp->remaining_annual_vacation,emp->ask_vacation_status);
			emp = emp->next;
		}
	}
	fclose(newFile);
	remove("data.txt");
	int useless = rename("temp.txt", "data.txt");
	printf("-数据已保存\n");
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
    int h_v = 0;//已用年假
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
            p1->taken_annual_vacation = h_v;//已用年假
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
	system("cls");
	char j_n[8] = { '\0' };
	char pass[6] = { '\0' };
	printf("请登录\n");
	printf("工号：");
	gets(j_n);
	for (int j = 0; j < 3; j++)
	{
		printf("密码：");
		gets(pass);
		bool flag = 0;
		for (int i = 0; i < 4; i++)
		{
			Employees* emp = com[i].head;
			while (emp != NULL)
			{
				if (!strcmp(emp->job_num, j_n) && !strcmp(emp->password, pass))
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

		case 0:	system("cls"); flag = 1; Save(); break;

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
	int h_v = 0;//已用年假
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

void Information_Inquiry_Department(Employees *emp)
{
	system("cls");
	Employees *emp_s;
	int flag = 0, judge;
	emp_s = com[emp->id_department - 1].head;
}

void Staff_And_Ui(Employees *emp)//员工功能
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
			case 2:Information_Inquiry_Individual(emp); break;
			case 3: RequestVacation(emp); break;
			case 4:ChangePassword(emp); break;
			case 0:flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); system("cls"); ; Save(); break;
		}
	}
}

void Manager_And_Ui(Employees* emp) //部门经理功能
{
	system("cls");
	int pick = 0;
	int flag = 0;
	int days = 0;
	while (1) {
		if (flag == 1)
			break;
		printf("------------------------------\n");
		printf("|         1.打卡选择          |\n");
		printf("|         2.个人查询          |\n");
		printf("|         3.部门查询          |\n");
		printf("|         4.审批请假          |\n");
		printf("|         5.修改密码          |\n");
		printf("|         0.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1: Select_clock(emp); break;
		case 2: Information_Inquiry_Individual; break;
		case 3: Vacation_Management(emp); break;
		case 4:Information_Inquiry_Individual(emp); break;
		case 5: ChangePassword(emp); break;
	
		case 0:flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); system("cls"); ; Save(); break;
		}
	}
}

void Admin_And_Ui(Employees* emp)//管理员功能
{
	system("cls");
	int pick = 0;
	int flag = 0;
	while (1) {
		if (flag == 1)
			break;
		printf("------------------------------\n");
		printf("|         1.系统维护          |\n");
		printf("|         2.信息查询          |\n");
		printf("|         3.信息管理          |\n");
		printf("|         4.修改密码          |\n");
		printf("|         0.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick) {
		case 1:  break;
		case 2:  break;
		case 3: break;
		case 4: break;
		case 0:flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); system("cls"); ; Save(); break;
		}
	}
}

void InputStaff() //添加员工
{
	int flag = 1;
	while(1)
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
		int h_v = 0;//已用年假
		int r_v = 0;//剩余年假
		int a_v_s = 0;// 请假状态：0 - 未申请，1 - 已申请待审批，2 - 已批准，3 - 已拒绝
		int temp;
		
		// 输入员工信息
		printf("请输入员工信息\n");
		while (1)
		{
			printf("姓名（不超过3个字符）：");
			temp = scanf("%s", name);
			if (strlen(name) != 3||name[0]<'A'||name[0]>'Z' || name[1] < 'A' || name[1]>'Z' || name[2] < 'A' || name[2]>'Z')
			{
				printf("姓名无效 请按1重新输入或按0退出\n");
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
		while (1)
		{
			printf("部门编号（1-Purchase, 2-Produce, 3-Sale, 4-Manage）：");
			temp = scanf("%d", &department_num);
			if (identity_num < 1 || identity_num > 4)
			{
				printf("部门编号无效 请按1重新输入或按0退出\n");
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
		while (1)
		{
			printf("职位编号（1-Admin, 2-Manager, 3-Staff）：");
			temp = scanf("%d", &identity_num);
			if (identity_num < 1 || identity_num > 3)
			{
				printf("职位编号无效 请按1重新输入或按0退出\n");
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
		while (1)
		{
			printf("年龄：");
			temp = scanf("%d", &age);
			if (age < 18 || age > 60)
			{
				printf("年龄无效 请按1重新输入或按0退出\n");
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
		newEmp->Whether_clock = clock;
		strcpy(newEmp->time_of_clock, tm_of_c);
		strcpy(newEmp->time_of_leave, tm_of_l);
		newEmp->Whether_be_late = w_be_l;
		newEmp->num_late = n_be_l;
		newEmp->num_clock = n_c;
		newEmp->num_ask_vacation = n_a_v;
		newEmp->total_annual_vacation = t_v;
		newEmp->taken_annual_vacation = h_v;
		newEmp->remaining_annual_vacation = r_v;
		newEmp->ask_vacation_status = a_v_s;

		newEmp->next = NULL;

		// 插入到对应部门的链表中
		Employees *move = com[department_num - 1].head;

		// 如果链表为空，直接将新节点作为头节点
		if (move == NULL)
		{
			com[department_num - 1].head = newEmp;
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

		// 更新部门员工数
		com[department_num - 1].num_of_staff++;

		printf("员工信息已成功添加到部门 %s\n", departments[department_num - 1]);
		Complete_job_num();
		Save();
		flag = 0;
		if (flag = 0)
		{
			system("cls");
			break;
		}
	}
}

void DeleteStaff() // 删除员工
{
	char jobnum[8];
	printf("请输入要删除的员工的编号: ");
	int temp=scanf("%s", jobnum);

	int found = 0; // 标记是否找到员工
	for (int i = 0; i < 4; i++) // 遍历所有部门
	{
		Employees* prev = NULL; // 前驱节点
		Employees* curr = com[i].head; // 当前节点

		while (curr != NULL) // 遍历当前部门的员工链表
		{
			if (strcmp(curr->job_num, jobnum) == 0) // 找到匹配的员工
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
				printf("员工工号为 %s 的数据已成功删除。\n", jobnum);
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
		printf("未找到工号为 %s 的员工数据。\n", jobnum);
	}
}

void ModifyStaff(void) // 修改员工信息
{
	char jobnum[8];
	printf("请输入要修改的员工工号：");
	int temp=scanf("%s", jobnum);

	int found = 0;
	for (int i = 0; i < 4; i++) // 遍历所有部门
	{
		Employees* curr = com[i].head; // 当前节点
		while (curr != NULL) // 遍历当前部门的员工链表
		{
			if (strcmp(curr->job_num, jobnum) == 0) // 找到匹配的员工
			{
				found = 1;
				ModifyMultipleFields(curr);//调用modifyMultipleFields函数实现信息修改
				break;
			}
			curr = curr->next; // 移动到下一个节点
		}
		if (found) // 如果已找到员工，退出部门循环
		{
			break;
		}
	}

	if (!found) // 如果遍历完所有部门仍未找到员工
	{
		printf("未找到工号为 %s 的员工数据。\n", jobnum);
	}
}

void ModifyMultipleFields(Employees* emp)//modifyStaff函数的辅助函数
{
	int fields[10] = { 0 }; // 用于记录用户选择的字段
	int numFields = 0;

	while (1)
	{
		printf("请选择要修改的字段（1-7），输入0完成选择：\n");
		printf("1. 姓名\n");
		printf("2. 职位\n");
		printf("3. 部门\n");
		printf("4. 工龄\n");
		printf("5. 工作状态\n");
		printf("6. 密码\n");
		printf("7. 打卡状态\n");
		printf("请输入您的选择（0-7）：");
		int choice;
		int temp = scanf("%d", &choice);

		if (choice == 0)
		{
			break; // 如果用户输入0，退出循环
		}
		else if (choice >= 1 && choice <= 7)
		{
			fields[numFields++] = choice; // 记录用户选择的字段编号
		}
		else
		{
			printf("无效的选择！\n");
		}
	}

	for (int i = 0; i < numFields; i++)
	{
		switch (fields[i])
		{
		case 1: // 修改姓名
			printf("请输入新的姓名（不超过3个字符）：");
			scanf("%s", emp->name);
			break;
		case 2: // 修改职位
			printf("请输入新的职位编号（1-Admin, 2-Manager, 3-Staff）：");
			int identity_num;
			scanf("%d", &identity_num);
			if (identity_num >= 1 && identity_num <= 3)
			{
				strcpy(emp->identity, identities[identity_num - 1]);
			}
			else
			{
				printf("无效的职位编号！\n");
			}
			break;
		case 3: // 修改部门
			printf("请输入新的部门编号（1-Purchase, 2-Produce, 3-Sale, 4-Manage）：");
			int department_num;
			scanf("%d", &department_num);
			if (department_num >= 1 && department_num <= 4)
			{
				strcpy(emp->department, departments[department_num - 1]);
			}
			else
			{
				printf("无效的部门编号！\n");
			}
			break;
		case 4: // 修改工龄
			printf("请输入新的工龄：");
			scanf("%d", &emp->age_of_work);
			break;
		case 5: // 修改工作状态
			printf("请输入新的工作状态（1-正常工作, 0-假期中）：");
			scanf("%d", &emp->stage);
			break;
		case 6: // 修改密码
			printf("请输入新的密码（4位数字）：");
			scanf("%s", emp->password);
			break;
		case 7: // 修改打卡状态
			printf("请输入新的打卡状态（1-已打卡, 0-未打卡）：");
			scanf("%d", &emp->Whether_clock);
			break;
		}
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
		scanf("%s", pass1);
		getchar();
		if (strcmp(pass1, emp->password) == 0)
		{
			printf("请输入新密码：\n");
			scanf("%s", pass1);
			getchar();

			printf("请再次输入新密码：\n");
			scanf("%s", pass2);
			getchar();

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
	system("cls");
	while (1)
	{
		int pick, flag = 0;
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
					emp->ask_vacation_status = 1; // 设置为已申请待审批状态
					printf("%s %s 已成功申请假期。\n", emp->identity, emp->name);
				}
				else if (emp->ask_vacation_status == 1)
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
			case 2:emp->ask_vacation_status = 0; printf("已成功取消申请。\n"); Sleep(commmon_time); system("cls"); break;
			case 0:flag = 1; printf("退出登录成功\n"); Sleep(commmon_time); Save(); break;
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
		if (emp_s->ask_vacation_status == 1 )
		{
			if (emp_s->id_identity != 2)
			{
				printf("如果同意申请，请输入1\n");
				printf("如果拒绝申请，请输入2\n");
				printf("如果要退出审批，请输入0\n");
				printf("姓名：%s\n", emp_s->name);
				printf("工号：%s\n", emp_s->job_num);
				printf("职务：%s\n", identities[emp_s->id_identity - 1]);
				printf("总年假：%d\n", emp_s->total_annual_vacation);
				printf("已用年假：%d\n", emp_s->taken_annual_vacation);
				printf("剩余年假：%d\n", emp_s->remaining_annual_vacation);
				scanf("%d", &judge);
				switch (judge)
				{
				case 1:emp_s->ask_vacation_status = 2; printf("已同意申请=\n"); system("cls"); ; break;
				case 2:emp_s->ask_vacation_status = 3; printf("已拒绝申请=\n"); system("cls"); ; break;
				case 0:flag = 1; printf("退出审批管理成功\n"); Sleep(commmon_time); system("cls");  break;
				}
			}
		}
		if (flag == 1)
			break;
		emp_s = emp_s->next;
	}
	Save();
	printf("已全部处理。\n");
	Sleep(commmon_time);
	system("cls");
}
