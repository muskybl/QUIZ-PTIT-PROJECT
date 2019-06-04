#include <iostream>
#include <iomanip>
#include <ctime>
#include "const.h"
#include "md5.h"
#include "md5.cpp"
#include "mylib.h"
#include "function.h"
#include "background.h"
#include "instruction.h"
#include "menu.h"
#include "linkedlist.h"
#include "tree.h"
#include "teacher_option.h"
#include "student_option.h"
#include "signin.h"

void start() // lay du lieu
{
	load_data();
}
void end() // luu du lieu
{
	save_data();
}

int main()
{
	start();
	sign_in();
	end();
	system("cls");
	gotoxy(0, 30);
}
