﻿#include"variable.h"

Employees * CreatAndRead_employees(int i)
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
	
    Employees *head = NULL, *p1 = NULL, *p2 = NULL;
    FILE *fp = fopen("data.txt", "r");//只读打开data.txt
    if (fp == NULL)
    {
        printf("文件不存在");
        return NULL;
    }

	while (fscanf(fp, "%s %s %d %d %d %d %d %s %d %s %s %d %d %d %d %d", 
        name,j_num,&department_num,&identity_num,&age,&age_w,&stage,pass,&w_clock, tm_of_c, tm_of_l,&w_be_l,&n_be_l,&t_v,&h_v,&r_v) == 16)//每一行有16个数据 所以fscanf返回值为16
	{
		if (department_num == i + 1)//程序中的部门索引是0~3 而文件和手动输入的部门索引是1~4，故加1
		{
			p1 = (Employees *)malloc(sizeof(Employees));//开辟内存
			if (p1 == NULL)
			{
				fclose(fp); // 内存分配失败，关闭文件
				return head;
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


void init_company(void)
{
	for (int i = 0; i < 4; i++)
	{
		com[i].order = i + 1;
		strcpy(com[i].department, departments[i]);
		com[i].num_of_staff = 0;//初始化部门人数
		com[i].head = CreatAndRead_employees(i);//i从0~3代表不同公司部门
	}
}

void complete_job_num(void)//完成每个人的工号 4~10
{
	for (int i = 0; i < 4; i++)
	{
		Employees *emp = com[i].head;
        strcpy(emp->job_num, emp->name);
        emp->job_num[3] = emp->id_department + '0';
        emp->job_num[4] = emp->id_identity + '0';
		for (int j=0;emp != NULL;j++)
		{
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


Employees *LoginAndUi(void)
{
	system("cls");
	char j_n[8] = { '\0' };
	char pass[6] = { '\0' };
	printf("请登录\n");
	printf("工号：");
	gets(j_n);
	printf("密码：");
	gets(pass);
	for (int i = 0; i < 4; i++)
	{
		Employees *emp = com[i].head;
		while (emp != NULL)
		{
			if(!strcmp(emp->job_num,j_n) && !strcmp(emp->password, pass))
			{
				printf("%s %s 验证通过，欢迎登录\n", emp->identity, emp->name);
				Sleep(1500);
				return emp;
			}
			emp = emp->next;
		}
	}
	printf("工号或密码错误");
	return NULL;
}

void StaffAndUi(Employees *emp)
{
	system("cls");
	int pick_0 = 0;
	while (1)
	{
		printf("------------------------------\n");
		printf("|         1.打卡选择          |\n");
		printf("|         2.信息查询          |\n");
		printf("|         3.请假系统          |\n");
		printf("|         4.修改密码          |\n");
		printf("|         5.退出登录          |\n");
		printf("------------------------------\n");
		scanf("%d", &pick_0);
		switch (pick_0)
		{
			case 1:
			{
					int pick_1;
					system("cls");;
					printf("------------------------------\n");
					printf("|         1.上班打卡          |\n");
					printf("|         2.下班打卡          |\n");
					printf("|         3.退出打卡          |\n");
					printf("------------------------------\n");
					scanf("%d", &pick_1);
					switch (pick_1)
					{
					case 1:
					{
                        time_t current_time = time(NULL);
                        struct tm *local_tm;
                        local_tm = localtime(&current_time);
						if (emp->Whether_clock != 1&& local_tm->tm_hour > 6)
						{
							emp->Whether_clock = 1;
							printf("打卡成功\n");

							printf("打卡时间：%d-%02d-%02d.%d:%02d\n", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday,
								local_tm->tm_hour, local_tm->tm_min);
							strftime(emp->time_of_clock, 17, "%Y-%m-%d %H:%M", local_tm);

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
							Sleep(4000);
							system("cls");
						}
						else if(local_tm->tm_hour < 6)
						{
							printf("未到打卡时间(6:00),打卡失败\n");
							Sleep(2000);
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
							strftime(emp->time_of_clock, 17, "%Y-%m-%d %H:%M", local_tm);
							Sleep(4000);
							system("cls");
						}
						else
						{
							printf("今日还未上班打卡");
							Sleep(2000);
							system("cls");
						}
					}break;

					case 3:
					{
						system("cls");
					}break;
					}
			}

		}
	}
}

void Save(int i)//数据保存
{
    char line[101] = { '\0' }, j_n[8] = { '\0' };
    bool flag = 0;
    switch (i)
    {
    case 1:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            for (int i = 4; i < 11; i++)
            {
                j_n[i - 4] = line[i];
            }
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(j_n, emp->job_num) == 0)
                    {
                        line[0] = emp->name[0];
                        line[1] = emp->name[1];
                        line[2] = emp->name[2];
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
        printf("姓名已保存\n");
    }break;

    case 2:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            char name[4] = { '\0' };
            int id_d = 0, id_i = 0, age_w = 0;
            for (int i = 0; i < 3; i++)
                name[i] = line[i];
            id_d = line[12] - '0';
            id_i = line[14] - '0';
            age_w = ((line[16] - '0') * 10) + line[17] - '0';
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(emp->name, name) == 0 && emp->id_department == id_d && emp->id_identity == id_i && emp->age_of_work == age_w)
                    {
                        for (int j = 4; j < 11; j++)
                        {
                            line[j] = emp->job_num[j - 4];
                        }
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
    }break;

    case 3:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            char name[4];
            int id_d = 0, id_i = 0, age_w = 0;
            for (int i = 0; i < 3; i++)
                name[i] = line[i];
            id_d = line[12]-'0';
            id_i = line[14] - '0';
            age_w = ((line[16] - '0') * 10) + line[17] - '0';
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(emp->name,name)==0&&emp->id_department==id_d&&emp->id_identity==id_i&&emp->age_of_work==age_w)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            if (strcmp(emp->identity, identities[j]) == 0);
                            {
                                line[4] = j + 1;
                                break;
                            }
                        }
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
        printf("职位已保存\n");
    }break;

    case 4:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            for (int i = 4; i < 11; i++)
            {
                j_n[i - 4] = line[i];
            }
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(j_n, emp->job_num) == 0)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (strcmp(emp->department, departments[j]) == 0);
                            {
                                line[6] = j + 1;
                                break;
                            }
                        }
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
        printf("部门已保存\n");
    }break;

    case 5:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            for (int i = 4; i < 11; i++)
            {
                j_n[i - 4] = line[i];
            }
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(j_n, emp->job_num) == 0)
                    {
                        int temp = emp->age_of_work;
                        line[8] = temp / 10;
                        line[9] = temp % 10;
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
        printf("工龄已保存\n");
    }break;

    case 6:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            for (int i = 4; i < 11; i++)
            {
                j_n[i - 4] = line[i];
            }
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(j_n, emp->job_num) == 0)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (strcmp(emp->department, departments[j]) == 0);
                            {
                                line[11] = emp->stage;
                                break;
                            }
                        }
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
        printf("工作状态已保存\n");
    }break;

    case 7:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            for (int i = 4; i < 11; i++)
            {
                j_n[i - 4] = line[i];
            }
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(j_n, emp->job_num) == 0)
                    {
                        for (int j = 13; j < 17; j++)
                        {
                            line[j] = emp->password[j - 13];
                        }
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
        printf("密码已保存\n");
    }break;

    case 8:
    {
        FILE *oldFile = fopen("data.txt", "r");
        if (oldFile == NULL)
        {
            printf("无法打开原始文件\n");
            return;
        }

        FILE *newFile = fopen("temp.txt", "w");
        if (newFile == NULL)
        {
            printf("无法打开临时文件\n");
            fclose(oldFile);
            return;
        }

        while (fgets(line, 100, oldFile) != NULL)
        {
            flag = 0;
            for (int i = 4; i < 11; i++)
            {
                j_n[i - 4] = line[i];
            }
            for (int i = 0; i < 4; i++)
            {
                Employees *emp = com[i].head;
                while (emp != NULL)
                {
                    if (strcmp(j_n, emp->job_num) == 0)
                    {
                        line[18] = emp->Whether_clock;
                        flag = 1;
                    }
                    if (flag == 1)
                        break;
                    emp = emp->next;
                }
                if (flag == 1)
                    break;
            }
            line[strcspn(line, "\n")] = '\0';
            fprintf(newFile, "%s\n", line);
        }
        fclose(oldFile);
        fclose(newFile);
        remove("data.txt");
        int useless = rename("temp.txt", "data.txt");
        printf("打卡状态已保存\n");
    }break;
    }
}


