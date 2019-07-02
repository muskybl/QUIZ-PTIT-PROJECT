
/* ####################			Step 1			#################### */
// int student_option(int x, int y)
// {
// 	student_window();
	
// }
void start_exam(int, int, int, int, node <Student> *st); // x, y, posQuestion

void st_subject_option(int, int, node <Student> *);
void st_test_option(int x, int y, int posSubject, node <Student> *st) // 3
{
	system("cls");
	int option, front, rear, posTest, pages, number; 
	// posTest : vi tri de thi
	pages = 1;
	option = -1;
	posTest = 0;
	string m = {" -> "};
	node<Subject> *p = ls.find(posSubject);
	number = p->data.le.total;
	while(1)
	{
		system("cls");
		student_window();
		gotoxy(95, 3);
		cout << "Ma mon: " << p->data.subjectId;
		gotoxy(95, 4);
		cout << "Ten mon: "<< p->data.subjectName;
		gotoxy(95, 6);
		cout << "Ma sv: "<< st->data.studentId;
		gotoxy(95, 7);
		cout << "Ten sv: "<< st->data.studentLastName << " " << st->data.studentMiddleName << " " << st->data.studentLastName;
		reset_page(pages, front, rear, posTest, option, number);
		show_list_test(x, y, posSubject, number, pages, front, rear); // danh sach de thi
		line_option(x, y + 3, number, m, posTest, option, pages, front, rear);
		switch(option)
		{
			case ENTER:
			{
				if(notify(30, 17, " Bat dau thi ?")) return start_exam(x, y, posTest, posSubject, st);
				else break;
			} 
			case ESC: return st_subject_option(x, y, st);
		}
	}
}

void st_subject_option(int x, int y, node <Student> *st) // 2
{
	system("cls");
	
	int posSubject, option, front, rear, number, pages;
	pages = 1;
	option = -1;
	posSubject = 0;
	string m = {" -> "};
	number = ls.numberSubject;
	while(1)
	{
		system("cls");
		student_window();
		reset_page(pages, front, rear, posSubject, option, number);
		show_listsubject(x, y, number, pages, front, rear);
		line_option(x, y + 3, number, m, posSubject, option, pages, front, rear);
		switch(option)
		{
			case ENTER:
			{
				node<Subject> *p = ls.find(posSubject);
				if(st->data.listScore.find_subject_score(p->data.subjectId) != NULL) // neu sv da thi
				{
					if(notify(30, 17, "Sv da thi mon nay! Thoat ?")) return;
					else break;
				} 
				else return st_test_option(x, y, posSubject, st);
			} 
			case ESC: if(notify(30, 17, "Thoat chuong trinh ?")) return;
		}
	}
}

void mix_ques(TNode *exam[], TNode *arr[], int limit, int number)
{
	int temp[number];
	rand_arr(temp, number);
	for(int i = 0; i < limit; i++) exam[i] = arr[temp[i]]; // Xao tron cau hoi	
}
/* ####################			Step 1			#################### */


/* ####################			Step 2			#################### */
void do_ques(TNode *ques[], int *anSheet, int x, int y, int posQues) // 5
{
	
	string ans[] = {"A", "B", "C", "D"};
	show_ques(ques, anSheet, x, y, posQues);
	Button r[4];
	create_button(r, x, y + 6, 4, 5, 0, ans, 4, 3);
	anSheet[posQues] = menu_position(r, 4) + 1;
}
void save_score(node<Student> *st, string subId, float score)
{
	st->data.listScore.insert_score(subId, score);
}
void show_result(int x, int y, node<Student> *st, float score, int correctAns, int n) // n la tong so cau
{
	if(show_result_info(x, y, "Ket qua thi :", score, correctAns, n)) return st_subject_option(2, 12, st);
}
void hand_in(TNode *ques[], int n, int *anSheet, node<Subject> *su, int x, int y, node<Student> *st, bool force) // 6 nop bai
{
	int correctAns = 0;
	float score = 0.0;
	for(int i = 0; i < n; i++) if(ques[i]->info.rightAnswer == anSheet[i]) correctAns++;
	score = correctAns * (10.0 / n);
	if(force) // bat buoc nop bai
	{
		save_score(st, su->data.subjectId, score);
		return show_result(x, y, st, score, correctAns, n); // n la tong so cau
	}
	if(notify(x, y, "Nop bai ?")) // else khong ep nop bai
	{	
		save_score(st, su->data.subjectId, score);
		return show_result(x, y, st, score, correctAns, n); // n la tong so cau
	}
}

bool time_up(clock_t start, clock_t end, int limit) // limit: minute
{
	int timePassed = int((end - start) / CLOCKS_PER_SEC);
	return timePassed > limit * 60 ? 1:0;
}
void start_exam(int x, int y, int posTest, int posSubject, node <Student> *st) // 4
{
	int option, front, rear, posQuestion, pages, number, i, time, nQuestion;;
	pages = 1; option = -1; posQuestion = number = i = 0;
	string id, name, m = {" -> "};
	
	node<Subject> *p = ls.find(posSubject);
	node<Exam> *e = p->data.le.find_exam(posTest);
	id = p->data.subjectId;
	name = p->data.subjectName;
	count_question(avl.Root, id, number); // dem so luong cau hoi trong ds	
	nQuestion = min(e->data.nQues, number); // So luong cau hoi trong de thi
	time = e->data.time;
	TNode *arr[number]; // mang luu dia chi ds cau hoi
	TNode *ques[nQuestion];
//	
	int ansSheet[nQuestion] = { }; // khoi tao dap an ' X '	
	address_arr(avl.Root, arr, id, i); // mang dia chi ds cau hoi
	
	mix_ques(ques, arr, nQuestion, number); // tron cau hoi
	show_info_sub(x + VERTICAL3 + 2, y - 9, id, p->data.subjectName);
	clock_t begin = clock();
	clock_t end;
//	counter(94, 7, time);
	while(1)
	{
		system("cls");
		student_window();
		do_quiz();
		gotoxy(95, 3);
		cout << "Ma mon: " << id;
		gotoxy(95, 4);
		cout << "Ten mon: "<< name;
		reset_page(pages, front, rear, posQuestion, option, nQuestion);
		show_all_answer(ansSheet, nQuestion, 94, 12);
		show_list_question(ques, ansSheet, x, y, nQuestion, pages, front, rear);
		
		show_time_left(100, 6, time, int((clock() - begin) / CLOCKS_PER_SEC));
		
		line_option(2, 14, nQuestion, m, posQuestion, option, pages, front, rear);
		if(time_up(begin, clock(), time))
		{
			hand_in(ques, nQuestion, ansSheet, p, 30, 17, st, 1); // n la tong so cau
			return;
		}
		switch(option)
		{
			case ENTER:
			{
				do_ques(ques, ansSheet, 2, 2, posQuestion); break; // chosen question
				end = clock();
				if(time_up(begin, clock(), time))
				{
					hand_in(ques, nQuestion, ansSheet, p, 30, 17, st, 1); // n la tong so cau
					return;
				}
			} 
			case FINISH: hand_in(ques, nQuestion, ansSheet, p, 30, 17, st, 0); return; 
			default: break;
		}
		
	}
}

/* ####################			Step 2			#################### */

void run_student_option(node <Student> *st) // 1
{	
	resizeConsole(1100, 630);
	return st_subject_option(2, 12, st);
	
}
