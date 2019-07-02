

/*	########################## 		Option console 		##########################	*/
void normal () 
{
	SetColor(WHITE);
	SetBGColor(BLACK);
}
void highlight () 
{
	SetColor(WHITE);
	SetBGColor(BLUE);
}
void show_rectangle(int x, int y, int width, int hight)
{
	SetColor(BLUE);
	gotoxy(x,y);
	cout << char(201);
	for(int i = 1; i < width; i++)
	cout << char(205);
	cout << char(187);
	gotoxy(x,hight + y - 1);
	cout << char(200);
	for(int i = 1; i < width; i++)
	cout << char(205);
	cout << char(188);
	for(int i = y + 1; i < hight + y - 1; i++)
	{
		gotoxy(x,i);
		cout << char(186);
		gotoxy(x + width,i);
		cout << char(186);
	}
	gotoxy(0,0);
	SetColor(WHITE);
}
void color_rectangle(int x, int y, int width, int hight, int color)
{
	SetBGColor(color);
	for(int i = 0; i < hight; i++)
	{
		for(int j = 0; j < width; j++)
		{
			gotoxy(x + j, y + i); cout << " ";
		}
		gotoxy(x + 1, y + i) ; cout << " ";
	}
	SetBGColor(BLACK);
}
void insert_title(int x,int y,int color, int width, int hight, string title)
{
	SetColor(color);
	gotoxy(x + (width - title.length())/2 + 1,y + (hight - 1)/2);
	cout << title;
	SetColor(WHITE);
}

/*	########################## 		Option console 		##########################	*/


/*	########################## 		Clear screen 		##########################	*/


/*	########################## 		Clear screen 		##########################	*/

void clear_screen(int x, int y, int length, int height)
{
	for(int i = 0; i < height; ++i)
	{
		gotoxy(x, i + y);
		for(int j = 0; j < length; ++j)
		{
			cout << " ";
		}
	}
}
void clear_screen_1()
{
	normal();
	clear_screen(3, 3, 34, 6);
}
void clear_screen_2()
{
	normal();
	clear_screen(38, 2, 93, 6);
}
void clear_screen_3()
{
	normal();
	clear_screen(3, 12, 34, 20);
}
void clear_screen_4()
{
	normal();
	clear_screen(39, 9, 91, 23);
}
/*	########################## 		Clear screen 		##########################	*/


/*	########################## 		Keyboard 		##########################	*/
void function_key(char function, int &option)
{
	option = -1;
	while(option == -1)
	{
		function = getch();
		if(function == 0 || function == -32) function = getch();
		switch(function)
		{
			case ENTER:
				{
					normal();
					option = ENTER; // 1
					return ;	
				}
			case ESC:
				{
					normal();
					option = ESC; // 2
					return ;
				}
			case DEL: 
				{
					normal();
					option = DEL; // 3
					return ;
				}
			case INSERT :
				{
					normal();
					option = INSERT; // 4
					return ;
				}
			case EDIT: // f7
				{
					normal();
					option = EDIT; //5 
					return ;	
				}
			case FINISH: //f8
				{
					normal();
					option = FINISH; //6
					return ;
				}
			case HOME:
				{
					normal();
					option = HOME; //6
					return ;
				}
				
			case UP:
				{
					normal();
					option = UP;
					return ;
				}
			case DOWN:
				{
					normal();
					option = DOWN;
					return ;
				}
			case LEFT:
				{
					normal();
					option = LEFT;
					return ;
				}
			case RIGHT:
				{
					normal();
					option = RIGHT;
					return ;
				}
			default : option = -1; break;
		}
	}
}
void line_option(int x, int y, int &number,string s, int &pos, int &option, int &page, int &front, int &rear)
{
	ShowConsoleCursor(0);
	normal();
	char control;
	int posLine = pos % MAX_LINE; // new fix
	while (number == 0) // don't have any value
	{
		function_key(control, option);
		if(option == ESC || option == INSERT || option == HOME) return;
	}
	int limit;
	if(page * MAX_LINE <= number) limit = MAX_LINE;
	else limit = number % MAX_LINE;
	while(posLine < limit)
	{
		highlight();
		gotoxy(x,y + posLine);
		cout << s;
		function_key(control, option);
		if(option >=72 && option <= 80) 
		{ 
			switch(option)
			{
				case UP:
				if(posLine + 1 > 1) // pos bottom
				{
					normal();
					gotoxy(x, y + posLine);
					cout << "    ";
					--pos;
					--posLine;
					highlight();
					gotoxy(x, y + posLine);
					cout << s;
					normal();
				}
				else // pos top
				{
					normal();
					gotoxy(x, y + posLine);
					cout << "    ";
					posLine = limit - 1;
					pos =  rear - 1;
					highlight();
					gotoxy(x, y + posLine);
					cout << s;
					normal();
				}
				break;
				case DOWN:
				if(posLine < limit - 1)	
				{
					normal();
					gotoxy(x,y + posLine);
					cout << "    ";
					++pos;
					++posLine;
					highlight();
					gotoxy(x, y + posLine);
					cout << s;
					normal();
				}
				else
				{
					normal();
					gotoxy(x, y + posLine);
					cout << "    ";
					pos = front ;
					posLine = 0;
					highlight();
					gotoxy(x, y + posLine);
					cout << s;
					normal();
				}
				break;
				case LEFT:
					if(page > 1)
					{
						normal();
						posLine = 0;
						--page;
						return;
					}
					break;
				case RIGHT:
					if(page * MAX_LINE < number) 
					{
						normal();
						posLine = 0;
						++page;
						return;
					}	
					break;
			}
		}
		else return;
	}
	normal();
	ShowConsoleCursor(0);
}

/*	########################## 		Keyboard 		##########################	*/
void reset_page(int &page, int &front, int &rear, int &pos, int &option, int number)
{
	if (number <= front ) page = max(1, page - 1);
	front = page * MAX_LINE - MAX_LINE;
	rear = min(page * MAX_LINE, number);
	if(pos > front && number != 0 && pos < rear)
	{
		switch(option)
		{
			case 3: --pos; break;
			case 4: ++pos; break;
		}
	}
	else pos = front;
	option = -1;
}
void show_total(int x, int y, string s, int number, int max, int page)
{
	gotoxy(x, y);
	cout << s << number << "/" << max;
	gotoxy(x + 4, y + 22);
	cout << "Trang:"<< page << "/";
	cout << number / MAX_LINE + 1;
}

/*	########################## 		String input 		##########################	*/ 
void show_string(string str, int max,int x, int y)
{
	int k = 0;
	int len = str.length();
	int start;
	int end;
	while (true)
	{
		gotoxy(x, k + y);
		start = max * k;
		end = min(max, len - start);
		cout << str.substr(start, end);
		if (end < max) break;
		++k;
	}
}
void show_data_string(int x, int y, int max, int number, string data)
{
	ShowConsoleCursor(0);
	for(int i = 0; i < number; ++i)
	{
		gotoxy(x + i % max , y + i / max);
		cout << " ";
	} 
	show_string(data, max,x, y);
	ShowConsoleCursor(1);
}
void show_password(int x, int y, int const number)
{
	ShowConsoleCursor(0);
	gotoxy(x, y);
	for(int i = 0; i <= number; ++i) cout << " "; // clear line
	gotoxy(x, y);
	for(int i = 0; i < number; ++i) cout << "*"; 
	ShowConsoleCursor(1);
}
void update_string(int x, int y, int max,int number, string data, bool encrypt) // update string and show it
{
	if(encrypt) show_password(x, y, number);
	else show_data_string(x, y, max,number, data);
}
void del_letter(int x, int y, int max, int &number, int &pos, string &data,bool encrypt)
{
	if(number > 0 && pos > 0)
	{
		for(int j = pos; j <= number; j++) data[j - 1] = data[j];
		--number;
		--pos;
		update_string(x, y, max, number, data, encrypt);
		gotoxy(x + pos % max, y + pos / max);
	}
}
void clear(int x, int y, int max, int &number, string &data)
{
	gotoxy(x,y);
	data.assign(number + 1,'\0');		// set value of string become empty
	data.resize(0);
	update_string(x, y, max, number, data, 0);
}
void right_moving_cursor(int x, int y, int &pos, int &number)
{
	if (pos < number)
	{
		++pos;
		gotoxy(x + pos % MAX_CHAR_LINE1, y + pos / MAX_CHAR_LINE1);
	}
}
void left_moving_cursor(int x, int y, int &pos)
{
	if (pos > 0)
	{
		--pos;
		gotoxy(x + pos % MAX_CHAR_LINE1, y + pos / MAX_CHAR_LINE1);
	}
}
void insert_character_to_string(int pos, string &data, char character,bool toup)
{
	if(toup) data[pos] = toupper(character);
	else data[pos] = character;
}
void insert_letter(int x, int y, int max, int &pos, int &number, string &data, char &character, bool encrypt, bool toup)
{
	if(pos == number)
	{
		insert_character_to_string(pos, data, character, toup);
		++number;
		++pos;
		update_string(x, y, max, number, data, encrypt);
		data[pos] = '\0';
	}
	else // somewhere in the line 
	{
		++number;
		for(int j = number ; j >= pos; j--) data[j] = data[j - 1];
		insert_character_to_string(pos, data, character, toup);
		update_string(x, y, max, number, data, encrypt);
		++pos;
	}
	gotoxy(x + pos % max, y + pos / max);
}
bool check_letter(char c)
{
	if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' '))) return 0;
	return 1;
}
void input_info(int x, int y, int maxN, int maxL, string &data, bool encrypt, bool toup, bool onlyLetter) 
{
	// onlyLetter do NOT include number f 0...9
	// maxL is the maxium char per line
	int position = data.length();
	int number = position; 									// the number of line;
	char catchKey;											// catchKey : catch key
	// set value 
	if(number == 0) data.assign(maxN, '\0');					// if: string is empty
	else data.insert(position, maxN - position, '\0'); 		// else: the rest of string is '\0' 
	//
	update_string(x, y, maxL, number, data, encrypt); 				// show the data of string 
	gotoxy(x + number, y);	// goto position need fix
	while(1)
	{
		catchKey = getch();
		switch(catchKey)
		{
			case -32: // special case that catchKey got 2 value 
			{
				catchKey = getch();
				switch(catchKey)
				{
					case LEFT: left_moving_cursor(x, y, position); break;
					case RIGHT: right_moving_cursor(x, y, position, number); break;
					case UP: break;
					case DOWN: break;
					case DEL: clear(x, y, maxL, number, data); break;
				}
			} break;
			case 0: catchKey = getch(); break; // except f1, f2, ... case (contain zero value )
			case ENTER: data.resize(number); return; // end
			case BACKSPACE: del_letter(x, y, maxL, number, position, data, encrypt); break; // delete 1 char
			case ESC: clear(x, y, maxL, number, data); return; //	Delete All
			default : 
			{
				if(number < maxN) // number < max length of string
				{
					if(onlyLetter)
					{
						if(check_letter(catchKey)) insert_letter(x, y, maxL, position, number, data, catchKey, encrypt, toup);
					}
					else insert_letter(x, y, maxL, position, number, data, catchKey, encrypt, toup);
				}
			}
			break;
		}
	}
}

/*	########################## 		String input 		##########################	*/


/*	########################## 		Question process 		##########################	*/
void convert_answer(int answer, int x, int y)
{
	switch(answer)
		{
			case 0: gotoxy(x, y); cout << 'X'; return; // don't know the answer
			case 1: gotoxy(x, y); cout << 'A'; return;
			case 2: gotoxy(x, y); cout << 'B'; return;
			case 3: gotoxy(x, y); cout << 'C'; return;
			case 4: gotoxy(x, y); cout << 'D'; return;
		}
}
void mark_rightAnswer(int x, int y)
{
	SetColor(12);
	gotoxy(x, y); cout << char(251);
	normal();
}
void show_form_ques(int x, int y)
{
	gotoxy(x, y);
	cout << "A:";
	gotoxy(x, y + 1);
	cout << "B:";
	gotoxy(x, y + 2);
	cout << "C:";
	gotoxy(x, y + 3);
	cout << "D:";
}
void swap_ab(int &a, int &b)
{
	int c = a; a = b; b = c;
}
void rand_arr(int *arr, int number) // mix 
{
	for(int i = 0; i < number; ++i) arr[i] = i;
	for(int i = 0; i < number; ++i) swap_ab(arr[i], arr[rand() % number]);
}

/*	########################## 		Question process 		##########################	*/



/*	########################## 		Genaral form 		##########################	*/
void list_class_form(int number, int page)
{
	clear_screen_4();
	show_total(115, 9, "So lop:",number, MAXCLASS, page);	
	gotoxy(VERTICAL2 + 10,8);
	cout << "***   Danh sach cac lop   ***";
	gotoxy(VERTICAL1 + 5,10);
	cout << "| STT |";
	gotoxy(VERTICAL2, 10);
	cout << "|       Ma lop       |";
	gotoxy(VERTICAL3, 10);
	cout << "|       Ten lop      |";
	gotoxy(VERTICAL4, 10);
	cout << "| Si so sv |";
	if(number == 0)
	{
		gotoxy(VERTICAL3 - 18, 12);
		cout << " Danh sach lop trong ! ";
	}
}
void list_student_form(int number, int page)
{
	clear_screen_4();
	show_total(115, 9, "So sv:",number, MAXSTUDENT,page);
	gotoxy(VERTICAL2 + 10, 8);
	cout << "*** Danh sach sinh vien ***";	
	
	// ma lop
	// ten lop
	
	gotoxy(VERTICAL1 + 3, 10);
	cout << "| STT |";
	gotoxy(VERTICAL1 + 11, 10);
	cout << "| Ma sinh vien |";
	gotoxy(VERTICAL2 + 9, 10);
	cout << "|   Ho   |";
	gotoxy(VERTICAL2 + 23, 10);
	cout << "|       Ten dem       |";
	gotoxy(VERTICAL3 + 19, 10);
	cout << "|   Ten   |";
	gotoxy(VERTICAL4 + 7, 10);
	cout << "| GT |";
	if(number == 0)
	{
		gotoxy(VERTICAL3 - 17, 12);
		cout << " Danh sach sinh vien trong ! ";
	}
}
void list_score_form(int number, string subId, string subName, int page)
{
	show_total(115, 9, "So sv:",number, MAXSTUDENT, page);
	gotoxy(VERTICAL2 + 10, 8);
	cout << "*** Danh sach diem thi ***";
	gotoxy(VERTICAL1, 2);
	cout << "Ma mon:" << subId;
	gotoxy(VERTICAL1, 3);
	cout << "Ten mon:"<< subName ;

	gotoxy(VERTICAL1 + 3, 10);
	cout << "| STT |";
	gotoxy(VERTICAL1 + 13, 10);
	cout << "|     Ma sv    |";
	gotoxy(VERTICAL2 + 11, 10);
	cout << "|          Ho va ten sv          |";
	gotoxy(VERTICAL3 + 18, 10);
	cout << "| GT | ";
	gotoxy(VERTICAL4 + 1, 10);
	cout << "| Diem thi |";
	if(number == 0)
	{
		gotoxy(VERTICAL2 + 13,12);
		cout << " Khong co sinh vien de hien thi ! ";
	}
}
void list_subject_form(int x, int y, int number, int page)
{
	show_total(x + VERTICAL2 + 15, y, "So mon:", number, MAXSUBJECT, page);
	gotoxy(x + 32, y);
	cout << "*** Danh sach mon hoc ***";
	gotoxy(x + 4, y + 2);
	cout << "| STT |";
	gotoxy(x + 27, y + 2);
	cout << "|     Ma mon hoc     |";
	gotoxy(x + VERTICAL2 + 5, y + 2);
	cout << "|     Ten mon hoc     |";
	if(number == 0)
	{
		gotoxy(x + VERTICAL1 - 3,y + 4);
		cout << "Danh sach mon hoc trong !";
	}
}
void list_test_form(int x, int y, int number, int page)
{
	show_total(x + VERTICAL2 + 15, y, "Tong de:", number, MAX_N_QUESTION, page);
	gotoxy(x + 32,y);
	cout << "*** Danh sach de thi ***";
	gotoxy(x + 4, y + 2);
	cout << "| STT |";
	gotoxy(x + 20, y + 2);
	cout << "|    Ma de thi    |";
	gotoxy(x + VERTICAL1 + 7, y + 2);
	cout << "|    So cau hoi   |";
	gotoxy(x + VERTICAL2 + 11, y + 2);
	cout << "| Thoi gian(phut) |";
	if(number == 0)
	{
		gotoxy(x + VERTICAL1 - 4, y + 4);
		cout << "Danh sach de thi trong !";
	}
}
void list_question_form(int x, int y, int number, int page)
{
	show_total(x + VERTICAL2 + 15, y, "So cau:",number, MAX_N_QUESTION, page);
	gotoxy(x + 32, y);
	cout << "*** Danh sach cau hoi ***";
	gotoxy(x + 4, y + 1);
	cout << "|   STT   |";
	gotoxy(x + 19, y + 1);
	cout << "|                        Cau hoi                        |";
	gotoxy(x  + VERTICAL2 + 18, y + 1);
	cout << "| Dap an |";
	if(number == 0)
	{
		gotoxy(x + 37, y + 3);
		cout << " Danh sach cau hoi trong ! ";
	}
}
/*	########################## 		Genaral form 		##########################	*/

/*	########################## 		Stuff function 		##########################	*/
void show_info_sub(int x, int y, string id, string name)
{
	gotoxy(x, y);
	cout << "Ma mon: " << id;
	gotoxy(x, y + 1);
	cout <<	"Ten mon: " << name;
}

void show_time_left(int x, int y, int limit, int timePassed)
{
	normal();
	int timeLeft = limit *60 - timePassed;
	clear_screen(x + 1, y, 25, 1);
	gotoxy(x + 5, y);
	if(timeLeft < limit*60) SetColor(4);	
	cout << timeLeft / 3600 << " : " << timeLeft / 60 << " : " << timeLeft % 60;
	
}

/*	########################## 		Stuff function 		##########################	*/




/*		**************************			END			**************************		*/
