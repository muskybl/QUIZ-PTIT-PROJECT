//*********************************************************************************************
//											Gobal var
//	ListExam le;
	ListClass lc;   
	ListSubject ls;
	Tree avl;
//											Gobal var	
//*********************************************************************************************
void load_data()
{
	lc.read_file("readlc.txt");
	ls.read_file("readsub.txt");
	avl.read_file("readtree2.txt");
	
//	lc.read_file("writelc.txt");
//	ls.read_file("writesub.txt");
//	avl.read_file("writetree.txt");

}
void save_data()
{
	lc.write_file("writelc.txt");
	ls.write_file("writesub.txt");
	avl.write_file("writetree.txt");
}
//
	
//	
void run_teacher_option(); // admin mode
//*********************************************************************************************
//											HEADER USER OPTION
//*********************************************************************************************

int teacher_option(int x, int y)
{
	
	int teacher_choice;
	Button teach_option[N_OPTION];
	while(1)
	{
		ShowConsoleCursor(0);
		system("cls");
		teacher_window();
		teach_instruction();
		string s[N_OPTION] = {"    Lop    ",
							  " Bang diem  ",
						  	  "Cau hoi thi ",
						   	  "  De thi  ",
							 }; 
		create_button(teach_option, x, y, N_OPTION, 23, 0, s, 21, 5);
		teacher_choice = menu_position(teach_option, N_OPTION);
		if(teacher_choice == -1)
		{
			if(notify(52, 13,"Thoat chuong trinh ?"))
			return -1;
		} 
		else return teacher_choice;	
	}
}
int student_option(int x, int y)
{
	ShowConsoleCursor(0);
	int student_choice;
	string s[N_OPTION] = {"  Chon mon thi ",
						  " So cau hoi thi",
						  " Thoi gian thi ",
						  "  Ket qua thi  ",
						 };
	Button student_option[N_OPTION];
	create_button(student_option, x, y, N_OPTION, 24, 0, s, 18, 5);
	student_choice = menu_position(student_option, N_OPTION);
	return student_choice;
}

//*********************************************************************************************
//											FOOTER USER OPTION	
//*********************************************************************************************



//*********************************************************************************************
//											HEADER PRINF INFOMATION
//*********************************************************************************************


void show_list_class(int number, int page, int front, int rear)
{
	list_class_form(number, page);
	if(number == 0) return;
	lc.show_listclass(39, 11, front, rear);
	
}
void show_liststudent(int number, int page, int pos, int front, int rear)
{
	list_student_form(number, page);
	gotoxy(VERTICAL1, 2);
	cout << "Ma lop: " << lc.cl[pos].classId;
	gotoxy(VERTICAL1, 3);
	cout << "Ten lop: "<<lc.cl[pos].className;
	if(number == 0) return;
	lc.cl[pos].listStudent.show_list_student(39, 11, front, rear);
}
void show_listscore(int posClass, int number, string subId, string subName, int page, int front, int rear)
{
	list_score_form(number, subId, subName, page);
	gotoxy(VERTICAL1, 4);
	cout << "Ma lop:" << lc.cl[posClass].classId;
	gotoxy(VERTICAL1, 5);
	cout << "Ten lop:" << lc.cl[posClass].className; 
	if(number == 0) return;
	lc.cl[posClass].show_listscores(39, 11, front, rear, subId);
}
void show_listsubject(int x, int y, int number, int page, int front, int rear) // 4
{
	list_subject_form(x, y, number, page);
	if(number == 0) return;
	ls.show_list_subject(x, y, front, rear);
}
void show_list_question(TNode *arr[], int *ans, int x, int y, int number, int page, int front, int rear) // 4
{
	list_question_form(x, y, number, page);
	avl.list_question(x + 6, y + 2, arr, ans, front, rear);
}
void show_list_test(int x, int y, int posS, int number, int page, int front, int rear)
{
	list_test_form(x, y, number, page);
	if(number == 0) return;
	ls.show_list_exam(x, y, posS, front, rear);
}
//*********************************************************************************************
//											FOOTER PRINF INFOMATION
//*********************************************************************************************



void class_option(); 
//*********************************************************************************************
//											HEADER STUDENT OPTION
//*********************************************************************************************


void dele_student_option(int posClass, int posStudent)
{
	lc.cl[posClass].listStudent.dele_student(4, 12, posStudent);
	while(kbhit()) cin.ignore();
}
void insert_student_option(int posClass)
{
	lc.insert_student(posClass , 4, 12);
	while(kbhit()) cin.ignore();
}
void edit_info_st_option(int posClass, int posStudent)
{
	lc.changeinfo_student(posClass, posStudent, 4, 12);
	while(kbhit()) cin.ignore();
}

void student_option(int posClass) // 4
{
	int front, rear, number, pages, posStudent, option;
	pages = 1;
	option = -1;
	posStudent = 0;
	system("cls");
	string m = {" -> "};
	teacher_window();
	student_instruction();
	while(1)
	{
		number = lc.cl[posClass].listStudent.numberStudent;
		reset_page(pages, front, rear, posStudent, option, number);
		show_liststudent(number, pages, posClass, front, rear);
		line_option(VERTICAL1 - 1, 11, number, m, posStudent, option, pages, front, rear);
		switch(option)
		{
			case ESC: return class_option(); 
			case DEL: dele_student_option(posClass, posStudent); break;
			case INSERT: insert_student_option(posClass); break;
			case EDIT: edit_info_st_option(posClass, posStudent); break;
			case HOME: return run_teacher_option() ;
		}
	}
}


//*********************************************************************************************
//											FOOTER STUDENT OPTION
//*********************************************************************************************



//*********************************************************************************************
//											HEADER CLASS OPTION
//*********************************************************************************************


void dele_class_option(int pos)
{
	lc.delete_class(4, 12, pos);
	while(kbhit()) cin.ignore();
}
void insert_class_option()
{
	lc.insert_class(4, 12);
	while(kbhit()) cin.ignore();
}

void edit_info_class_option(int pos)
{
	lc.changeinfo_class(4, 12, pos);
	while(kbhit()) cin.ignore();
}
void class_option() // 4
{
	system("cls");
	int front, rear, number, posClass, pages, option;
	pages = 1;
	option = -1;
	posClass = 0;
	string m = {" -> "};
	teacher_window();
	class_instruction();
	while(1)
	{
		number = lc.numberClass;
		reset_page(pages, front, rear, posClass, option, number);
		show_list_class(number, pages, front, rear);
		line_option(VERTICAL1 - 1, 11, number, m, posClass, option, pages, front, rear);
		switch(option)
		{
			case ENTER: return student_option(posClass);
			case ESC: return run_teacher_option();
			case HOME: return run_teacher_option();
			case DEL: dele_class_option(posClass); break;
			case INSERT: insert_class_option(); break;
			case EDIT: edit_info_class_option(posClass); break;
		}	
	}
}


//*********************************************************************************************
//											FOOTER CLASS OPTION
//*********************************************************************************************



//*********************************************************************************************
//											HEADER SCORE OPTION
//*********************************************************************************************


void show_scores(string m, int posClass, int posSubject);
void choose_class(string m);
void choose_subject(string m, int posClass) // 4
{
	system("cls");
	teacher_window();
	int pages, front, rear, number, posSubject, option;
	pages = 1;
	option = -1;
	posSubject = 0;
	show_listSubject_instruction();
	while(1)
	{
		clear_screen_4();
		number = ls.numberSubject;
		reset_page(pages, front, rear, posSubject, option, number);
		show_listsubject(39, 8, number, pages, front, rear);
		line_option(VERTICAL1 - 1, 11, number, m, posSubject, option, pages, front, rear);
		switch(option)
		{
			case ENTER: return show_scores(m, posClass, posSubject);
			case ESC: return choose_class(m);
			case HOME: return run_teacher_option();
		}
	}
}
void choose_class(string m) // 4
{
	system("cls");
	teacher_window();
	int pages, front, rear, number, posClass, option;
	pages = 1;
	show_listClass_instruction();
	while(1)
	{
		clear_screen_4();
		number = lc.numberClass;
		reset_page(pages, front, rear, posClass, option, number);
		show_list_class(number, pages, front, rear);
		line_option(VERTICAL1 - 1, 11, number, m, posClass, option, pages, front, rear);
		switch(option)
		{
			case ENTER: return choose_subject(m, posClass);
			case ESC: return run_teacher_option();
			case HOME: return run_teacher_option();
		}
	}
}
void show_scores(string m, int posClass, int posSubject) // 4
{
	system("cls");
	teacher_window();
	int pages, front, rear, number, posStudent, option;
	pages = 1;
	string subId = ls.find_subject(posSubject)->data.subjectId;
	string subName = ls.find_subject(posSubject)->data.subjectName;
	show_listStudent_instruction();
	while(1)
	{
		clear_screen_4();
		number = lc.cl[posClass].listStudent.numberStudent;
		reset_page(pages, front, rear, posStudent, option, number);
		show_listscore(posClass, number, subId, subName, pages, front, rear);
		line_option(VERTICAL1 - 1, 11, number, m, posStudent, option, pages, front, rear);
		switch(option)
		{
			case ESC: return choose_subject(m, posClass);
			case HOME: return run_teacher_option();
		}	
	}
}
void show_scores() // _score
{
	string m = {" -> "};
	choose_class(m);
}


//*********************************************************************************************
//											FOOTER SCORE OPTION
//*********************************************************************************************
void subject_option(bool);
void ex();
void test_option(int posSubject)
{
	system("cls");
	int option, front, rear, posQuestion, pages, number;
	pages = 1;
	option = -1;
	posQuestion = 0;
	string m = {" -> "};
	string data;
	node<Subject> *p = ls.find(posSubject);
	string subId = p->data.subjectId;
	string subName = p->data.subjectName;
	gotoxy(4, 3);
	cout << "Ma mon: " << subId;
	gotoxy(4, 4);
	cout << "Ten mon: "<< subName;
	exam_instruction();
	teacher_window();
	
	while(1)
	{
		
		number = p->data.le.total;
		
		reset_page(pages, front, rear, posQuestion, option, number);
		show_list_test(39, 8, posSubject, number, pages, front, rear);
		line_option(VERTICAL1 - 1, 11, number, m, posQuestion, option, pages, front, rear);
		switch(option)
		{
			case ENTER: break;
			case ESC: return subject_option(1);
			case HOME: return run_teacher_option();
			case DEL: p->data.le.delete_exam(4, 12, posQuestion); break;
			case INSERT: p->data.le.insert_exam(4, 12); break;
		}
	}
	
}

//*********************************************************************************************

void question_option(int);
	
//*********************************************************************************************


//*********************************************************************************************
//											HEADER SUBJECT OPTION
//*********************************************************************************************


void dele_subject_option(int posSubject)
{
	ls.dele_subject(lc, 4, 12, posSubject);
	while(kbhit()) cin.ignore();
}
void insert_subject_option()
{
	ls.insert_subject(4, 12);
	while(kbhit()) cin.ignore();
}
void edit_subject_option(int posSubject)
{
	ls.change_subject(lc, 4, 12, posSubject);
	while(kbhit()) cin.ignore();
}

void subject_option(bool way)
{
	system("cls");
	int posSubject, option, front, rear, number, pages;
	pages = 1;
	option = -1;
	posSubject = 0;
	string m = {" -> "};
	teacher_window();
	subject_instruction();
	while(1)
	{
		
		number = ls.numberSubject;
		reset_page(pages, front, rear, posSubject, option, number);
		show_listsubject(39, 8, number, pages, front, rear); // new fix
		line_option(39, 11, number, m, posSubject, option, pages, front, rear);
		switch(option)
		{
			case ENTER:
			if(way) return test_option(posSubject);
			else return question_option(posSubject);
			
			case ESC: return run_teacher_option();
			case DEL: dele_subject_option(posSubject); break;
			case INSERT: insert_subject_option(); break;
			case EDIT: edit_subject_option(posSubject); break;
			case HOME: return run_teacher_option();
		}
	}
}



//*********************************************************************************************
//											FOOTER SUBJECT OPTION
//*********************************************************************************************



//*********************************************************************************************
//										QUESTION
//*********************************************************************************************

void show_ques(TNode *arr[], int *ans, int x, int y, int posQuestion) // 2
{
	gotoxy(x, y);
	cout << "C" << posQuestion  + 1 << ": ";
	show_form_ques(x, y + 2);
	arr[posQuestion]->info.show_question(x + 3, y, ans[posQuestion]);
}

void del_question(int x, int y, int key)
{
	string title = "!!!   XOA CAU HOI   !!!";
	string mess1 = "XOA THANH CONG !";
	string mess2 = "XOA THAT BAI !";
	bool dele;
	box_result_message(x, y , 10, title,"");
	dele = yesno_message(x + 1, y + 6);
	if(dele) 
	{
		avl.del_question(key);
		box_result_message(x, y, 10, title, mess1);
	}
	else box_result_message(x, y, 10, title, mess2);
}

void insert_question(string id, int x, int y) // id: subject id // 2
{
	clear_screen(38, 2, 93, 6);
	avl.insert(id, x, y);
}
void change_question(TNode *node, int x, int y)
{
	clear_screen(38, 2, 93, 6);
	avl.change_value(node, x, y);
}

void show_all_answer(int *ans, int number, int x, int y) // answer table // 3
{
//	clear_screen_3();
	int k = 0;
	int tab = 7;
	int nCollum = (number % MAX_LINE != 0) ? number/MAX_LINE + 1 : number / MAX_LINE;
	for(int i = 1; i <= nCollum; ++i) //number Collum
	{
		for(int j = 1; j <= MAX_LINE && k < number; ++j)
		{
			gotoxy(x, y + j);
			cout << k + 1 << ":";
			convert_answer(ans[k++], wherex(), wherey());
		}
		x += tab;
	}
}
void convert_arr_to_ans(TNode *arr[], int *ans, int number)
{
	for(int i = 0; i < number; i++)
	{
		ans[i] = arr[i]->info.rightAnswer;
	}
}
void find_error(int number, TNode *arr[])
{
	gotoxy(2, 36);
	for(int i = 0; i < number; i++)
	{
		cout << "        ";
	}
	gotoxy(2, 36);
	for(int i = 0; i < number; i++)
	{
		cout << arr[i]->key << " ";
	}
	gotoxy(2, 37);
	for(int i = 0; i < 100; i++)
	{
		cout << "        ";
	}
	gotoxy(2, 37);
	avl.list_key();
}
void question_option(int posSubject) // important
{
	int option, front, rear, posQuestion, pages, number, i;
	pages = 1;
	option = -1;
	posQuestion = 0;
	string m = {" -> "};
	node<Subject> *p = ls.find(posSubject);
	string id = p->data.subjectId;
	system("cls");
	
	question_window();
	question_instruction();
	show_info_sub(4, 3, id, p->data.subjectName);
	while(1)
	{
//		clear_screen_2();
		clear_screen_3();
		clear_screen_4(); // clear info ques
		
		number = 0;
		i = 0;
		count_question(avl.Root, id, number);
		TNode *arr[number]; // khai bao mang dia chi 
		int ans[number]; // mang dap an
		
		address_arr(avl.Root, arr, id, i); // thiet lap mang dia chi
		
		reset_page(pages, front, rear, posQuestion, option, number);
		convert_arr_to_ans(arr, ans, number);
		show_all_answer(ans, number, 4, 11);

		show_list_question(arr, ans, 39, 9, number, pages, front, rear);
		
		line_option(VERTICAL1 - 1, 11, number, m, posQuestion, option, pages, front, rear);
		
		if(option != -1) clear_screen_2();
		switch(option)
		{
			case ENTER: show_ques(arr, ans, 38, 2, posQuestion); break; // show chosen question
			case DEL: del_question(4, 12, arr[posQuestion]->key); break;
			case INSERT: insert_question(id, 38, 2); break;
			case EDIT: change_question(arr[posQuestion], 38, 2); break; // edit question
			case ESC: return subject_option(0);
			case HOME: return run_teacher_option();
			default: break;
		}
	}
}



//*********************************************************************************************
//										QUESTION
//*********************************************************************************************

void run_teacher_option()
{
	resizeConsole(1100, 600);
	int option;
	while(1)
	{
		option = teacher_option(39, 2);
		switch(option)
		{
			case -1: return;
			case 0: return class_option();
			case 1: return show_scores();
			case 2: return subject_option(0); // ENTER -> question
			case 3: return subject_option(1); // ENTER -> list test
		}
	}
}


//*********************************************************************************************
//										Student Option
//*********************************************************************************************




//*********************************************************************************************
//										Student Option
//*********************************************************************************************
