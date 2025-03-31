#include"variable.h"
#include"fun.h"

<<<<<<< HEAD

Employees * CreatAndRead_employees(int i)//存入文件中的数据
=======
void Save(void)//数据保存
>>>>>>> main
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
			fprintf(newFile, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %s\n",
				emp->name, emp->job_num, emp->id_department, emp->id_identity, emp->age, emp->age_of_work, emp->stage, emp->password, emp->Whether_clock,
				emp->time_of_clock, emp->time_of_leave, emp->Whether_be_late, emp->num_late, emp->total_annual_vacation, emp->taken_annual_vacation, emp->remaining_annual_leave,emp->telephone_number);
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
	char name[4] = { '\0' };//第十二行至第十八行的变量临时存储fscanf读入的数据
    char j_num[8] = { '\0' };
    int department_num = 0;
	int identity_num = 0;
    int age = 0;
	int age_w = 0;
	int stage = 0;
	char pass[5] = { '\0' };
    int w_clock = 0;
    char tm_of_c[20] = { '\0' };
    char tm_of_l[20] = { '\0' };
    int w_be_l = 0;
    int n_be_l = 0;
    int t_v = 0;
    int h_v = 0;
    int r_v = 0;
	char phone_num[12] = { '\0' };

    Employees *head = NULL, *p1 = NULL, *p2 = NULL;
    FILE *fp = fopen("data.txt", "r");//只读打开data.txt
    if (fp == NULL)
    {
        printf("文件不存在");
		Sleep(error_time);
		exit(1);
    }

	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %s", 
        name,j_num,&department_num,&identity_num,&age,&age_w,&stage,pass,&w_clock, tm_of_c, tm_of_l,&w_be_l,&n_be_l,&t_v,&h_v,&r_v, phone_num) == 17)//每一行有17个数据 所以fscanf返回值为17
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
			strcpy(p1->name, name);//将数据存入
            strcpy(p1->job_num, j_num);//工号
            if (department_num >= 1 && department_num <= 4)//所属部门
                strcpy(p1->department, departments[i]);
            p1->id_department = department_num;
            if (identity_num >= 1 && identity_num <=3)//职位
                strcpy(p1->identity, identities[identity_num - 1]);
            p1->id_identity = identity_num;
            p1->age = age;
            p1->age_of_work = age_w;//工龄
            p1->stage = stage; //工作状态
            strcpy(p1->password, pass);//四位密码
            p1->Whether_clock = w_clock;//是否打卡
            strcpy(p1->time_of_clock, tm_of_c);//打卡时间
            strcpy(p1->time_of_leave, tm_of_l);//离开时间
            p1->Whether_be_late = w_be_l;//是否迟到
            p1->num_late = n_be_l;//迟到数
            p1->total_annual_vacation = t_v;//总年假
            p1->taken_annual_vacation = h_v;//已用年假
            p1->remaining_annual_leave = r_v;//剩余年假
			strcpy(p1->telephone_number, phone_num);//电话号码

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

void init_company(void)//初始化公司数组
{
	for (int i = 0; i < 4; i++)
	{
		com[i].order = i + 1;
		strcpy(com[i].department, departments[i]);
		com[i].num_of_staff = 0;//初始化部门人数
		com[i].head = CreatAndRead_employees(i);//i从0~3代表不同公司部门
	}
}

void complete_job_num(void)//完成工号
{
	for (int i = 0; i < 4; i++)
	{
<<<<<<< HEAD
		bool flag = 0;
		if (flag = 0)
		{
			Employees *emp = com[i].head;
			for (int j = 0; emp != NULL; j++)
			{
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

		FILE *oldFile = fopen("data.txt", "r");
		if (oldFile == NULL) {
			printf("无法打开原始文件");
			return;
		}

		FILE *tempFile = fopen("temp.txt", "w");
		if (tempFile == NULL) {
			printf("无法打开临时文件");
			fclose(oldFile);
			return;
		}

		char line[100];

		while (fgets(line, 100, oldFile) != NULL)
		{
			for (int i = 0; i < 4; i++)
			{
				Employees *emp = com[i].head;

				char name[4] = { '\0' };
				int identity_num = 0;
				int department_num = 0;
				sscanf(line, "%s %d %d", name, &identity_num, &department_num);
				while (emp != NULL)
				{
					if (strcmp(name, emp->name) == 0 && strcmp(identities[identity_num - 1], emp->identity) == 0 && strcmp(departments[department_num - 1], emp->department) == 0)
					{
						// 去掉行尾的换行符
						int temp = strcspn(line, "\n");
						for (int j = temp; j > temp - 9; j--)
						{
							line[j] = '\0';
						}
						// 在每一行末尾添加新数据
						fprintf(tempFile, "%s %s\n", line, emp->job_num);
					}
					emp = emp->next;
				}
			}
		}

		fclose(oldFile);
		fclose(tempFile);

		remove("data.txt");
		int temp = rename("temp.txt", "data.txt");

		printf("新数据已成功添加到每一行末尾。\n");
		flag = 1;
	}
}

void Main_UI(void)
{
	char j_n[8] = { '\0' };
	char pass[6] = { '\0' };
	system("cls");
	printf("请登录\n");
	printf("工号：");
	gets(j_n);
	printf("密码：");
	gets(pass);
	for (int i = 0; i < 4; i++)
	{
		bool flag = 0;
=======
>>>>>>> main
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

void select_clock(Employees *emp)//打卡选择
{
	int pick;
	system("cls");;
	printf("------------------------------\n");
	printf("|         1.上班打卡          |\n");
	printf("|         2.下班打卡          |\n");
	printf("|         3.退出打卡          |\n");
	printf("------------------------------\n");
	int temp = scanf("%d", &pick);
	switch (pick)
	{
	case 1:
	{
		time_t current_time = time(NULL);
		struct tm *local_tm;
		local_tm = localtime(&current_time);//将时间戳转为本地时间
		if (emp->Whether_clock != 1 && local_tm->tm_hour > 6)
		{
			emp->Whether_clock = 1;
			printf("打卡成功\n");

			printf("打卡时间：%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
				local_tm->tm_hour, local_tm->tm_min);

			int temp = sprintf(emp->time_of_leave, "%d%d-%02d-%02d%d:%02d", 
				local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,local_tm->tm_hour, local_tm->tm_min);

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

			int temp = sprintf(emp->time_of_leave, "%d%d-%02d-%02d%d:%02d",
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

	case 3:
	{
		system("cls");
	}break;

	}
}

void StaffAndUi(Employees *emp)
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
		printf("|         5.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
			case 1:select_clock(emp); break;
			case 5:flag = 1; system("cls"); printf("退出登录成功\n");Sleep(commmon_time); break;
		}
	}
}

void inputStaff() //添加员工
{
	char name[4]; // 员工姓名
	int identity_num; // 员工职位编号
	int department_num; // 部门编号
	int age; // 工龄
	int stage; // 工作状态
	char password[5]; // 密码
	int clock; // 打卡状态

<<<<<<< HEAD
	// 输入员工信息
	printf("请输入员工信息\n");
	printf("姓名（不超过3个字符）：");
	scanf("%s", name);
	printf("职位编号（1-Admin, 2-Manager, 3-Staff）：");
	scanf("%d", &identity_num);
	printf("部门编号（1-Purchase, 2-Produce, 3-Sale, 4-Manage）：");
	scanf("%d", &department_num);
	printf("工龄：");
	scanf("%d", &age);
	printf("工作状态（1-正常工作, 0-假期中）：");
	scanf("%d", &stage);
	printf("密码：");
	scanf("%s", password);
	printf("打卡状态（1-已打卡, 0-未打卡）：");
	scanf("%d", &clock);
=======
    
>>>>>>> main

	// 判断输入是否正确
	if (identity_num < 1 || identity_num > 3) {
		printf("职位编号无效！\n");
		return;
	}
	if (department_num < 1 || department_num > 4) {
		printf("部门编号无效！\n");
		return;
	}
	if (age < 1 || age > 60) {
		printf("工龄无效！\n");
		return;
	}
	if (stage != 0 && stage != 1) {
		printf("工作状态无效！\n");
		return;
	}
	if (clock != 0 && clock != 1) {
		printf("打卡状态无效！\n");
		return;
	}

	// 创建新员工节点
	Employees* newEmp = (Employees*)malloc(sizeof(Employees));
	if (newEmp == NULL) {
		printf("内存分配失败！\n");
		return;
	}

	// 将员工信息拷贝
	strcpy(newEmp->name, name);
	strcpy(newEmp->identity, identities[identity_num - 1]);
	strcpy(newEmp->department, departments[department_num - 1]);
	newEmp->age_of_work = age;
	newEmp->stage = stage;
	strcpy(newEmp->password, password);
	newEmp->Whether_clock = clock;
	newEmp->next = NULL;

	// 生成工号(姓名+部门+职位+在部门里的序号)
	char deptNum[2];
	char idNum[2];
	char staffNum[3];
	sprintf(deptNum, "%d", department_num); // 部门编号转为字符串
	sprintf(idNum, "%d", identity_num); // 职位编号转为字符串
	sprintf(staffNum, "%02d", com[department_num - 1].num_of_staff + 1); // 员工在部门里的序号，格式化为两位数

	strcpy(newEmp->job_num, name);
	strcat(newEmp->job_num, deptNum);
	strcat(newEmp->job_num, idNum);
	strcat(newEmp->job_num, staffNum);

	// 插入到对应部门的链表中
	Employees* move = com[department_num - 1].head;

	// 如果链表为空，直接将新节点作为头节点
	if (move == NULL) {
		com[department_num - 1].head = newEmp;
	}
	else {
		// 遍历链表，将新节点插入到链表末尾
		while (move->next != NULL) {
			move = move->next;
		}
		move->next = newEmp;
	}

	// 更新部门员工数
	com[department_num - 1].num_of_staff++;

	printf("员工信息已成功添加到部门 %s\n", departments[department_num - 1]);
}

void deleteStaff() // 删除员工
{
	char jobnum[8];
	printf("请输入要删除的员工的编号: ");
	scanf("%s", jobnum);

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

void modifyStaff(void) // 修改员工信息
{
	char jobnum[8];
	printf("请输入要修改的员工工号：");
	scanf("%s", jobnum);

	int found = 0;
	for (int i = 0; i < 4; i++) // 遍历所有部门
	{
		Employees* curr = com[i].head; // 当前节点
		while (curr != NULL) // 遍历当前部门的员工链表
		{
			if (strcmp(curr->job_num, jobnum) == 0) // 找到匹配的员工
			{
				found = 1;
				modifyMultipleFields(curr);//调用modifyMultipleFields函数实现信息修改
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

void modifyMultipleFields(Employees* emp)//modifyStaff函数的辅助函数
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
		scanf("%d", &choice);

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
