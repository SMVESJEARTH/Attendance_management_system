#include"variable.h"
#include"fun.h"


Employees * CreatAndRead_employees(int i)//存入文件中的数据
{
	Employees *head = NULL, *p1 = NULL, *p2 = NULL;
	FILE *fp = fopen("data.txt", "r");//只读打开data.txt
	if (fp == NULL)
	{
		printf("文件不存在");
		return NULL;
	}
	char name[4] = { '\0' };//第十二行至第十八行的变量临时存储fscanf读入的数据
	int identity_num = 0;
	int department_num = 0;
	int age = 0;
	int stage = 0;
	char pass[5] = { '\0' };
	int clock = 0;
	char j_num[8] = { '\0' };

	while (fscanf(fp, "%s %d %d %d %d %s %d %s", name,&identity_num,&department_num,&age,&stage,pass,&clock,j_num) == 8)//每一行有七个数据 所以fscanf返回值为7
	{
		if (department_num == i + 1)//程序中的部门索引是0~3 而文件和手动输入的部门索引是1~4，故加1
		{
			p1 = (Employees *)malloc(sizeof(Employees));//开辟内存
			if (p1 == NULL)
			{
				fclose(fp); // 内存分配失败，关闭文件
				return head;
			}
			strcpy(p1->name, name);//将数据存入
			if (identity_num >= 1 || identity_num <=3)
			{
				strcpy(p1->identity, identities[identity_num - 1]);
			}
			else
			{
				continue;
			}
			if (department_num >= 1 || department_num <= 4)
			{
				strcpy(p1->department, departments[i]);
			}
			else
			{
				continue;
			}

			p1->age_of_work = age;
			p1->stage = stage;
			strcpy(p1->password, pass);
			p1->Whether_clock = clock;
			p1->job_num[5] = '\0';
			p1->job_num[6] = '\0';
			char n[2] = { '\0' };
			sprintf(n, "%d", department_num);
			strcpy(p1->job_num, name);
			strcat(p1->job_num, n);
			sprintf(n, "%d", identity_num);
			strcat(p1->job_num, n);

			if (head == NULL)
			{
				head = p1;
				p2 = p1;
			}
			else
			{
				p2->next = p1;
				p2 = p1;
			}
			p2->next = NULL;
			com[i].num_of_staff++;//部门员工数自增
		}
	}
	fclose(fp);
	return head;
}


void init_company(void)
{
	for (int i = 0; i < 4; i++)
		
	for (int i = 0; i < 4; i++)
	{
		com[i].order = i + 1;
		strcpy(com[i].department, departments[i]);
		com[i].num_of_staff = 0;//初始化部门人数
		com[i].head = CreatAndRead_employees(i);//i从0~3代表不同公司部门
	}
}

void complete_job_num(void)//完成每个人的工号
{
	for (int i = 0; i < 4; i++)
	{
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
		Employees *emp = com[i].head;
		while (emp != NULL)
		{
			if(!strcmp(emp->job_num,j_n))
			{
				if (!strcmp(emp->password, pass))
				{
					emp->Whether_clock = 1;
					flag = 1;
					printf("%s %s 验证通过，打卡成功\n", emp->identity, emp->name);
					break;
				}
			}
			emp = emp->next;
		}
		if (flag)
			break;
	}
	Sleep(1500);
	system("cls");
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
