/*
	Preferance Code Form
***	Example		: abde
	Function	: ab_de
	Var			: abDe
	Struct		: AbDe
	Const	 	: ABDE
*/
#include <ctime>
using namespace std;
struct Button
{
	int x, y, width, hight;
	string name;
	Button(){}
	Button(int const &x, int const &y, int const &width, int const &hight,string name)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->hight = hight;
		this->name = name;
	}	
	void show_button()
	{
		color_rectangle(x , y, width, hight , BLUE);
		show_rectangle(x , y, width, hight);
		insert_title(x , y , WHITE,width,hight,name);
	}
	void show_empty_button()
	{
		SetBGColor(0);
		color_rectangle(x , y, width, hight , 0);
		show_rectangle(x, y , width , hight);
		insert_title(x, y, GREEN, width, hight, name);
	}
};
void create_button(Button *c,int x, int y, int number, int tabx, int taby, string s[], int width, int hight)
{
	for(int i = 0; i < number; i++)
	{
		c[i] = Button(x + tabx * i,y + taby * i, width, hight,s[i]);
		c[i].show_empty_button();
	}
	c[0].show_button();
}
void move_left(Button *&left, int &pos, int num)
{
	if(pos == 0 )
		{
			left[pos].show_empty_button();
			pos = num - 1;
			left[pos].show_button(); 
		}
	else 
		{
			left[pos].show_empty_button();
			pos -= 1;
			left[pos].show_button();
		}
}
void move_right(Button *&right, int &pos, int num)
{
	if(pos == num - 1)
		{
			right[pos].show_empty_button();
			pos = 0;
			right[pos].show_button();
		}
	else 
		{
			right[pos].show_empty_button();
			pos += 1;
			right[pos].show_button();
		}
}
void move_up(Button *&up,int &pos,int const &num)
{
	if(pos == 0)
		{
			up[pos].show_empty_button();
			pos = num - 1;
			up[pos].show_button(); 
		}
	else 
		{
			up[pos].show_empty_button();
			pos -= 1;
			up[pos].show_button();
		}
}
void move_down(Button *&down,int &pos,int const &num)
{
	if(pos == num - 1)
		{
			down[pos].show_empty_button();
			pos = 0;
			down[pos].show_button();
		}
	else 
		{
			down[pos].show_empty_button();
			down[pos += 1].show_button();
		}
}
int menu_position(Button *controller, int number)
{	
	ShowConsoleCursor(0);
	char catchKey ;
	int position = 0;
	while(1)
	{
		Sleep(1);
		if(kbhit())
		{
			catchKey = getch();
			
//			std::this_thread::sleep_for(std::chrono::seconds());
			switch(catchKey)
			{
				case -32: break;
				case 0: break;
				case LEFT: move_left(controller,position,number);		break;
				case RIGHT: move_right(controller,position,number); 	break;
				case UP: move_up(controller,position,number); 			break;
				case DOWN: move_down(controller,position,number);		break;
				case ENTER: return position;
				case ESC: return -1;;
			}
		}
	}
	return -1;
}
void box_result_message(int x, int y, int const &hight, string title,string mess) // ...
{
	color_rectangle(x ,y , 32, 20, 0);
	show_rectangle(x + 1, y + 1, 29, 3); // title box
	insert_title(x, y + 1, WHITE, 29, 3, title); // title mess
	insert_title(x + 1, y + 3, WHITE, 29, 3, mess); // mess	
	show_rectangle(x, y , 31, hight); // rectange
}
void box_info_message(int x, int y, int const &hight, string title, string info, string mess)
{
	color_rectangle(x ,y , 32, 20, 0);
	show_rectangle(x + 1, y + 1, 29, 3); // title box
	insert_title(x, y + 1, WHITE, 29, 3, title); // title mess
	insert_title(x + 1, y + 3, WHITE, 29, 3, info);
	show_rectangle(x + 1, y + hight - 4, 29, 3); // mess box
	insert_title(x + 1, y + hight - 4, WHITE, 27, 3, mess); // mess
	show_rectangle(x, y , 31, hight); // rectange	
}
bool yesno_message(int x, int y)
{
	color_rectangle(x ,y , 11, 3, 0);
	Button option[2];
	string op[2] = {"   OK   "," CANCEL "};
	create_button(option,x + 2 , y, 2, 14, 0, op, 11, 3);
	return(!menu_position(option, 2)) ;
}
void class_eror_message(int x, int y, string title , int condition, string data, string mess)
{
	ShowConsoleCursor(0);
	color_rectangle(x , y, 31, 20, 0);
	switch(condition)
	{
		case 1:
			{
				box_result_message(x, y, 10, title, mess);
				return;
			} 
		case 2:
			{
				box_info_message(x, y, 10, title, " Danh sach lop day ! ", mess);
				return;
			}
		case 3:
			{
				box_info_message(x, y, 10, title, " Trung ma lop ! ", mess);
				insert_title(x, y + 5, WHITE, 20, 1, data);
				return;
			}
		case 4:
			{
				box_info_message(x, y, 10, title, " Ma lop hoac ten lop bi trong ! ", mess);
				return;
			}
	}
	ShowConsoleCursor(1);
}
void student_eror_message(int x, int y, string title,int condition, string data, string mess)
{
	ShowConsoleCursor(0);
	color_rectangle(x , y, 31, 20, 0);
	switch(condition)
	{
		case 1:
			{
				box_result_message(x, y, 10, title, mess);
				return;
			}
		case 2:
			{
				box_info_message(x, y, 11, title, "Trung ma sinh vien !", mess);
				insert_title(x, y + 5, WHITE, 20, 1, data);
				return;
			}
		case 3:
			{
				box_info_message(x, y, 10, title, "Ho hoac ten khong dung !", mess);
				return;
			} 
		case 4:
			{
				box_info_message(x, y, 10, title, "Ma sinh vien trong !", mess);
				return;
			} 
		case 5:
			{
				box_info_message(x, y, 10, title, "Mat khau trong !", mess);
				return;
			} 
		case 6:
			{
				box_info_message(x, y, 10, title, "Danh sach sv day !", mess);
				return;
			}
	
	}
}
void subject_eror_message(int x, int y, string title,int condition, string data, string mess)
{
	ShowConsoleCursor(0);
	color_rectangle(x , y, 31, 20, 0);
	switch(condition)
	{
		case 1:
			{
				box_result_message(x, y, 10, title, mess);
				return;
			}
		case 2:
			{
				box_info_message(x, y, 10, title, "Trung ma mon hoc !", mess);
				insert_title(x, y + 5, WHITE, 20, 1, data);
				return;
			}
		case 3:
			{
				box_info_message(x, y, 10, title, "Ma mon hoac ten mon trong !", mess);
				return;
			} 
		case 4:
			{
				box_info_message(x, y, 10, title, "Danh sach mon hoc day !", mess);
				return;
			}
	}
}
void test_eror_message(int x, int y, string title, int condition, string data, string mess)
{
	ShowConsoleCursor(0);
	color_rectangle(x , y, 31, 20, 0);
	switch(condition)
	{
		case 1:
			{
				box_result_message(x, y, 10, title, mess);
				return;
			}
		case 2:
			{
				box_info_message(x, y, 11, title, "Trung ma de thi !", mess);
				insert_title(x, y + 5, WHITE, 20, 1, data);
				return;
			}
		case 3:
			{
				box_info_message(x, y, 10, title, "De thi da day !", mess);
				return;
			}
		case 4:
			{
				box_info_message(x, y, 11, title, "So khong hop le !", mess);
				return;
			}
		case 5:
			{
				box_info_message(x, y, 11, title, "Ma de trong !", mess);
				return;
			}
	}
}

bool notify(int x, int y, string info)
{
	gotoxy(x, y);
	ShowConsoleCursor(0);
	color_rectangle(x ,y , 32, 7, 0);
	show_rectangle(x + 1, y + 1, 29, 3); // title box
	insert_title(x, y + 1, WHITE, 29, 3, info); // title mess
	show_rectangle(x, y , 31, 8); // rectange
	return(yesno_message(x + 2, y + 4));
}
bool show_result_info(int x, int y, string info, float score, int correct, int total)
{	
	ShowConsoleCursor(0);
	string ans[] = {"Thi tiep","Thoat "};
	Button r[2];
	cout << fixed << setprecision(2);
	
	color_rectangle(x ,y , 32, 9, 0);
	show_rectangle(x + 1, y + 1, 29, 4); // title box
	insert_title(x, y + 1, WHITE, 29, 3, info); // title mess
	show_rectangle(x, y , 31, 9); // rectange
	
	gotoxy(x + 11, y + 3);
	cout << score << '(' << correct << '/' << total << ')';
	
	create_button(r, x + 3, y + 5, 2, 14, 0, ans, 11, 3);
	return(!menu_position(r, 2));
}


