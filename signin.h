void sign_in();
void user_student(node<Student> *a)
{
	run_student_option(a);
}
void user_admin()
{
	run_teacher_option();
}
void sign_in_form()
{
	system("cls");
	show_tittle();
	show_rectangle(1,1,130,32);													// Print form
}
void close_program() // 1: thoat chuong trinh
{
	sign_in_form();
	if(!notify(50, 13, "Thoat chuong trinh ?")) return sign_in();
	system("cls");
	gotoxy(0, 0);
}
void fail_access() // 1: back sign in
{
	sign_in_form();												// Print form
	show_rectangle(40, 12, 50, 8); // o vien
	show_rectangle(41, 13, 48, 3);
	insert_title(40, 13, WHITE, 48, 3, "Tai khoan / mat khau khong dung. Thu lai ?");
	if(yesno_message(51, 16)) return sign_in();
	return close_program(); // else 
}

bool is_admin(string user, string pass)
{
	string u, p; // u : user, p : pass
	ifstream file("readad.txt");
	file >> u;
	file.ignore();
	file >> p; 
	file.close();
	
	if(u.compare(user) == 0 && p.compare(md5(pass)) == 0) return 1;
	else return 0;
}

void find_user(string user, string pass) // define who is user ?
{
	node<Student> *find;
	for(int i = 0; i < lc.numberClass; i++)
	{
		find = lc.cl[i].listStudent.find(user);
		if(find != NULL) // la hoc sinh
		{
			if(md5(pass).compare(find->data.password) == 0) return user_student(find); // kiem tra mat khau
			else break;
		}
	}
	if(is_admin(user, pass)) return user_admin(); // la admin
	return fail_access();
}
void sign_in()
{
	resizeConsole(1100, 630);
	string user, pass;
	loggin_console();
	
	input_info(54, 15, MAXID, MAX_CHAR_LINE3, user, 0, 1, 0); 
	input_info(54, 19, MAXID, MAX_CHAR_LINE3, pass, 1, 1, 0);
	
	if(yesno_message(50, 21)) return find_user(user, pass); // dong y dang nhap
	return close_program();
}



