#include"variable.h"
#include"fun.h"
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
			fprintf(newFile, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d\n",
				emp->name, emp->job_num, emp->id_department, emp->id_identity, emp->age, emp->age_of_work, emp->stage, emp->password, emp->Whether_clock,
				emp->time_of_clock, emp->time_of_leave, emp->Whether_be_late, emp->num_late,emp->num_clock,emp->vacation_status);
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
	int s_c_times = 0;
	int t_a_vdays = 0;//请的年假数
	int r_vdays = 0;
	int v_status = 0;
	Employees* head = NULL, * p1 = NULL, * p2 = NULL;
	FILE* fp = fopen("data.txt", "r");//只读打开data.txt
	if (fp == NULL)
	{
		printf("文件不存在");
		Sleep(error_time);
		exit(1);
	}

	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d %d",
		name, j_num, &department_num, &identity_num, &age, &age_w, &stage, pass, &w_clock, tm_of_c, tm_of_l, &w_be_l, &n_be_l, &s_c_times,&r_vdays, &v_status ,&t_a_vdays) == 17)//每一行有17个数据 所以fscanf返回值为17
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
			strcpy(p1->name, name);//将数据存入
			strcpy(p1->job_num, j_num);//工号
			if (department_num >= 1 && department_num <= 4)//所属部门
				strcpy(p1->department, departments[i]);
			p1->id_department = department_num;
			if (identity_num >= 1 && identity_num <= 3)//职位
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
			p1->num_clock = s_c_times;//打卡次数
			p1->vacation_status = v_status;// 请假状态
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

		bool flag = 0;
		if (flag = 0)
		{
			Employees* emp = com[i].head;
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

		FILE* oldFile = fopen("data.txt", "r");
		if (oldFile == NULL) {
			printf("无法打开原始文件");
			return;
		}

		FILE* tempFile = fopen("temp.txt", "w");
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
				Employees* emp = com[i].head;

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

void select_clock(Employees* emp)//打卡选择
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
		struct tm* local_tm;
		local_tm = localtime(&current_time);//将时间戳转为本地时间
		if (emp->Whether_clock != 1 && local_tm->tm_hour > 6)
		{
			emp->Whether_clock = 1;
			printf("打卡成功\n");
			emp->num_clock++;

			printf("打卡时间：%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
				local_tm->tm_hour, local_tm->tm_min);

			int temp = sprintf(emp->time_of_leave, "%d%d-%02d-%02d%d:%02d",
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
			struct tm* local_tm;
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

void StaffAndUi(Employees* emp)
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
		printf("|         5.信息排序          |\n");
		printf("|         6.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick)
		{
		case 1:select_clock(emp); break;
		case 2:findStaff(emp); break;
		case 3: requestVacation(emp); break;
		case 4:modifyStaffCode(emp); break;
		case 5:
		case 6:flag = 1; system("cls"); printf("退出登录成功\n"); Sleep(commmon_time); break;
		default:
			printf("无效选项，请重新输入。\n");
			Sleep(commmon_time);
		}
	}
}

void ManagerAndUi(Employees* emp) //部门经理功能
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
		printf("|         2.信息查询          |\n");
		printf("|         3.审批请假          |\n");
		printf("|         4.修改密码          |\n");
		printf("|         5.信息排序          |\n");
		printf("|         6.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick) {
		case 1: select_clock(emp); break;
		case 2:ManagerQueryInfo(emp); break;
		case 3: {
			Employees* curr = com[emp->id_department - 1].head;
			while (curr != NULL) {
				if (curr->vacation_status == 1) {
					printf("员工 %s 申请假期。\n", curr->name);
					printf("1. 批准\n2. 拒绝\n");
					int choice;
					scanf("%d", &choice);
					if (choice == 1) {
						approveVacation(curr);
					}
					else if (choice == 2) {
						rejectVacation(curr);
					}
				}
				curr = curr->next;
			}
		} break;
		case 4: modifyStaffCode(emp); break;
		case 5:ManagerSort(emp); break;
		case 6: flag = 1; system("cls"); printf("退出登录成功\n"); Sleep(commmon_time); break;
		default:
			printf("无效选项，请重新输入。\n");
			Sleep(commmon_time);
		}
	}
}

void AdminAndUi(Employees* emp)//管理员功能
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
		printf("|         3.信息管理         |\n");
		printf("|         4.修改密码          |\n");
		printf("|         5.信息排序          |\n");
		printf("|         6.退出登录          |\n");
		printf("------------------------------\n");
		int temp = scanf("%d", &pick);
		switch (pick) {
		case 1:  break;
		case 2:  AdminQueryInfo(); break;
		case 3: break;
		case 4: {
			// 查找并打印最佳员工
			Employees* allEmployees = NULL;
			for (int i = 0; i < 4; i++) {
				Employees* temp = com[i].head;
				while (temp != NULL) {
					Employees* newNode = createNewNode(temp);
					newNode->next = allEmployees;
					allEmployees = newNode;
					temp = temp->next;
				}
			}
			findAndPrintBestEmployees(allEmployees);
			// 释放临时链表
			while (allEmployees != NULL) {
				Employees* temp = allEmployees;
				allEmployees = allEmployees->next;
				free(temp);
			}
		} break; 
		case 5:AdminSort(); break;
		case 6: flag = 1; system("cls"); printf("退出登录成功\n"); Sleep(commmon_time); break;
		default:
			printf("无效选项，请重新输入。\n");
			Sleep(commmon_time);
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

void findStaff(Employees* emp)//普通职工查询自己的信息
{
	while (emp != NULL) {
			printf("姓名: %s\n", emp->name);
			printf("工号: %s\n", emp->job_num);
			printf("部门: %s\n", emp->department);
			printf("职位: %s\n", emp->identity);
			printf("年龄: %d\n", emp->age);
			printf("工龄: %d\n", emp->age_of_work);
			printf("状态: %d\n", emp->stage);
			printf("密码: %s\n", emp->password);
			printf("是否打卡: %d\n", emp->Whether_clock);
			printf("打卡时间: %s\n", emp->time_of_clock);
			printf("离开时间: %s\n", emp->time_of_leave);
			printf("是否迟到: %d\n", emp->Whether_be_late);
			printf("迟到次数: %d\n", emp->num_late);
			printf("打卡次数: %d\n", emp->num_clock);
			printf("请假次数: %d\n", emp->num_ask_vacation);
			printf("总年假: %d\n", emp->total_annual_vacation);
			printf("已用年假: %d\n", emp->taken_annual_vacation);
			printf("剩余年假: %d\n", emp->remaining_annual_leave);
	}
	system("pause");
	system("cls");
}

void modifyStaffCode(Employees* emp)//员工密码修改
{
		while (emp != NULL) {
				printf("当前密码: %s\n", emp->password);
				printf("请输入新密码: ");
				scanf("%s", emp->password);
				printf("密码修改成功。\n");
		}
		system("pause");
		system("cls");
}

void requestVacation(Employees* emp) //假期申请函数
{
	if (emp->stage == 0) {
		printf("员工 %s 已经在假期中，无法再次申请假期。\n", emp->name);
		return;
	}
	
	emp->vacation_status = 1; // 设置为已申请待审批状态
	printf("员工 %s 已成功申请假期，等待审批。\n", emp->name);
}

void approveVacation(Employees* emp) //批准职员的请假申请
{
	if (emp->vacation_status != 1) {
		printf("没有待审批的请假申请。\n");
		return;
	}
	emp->vacation_status = 2; // 设置为已批准状态
	emp->num_ask_vacation++;
	printf("员工 %s 的请假申请已被批准。\n", emp->name);
}

void rejectVacation(Employees* emp)//拒绝职员的请假申请
{
	if (emp->vacation_status != 1) {
		printf("没有待审批的请假申请。\n");
		return;
	}
	emp->vacation_status = 3; // 设置为已拒绝状态
	printf("员工 %s 的请假申请已被拒绝。\n", emp->name);
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
	int sortOption;
	printf("------------------------------\n");
	printf("|         1.按打卡次数排序    |\n");
	printf("|         2.按请假次数排序    |\n");
	printf("|         3.多重排序           |\n");
	printf("|         4.最佳员工            |\n");
	printf("|         5.返回上一级          |\n");
	printf("------------------------------\n");
	printf("请选择排序方式：");
	scanf("%d", &sortOption);

	switch (sortOption) {
	case 1: {
		// 按打卡次数排序
		com[emp->id_department - 1].head = mergeSortByClockTimes(com[emp->id_department - 1].head);
		printf("本部门员工信息已按打卡次数升序排序。\n");
		ManagerprintSortedEmployees(com[emp->id_department - 1].head, "打卡次数");
		Sleep(commmon_time);
	} break;
	case 2: {
		// 按请假次数排序
		com[emp->id_department - 1].head = mergeSortByVacationTimes(com[emp->id_department - 1].head);
		printf("本部门员工信息已按请假次数升序排序。\n");
		ManagerprintSortedEmployees(com[emp->id_department - 1].head, "请假次数");
		Sleep(commmon_time);
	} break;
	case 3: {
		// 按请假次数、打卡次数和名字排序
		com[emp->id_department - 1].head = mergeSortByMultipleAttributes(com[emp->id_department - 1].head);
		printf("本部门员工信息已按请假次数、打卡次数和名字排序。\n");
		ManagerprintSortedEmployees(com[emp->id_department - 1].head, "请假、打卡次数和名字");
		Sleep(commmon_time);
	} break;
		
	case 4: {
		// 查找并打印最佳员工
		findAndPrintBestEmployees(com[emp->id_department - 1].head);
	} break; 
	case 5: {
		return;
	}
	default:
		printf("无效选项，请重新输入。\n");
		Sleep(commmon_time);
	}
}

void ManagerprintSortedEmployees(Employees* head, const char* sortBy)//部门经理的信息排序的打印函数，打印输出排序后的信息
{
	if (head == NULL) {
		printf("没有员工信息可显示。\n");
		return;
	}

	printf("------------------------------\n");
	printf("| 姓名 | %s |\n", sortBy);
	printf("------------------------------\n");

	Employees* current = head;
	while (current != NULL) {
		if (strcmp(sortBy, "打卡次数") == 0) {
			printf("| %-4s | %-8d |\n", current->name, current->num_clock);
		}
		else if (strcmp(sortBy, "请假次数") == 0) {
			printf("| %-4s | %-8d |\n", current->name, current->num_ask_vacation);
		}
		else if (strcmp(sortBy, "请假、打卡次数和名字") == 0) {
			printf("| %-4s | 请假次数: %-3d 打卡次数: %-3d 姓名: %-4s |\n", current->name, current->num_ask_vacation, current->num_clock, current->name);
		}
		current = current->next;
	}
}

void AdminPrintSortedEmployees(const char* sortBy)//管理员的排序打印函数，打印排序后的数据
{
	printf("------------------------------\n");
	printf("| 部门 | 姓名 | %s |\n", sortBy);
	printf("------------------------------\n");

	for (int i = 0; i < 4; i++) {
		Employees* current = com[i].head;
		while (current != NULL) {
			if (strcmp(sortBy, "打卡次数") == 0) {
				printf("| %-6s | %-4s | %-8d |\n", com[i].department, current->name, current->num_clock);
			}
			else if (strcmp(sortBy, "请假次数") == 0) {
				printf("| %-6s | %-4s | %-8d |\n", com[i].department, current->name, current->num_ask_vacation);
			}
			else if (strcmp(sortBy, "请假、打卡次数和名字") == 0) {
				printf("| %-6s | %-4s | 请假次数: %-3d 打卡次数: %-3d 姓名: %-4s |\n", com[i].department, current->name, current->num_ask_vacation, current->num_clock, current->name);
			}
			current = current->next;
		}
	}
	printf("------------------------------\n");
}

void AdminSort(void)//管理员的排序函数
{
	int sortOption;
	printf("------------------------------\n");
	printf("|         1.按打卡次数排序    |\n");
	printf("|         2.按请假次数排序    |\n");
	printf("|         3.多重排序           |\n");
	printf("|         4.最佳员工            |\n");
	printf("|         5.返回上一级          |\n");
	printf("------------------------------\n");
	printf("请选择排序方式：");
	scanf("%d", &sortOption);

	switch (sortOption) {
	case 1: {
		// 按打卡次数排序
		for (int i = 0; i < 4; i++) {
			Employees* sortedHead = mergeSortByClockTimes(com[i].head); // 创建新的排序链表
			AdminPrintSortedEmployees("打卡次数"); // 打印排序后的链表
		}
		printf("所有部门的员工信息已按打卡次数升序排序。\n");
		Sleep(commmon_time);
	} break;
	case 2: {
		// 按请假次数排序
		for (int i = 0; i < 4; i++) {
			Employees* sortedHead = mergeSortByVacationTimes(com[i].head); // 创建新的排序链表
			AdminPrintSortedEmployees("请假次数"); // 打印排序后的链表
		}
		printf("所有部门的员工信息已按请假次数升序排序。\n");
		Sleep(commmon_time);
	} break;
	case 3: {
		// 按请假、打卡次数和名字排序
		for (int i = 0; i < 4; i++) {
			com[i].head = mergeSortByMultipleAttributes(com[i].head);
			AdminPrintSortedEmployees("请假、打卡次数和名字");
		}
		printf("所有部门的员工信息已按请假次数、打卡次数和名字排序。\n");
		Sleep(commmon_time);
	} break;
	case 4: {// 查找并打印最佳员工
		Employees* allEmployees = NULL;
		for (int i = 0; i < 4; i++) {
			Employees* temp = com[i].head;
			while (temp != NULL) {
				Employees* newNode = createNewNode(temp);
				newNode->next = allEmployees;
				allEmployees = newNode;
				temp = temp->next;
			}
		}
		findAndPrintBestEmployees(allEmployees);
		// 释放临时链表
		while (allEmployees != NULL) {
			Employees* temp = allEmployees;
			allEmployees = allEmployees->next;
			free(temp);
		}
	}break;
	case 5: {
		return;
	}
	default:
		printf("无效选项，请重新输入。\n");
		Sleep(commmon_time);
	}
}

void AdminQueryInfo(void) //管理员的信息查询函数
{
	system("cls");
	printf("------------------------------\n");
	printf("|         1.查询工作状态       |\n");
	printf("|         2.查询打卡、迟到、请假次数|\n");
	printf("|         3.查询员工所有信息   |\n");
	printf("|         4.返回上一级         |\n");
	printf("------------------------------\n");
	printf("请选择查询内容：");
	int choice;
	scanf("%d", &choice);

	char jobnum[8];
	printf("请输入员工工号：");
	scanf("%s", jobnum);

	Employees* emp = NULL;
	for (int i = 0; i < 4; i++) {
		emp = com[i].head;
		while (emp != NULL) {
			if (strcmp(emp->job_num, jobnum) == 0) {
				break;
			}
			emp = emp->next;
		}
		if (emp != NULL) {
			break;
		}
	}

	if (emp == NULL) {
		printf("未找到工号为 %s 的员工。\n", jobnum);
		Sleep(commmon_time);
		return;
	}

	switch (choice) {
	case 1: {
		printf("员工 %s 的工作状态为：%s\n", emp->name, emp->stage == 1 ? "正常工作" : "假期中");
		break;
	}
	case 2: {
		printf("员工 %s 的打卡次数：%d，迟到次数：%d，请假次数：%d\n", emp->name, emp->num_clock, emp->num_late, emp->num_ask_vacation);
		break;
	}
	case 3: {
		printf("员工 %s 的信息：\n", emp->name);
		printf("姓名：%s\n", emp->name);
		printf("工号：%s\n", emp->job_num);
		printf("部门：%s\n", emp->department);
		printf("职位：%s\n", emp->identity);
		printf("年龄：%d\n", emp->age);
		printf("工龄：%d\n", emp->age_of_work);
		printf("工作状态：%s\n", emp->stage == 1 ? "正常工作" : "假期中");
		printf("密码：%s\n", emp->password);
		printf("是否打卡：%s\n", emp->Whether_clock == 1 ? "已打卡" : "未打卡");
		printf("打卡时间：%s\n", emp->time_of_clock);
		printf("离开时间：%s\n", emp->time_of_leave);
		printf("是否迟到：%s\n", emp->Whether_be_late == 1 ? "是" : "否");
		printf("迟到次数：%d\n", emp->num_late);
		printf("打卡次数：%d\n", emp->num_clock);
		printf("请假次数：%d\n", emp->num_ask_vacation);
		break;
	}
	case 4: {
		return;
	}
	default: {
		printf("无效选项，请重新输入。\n");
		Sleep(commmon_time);
		return;
	}
	}
	Sleep(commmon_time);
}

void ManagerQueryInfo(Employees* emp) //部门经理的信息查询函数
{
	system("cls");
	printf("------------------------------\n");
	printf("|         1.查询工作状态       |\n");
	printf("|         2.查询打卡、迟到、请假次数|\n");
	printf("|         3.查询员工所有信息   |\n");
	printf("|         4.返回上一级         |\n");
	printf("------------------------------\n");
	printf("请选择查询内容：");
	int choice;
	scanf("%d", &choice);

	char jobnum[8];
	printf("请输入员工工号：");
	scanf("%s", jobnum);

	Employees* curr = com[emp->id_department - 1].head;
	while (curr != NULL) {
		if (strcmp(curr->job_num, jobnum) == 0) {
			break;
		}
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("未找到工号为 %s 的员工。\n", jobnum);
		Sleep(commmon_time);
		return;
	}

	switch (choice) {
	case 1: {
		printf("员工 %s 的工作状态为：%s\n", curr->name, curr->stage == 1 ? "正常工作" : "假期中");
		break;
	}
	case 2: {
		printf("员工 %s 的打卡次数：%d，迟到次数：%d，请假次数：%d\n", curr->name, curr->num_clock, curr->num_late, curr->num_ask_vacation);
		break;
	}
	case 3: {
		printf("员工 %s 的信息：\n", curr->name);
		printf("姓名：%s\n", curr->name);
		printf("工号：%s\n", curr->job_num);
		printf("部门：%s\n", curr->department);
		printf("职位：%s\n", curr->identity);
		printf("年龄：%d\n", curr->age);
		printf("工龄：%d\n", curr->age_of_work);
		printf("工作状态：%s\n", curr->stage == 1 ? "正常工作" : "假期中");
		printf("密码：%s\n", curr->password);
		printf("是否打卡：%s\n", curr->Whether_clock == 1 ? "已打卡" : "未打卡");
		printf("打卡时间：%s\n", curr->time_of_clock);
		printf("离开时间：%s\n", curr->time_of_leave);
		printf("是否迟到：%s\n", curr->Whether_be_late == 1 ? "是" : "否");
		printf("迟到次数：%d\n", curr->num_late);
		printf("打卡次数：%d\n", curr->num_clock);
		printf("请假次数：%d\n", curr->num_ask_vacation);
		break;
	}
	case 4: {
		return;
	}
	default: {
		printf("无效选项，请重新输入。\n");
		Sleep(commmon_time);
		return;
	}
	}
	Sleep(commmon_time);
}

void findAndPrintBestEmployees(Employees* head)// 查找并打印所有最佳员工
{
	int maxClock = 0;
	int minVacation = 200; 
	Employees* current = head;
	int bestEmployeeCount = 0;

	// 第一次遍历，找到最大打卡次数和最小请假次数
	while (current != NULL) {
		if (current->num_late == 0) { // 迟到数为0
			if (current->num_clock > maxClock) {
				maxClock = current->num_clock;
				minVacation = current->num_ask_vacation;
			}
			else if (current->num_clock == maxClock && current->num_ask_vacation < minVacation) {
				minVacation = current->num_ask_vacation;
			}
		}
		current = current->next;
	}

	// 第二次遍历，打印所有符合条件的最佳员工
	current = head;
	printf("最佳员工信息：\n");
	printf("姓名\t工号\t打卡次数\t请假次数\n");
	while (current != NULL) {
		if (current->num_late == 0 && current->num_clock == maxClock && current->num_ask_vacation == minVacation) {
			printf("%s\t%s\t%d\t\t%d\n", current->name, current->job_num, current->num_clock, current->num_ask_vacation);
			bestEmployeeCount++;
		}
		current = current->next;
	}

	if (bestEmployeeCount == 0) {
		printf("没有符合条件的最佳员工。\n");
	}
	else {
		printf("共找到 %d 名最佳员工。\n", bestEmployeeCount);
	}
}
