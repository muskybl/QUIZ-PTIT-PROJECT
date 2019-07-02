void back_instruction()
{
	clear_screen_1();
	gotoxy(4, 3);
	cout << "1. ESC: Quay tro ve.";
	gotoxy(4, 4);
	cout << "2. ' ~ ':Quay ve trang chinh.";
}
void teach_instruction()
{
	clear_screen_1();
	gotoxy(4, 3);
	cout << "1. ESC: Thoat chuong trinh.";
	gotoxy(4, 4);
	cout << "2. Phim dieu huong: Trai, phai.";
	gotoxy(4, 5);
	cout << "3. ENTER: Chon chuc nang.";
}
void class_instruction()
{
	clear_screen_1();
	back_instruction();
	gotoxy(4, 5);
	cout << "3. F7: Sua lop.";
	gotoxy(4, 6);
	cout << "4. INSERT: Them lop.";
	gotoxy(4, 7);
	cout << "5. DELETE: Xoa lop.";
	gotoxy(4, 8);
	cout << "6. ENTER: Chon lop.";
}
void student_instruction()
{
	clear_screen_1();
	back_instruction();
	gotoxy(4, 5);
	cout << "3. F7: Sua sinh vien.";
	gotoxy(4, 6);
	cout << "4. INSERT: Them sinh vien.";
	gotoxy(4, 7);
	cout << "5. DELETE: Xoa sinh vien.";
	gotoxy(4, 8);
	cout << "6. ENTER: Chon sinh vien.";
}
void show_listSubject_instruction()
{
	clear_screen_1();
	back_instruction();
	gotoxy(4, 5);
	cout << "3. ENTER: Chon mon hoc.";
}
void show_listClass_instruction()
{
	clear_screen_1();
	back_instruction();
	gotoxy(4, 5);
	cout << "3. ENTER: Chon lop.";
}
void show_listStudent_instruction()
{
	clear_screen_1();
	back_instruction();
}
void subject_instruction()
{
	clear_screen_1();
	back_instruction();
	gotoxy(4, 5);
	cout << "3. F7: Sua mon hoc.";
	gotoxy(4, 6);
	cout << "4. INSERT: Them mon hoc.";
	gotoxy(4, 7);
	cout << "5. DELETE: Xoa mon hoc.";
}
void question_instruction()
{
	clear_screen_1();
	
	gotoxy(4, 5);
	cout << "1. ESC / ~ : De quay ve.";
	gotoxy(4, 6);
	cout << "2. INSERT: Them cau hoi.";
	gotoxy(4, 7);
	cout << "3. DELETE: Xoa cau hoi.";
	gotoxy(4, 8);
	cout << "4.F7: Sua cau hoi.";
}
void exam_instruction()
{
	clear_screen_1();
	gotoxy(4, 6);
	cout << "1. ESC / '~' de quay ve.";
	gotoxy(4, 7);
	cout << "2. DELETE: Xoa de thi.";
	gotoxy(4, 8);
	cout << "3. INSERT: Them de thi.";
}
void do_quiz()
{
	
	gotoxy(94, 7);
	cout << "1. ENTER: Chon cau hoi.";
	gotoxy(94, 8);
	cout << "2. Phim trai phai: chon cau tra loi.";
	gotoxy(94, 9);
	cout << "3. F8: De nop bai thi.";
}


