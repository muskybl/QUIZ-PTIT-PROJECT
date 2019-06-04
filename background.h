

void show_tittle()
{
	gotoxy(22,2);
	cout << " _______ __     __   _______                    _______         __     __                   \n";
	gotoxy(22,3);
	cout << "|_     _|  |--.|__| |_     _|.----.---.-.----.  |    |  |.-----.|  |--.|__|.-----.--------. \n";
	gotoxy(22,4);
	cout << "  |   | |     ||  |   |   |  |   _|  _  |  __|  |       ||  _  ||     ||  ||  -__|        | \n";
	gotoxy(22,5);
	cout << "  |___| |__|__||__|   |___|  |__| |___._|____|  |__|____||___  ||__|__||__||_____|__|__|__| \n";
	gotoxy(22,6);
	cout << "                                                        |_____|							 \n";
}
void loggin_console()
{
	system("cls");
	show_tittle();
	show_rectangle(1,1,130,32);													// Print form
	color_rectangle(45,10,40,3,BLUE);									// Fill Tittle
	show_rectangle(45,9,40,16);													// Print Loggin shell 
	insert_title(45,10,WHITE,40,4,"***        LOGGIN        ***");		// Insert Tittle
	show_rectangle(46,13,38,4); 												// Type User
	show_rectangle(46,17,38,4); 												// Type Pass
	gotoxy(48, 15);
	cout << "User:";
	gotoxy(48, 19);
	cout << "Pass:";	
}
void teacher_window()
{
	system("cls");
	show_rectangle(1, 1, 130, 32);
	show_rectangle(2, 1, 35, 9); // o huong dan
	show_rectangle(2, 10, 35, 23); // o thong bao
	show_rectangle(38, 7, 92, 26); // o4
	insert_title(4, 2, 10, 31, 1, "*** Huong dan ***");
	insert_title(2, 11, 10, 35, 1, "*** Thong bao ***");
	gotoxy(32,32);
}
void question_window()
{
	system("cls");
	show_rectangle(1, 1, 130, 32);
	show_rectangle(38, 8, 92, 25); // o4
	show_rectangle(2, 10, 35, 23); // o dap an
	show_rectangle(2, 1, 35, 9); // o huong dan
	insert_title(4, 2, 10, 31, 1, "*** Thong tin ***");
	insert_title(2, 11, 10, 35, 1, "*** Dap an ***");
}
void student_window()
{
	system("cls");
	show_rectangle(93, 1, 38, 10); // o2
	show_rectangle(1, 11, 92, 25); // o3
	show_rectangle(93, 11, 38, 25); // o4
	
	insert_title(95, 2, 10, 35, 1, "*** Thong tin ***");
	insert_title(95, 12, 10, 35, 1, "*** Dap an ***");
	show_rectangle(1, 1, 130, 35); // khung ngoai
}

/////////////////////////////////////// CLEAR ///////////////////////////////////////
// seperate screen into 4 part , read from 1...4 . Rules : as reading book 
/*
			_____________________________
		   [	1	    ]		2	    ]
		   [____________]_______________]
		   [		    ]			    ]
		   [	  3     ]		4	    ]
		   [		    ]			    ]
		   [____________]_______________]
*/


///////////////////////////////// END CLEAR /////////////////////////////////

