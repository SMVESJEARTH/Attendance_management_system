#include"variable.h"

Employees * CreatAndRead_employees(int i)
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




