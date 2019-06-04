#include <fstream>

using namespace std;
template  <typename T>
struct node
{
	T data;
	node *next;
	node()
	{
		next = NULL;
	}
};
template  <typename T>
class List
{
	public:
	node<T> *first;
	List()
	{
		first = NULL;	
	}
	void insert(node<T> *value)
	{
		if (first == NULL)
			first = value;
		else
		{
			node<T> *q = first;
			for (; q->next != NULL; q = q->next) {}
			q->next = value;
		}
	}
	void insert_value(T value)
	{
		node<T> *p = new node<T>;
		p->data = value;
		
		insert(p);
	}
	
	node<T> *find(string id)
	{
		node<T> *find = first;
		while(find != NULL)
		{
			if(find->data.is_existed(id)) return find;
			find = find->next;
		}
		return NULL;
	}
	node<T> *find(int const &pos)
	{
		int i = 0;
		node<T> *f = first;
		while(i != pos)
		{
			f = f->next;
			++i;
		}
		return f;
	}
	void remove(node<T> *d)
	{
		if(d == first)
			first = first->next;
		else
		{
			node<T> *q = first;
			for (; q->next != d; q = q->next) {}
			q->next = d->next;
		}
		delete d;
	}
	void show(int x, int y, int front, int rear)
	{
		int number = front + 1;
		int line = 0;
		int count = 0;
		node<T> *tmp = first;
		while(count != front)
		{
			tmp = tmp->next;
			++count;
		}
		while(count != rear)
		{
			gotoxy(x, y + line);
			cout << number;
			tmp->data.show(x, y + line);
			tmp = tmp->next;
			++number;
			++count;
			++line;
		}
	}
	void clear()
	{
		node<T> *clear;
		while(first != NULL)
		{
			clear = first;
			first = clear->next;
			delete clear;
		}
	}

	~List()
	{
		clear();
	}
};


struct Score
{
	string subjectId;
	float score;
	Score() : subjectId{'\0'}, score{'0'} {}
	bool is_existed(string);
	void show(int, int);
	void change_id_score(string);
	void read_file(ifstream &);
	void write_file(ofstream &);
};

bool Score :: is_existed(string id)
{
	return (subjectId.compare(id) == 0);
}
void Score :: show(int x, int y)
{
	gotoxy(x + VERTICAL2 + 14 , y);
	cout << score;
}
void Score :: change_id_score(string const newId)
{
	subjectId = newId;
}
void Score :: read_file(ifstream &file)
{
	getline(file, subjectId, '@');
	file >> score;
}
void Score :: write_file(ofstream &file)
{
	file << subjectId << "@";
	file << score << " ";
}
class ListScore : public List<Score>
{
	public:
	int numberScore = 0;
	void insert_score(string, float);
	void show_score(int, int, string);
	void dele_score(string);
	node<Score> * find_subject_score(string);
	void change_id_score(string, string);
	void dele_all();
	void read_file(ifstream &);
	void write_file(ofstream &);
	
};
void ListScore :: insert_score(string id, float score)
{
	Score data;
	data.subjectId = id;
	data.score = score;
	insert_value(data);
	++numberScore;
}
void ListScore :: show_score(int x, int y, string subjectId)
{
	node<Score> *p = first;
	while(p != NULL)
	{
		if(!(p->data.subjectId.compare(subjectId)))
		{
			p->data.show(x, y);
			return;
		}
		p = p->next; 
	}
	gotoxy(x + VERTICAL2 + 14, y);
	cout << "Chua thi";
}
void ListScore :: dele_score(string idSubject)
{
	node<Score> *p;
	p = find(idSubject);
	if(p == NULL) return;
	remove(p);
	--numberScore;

}
node<Score> * ListScore :: find_subject_score(string id)
{
	return find(id);
}
void ListScore :: change_id_score(string oldId,  string newId)
{
	node<Score> *p;
	p = find(oldId);
	if(p == NULL) return;
	p->data.change_id_score(newId);
}
void ListScore :: read_file(ifstream &file)
{	
	file >> numberScore;
	for(int i = 0; i < numberScore; ++i)
	{
		Score sc;
		sc.read_file(file);
		insert_value(sc);
	}
}
void ListScore :: write_file(ofstream &file)
{
	file << numberScore << endl;
	node<Score> *sc = first;
	for(int i = 0; i < numberScore; ++i)
	{
		sc->data.write_file(file);
		file << '\n';
		sc = sc->next;
	}
}
void ListScore :: dele_all()
{
	clear();
}
struct Student
{
	string studentId;
	string studentFirstName;	// ten goi sv
	string studentMiddleName;	// ten dem sv
	string studentLastName; // ho sv
	string password;
	string pass;
	bool male;
	ListScore listScore;
	bool input(int, int, int &);
	bool is_existed(string);
	void show(int, int);
	void change_student(Student);
	void dele(); // delete all score
	void show_score(int, int, string);
	void dele_score(string);
	void change_id_score(string, string);
	void read_file(ifstream &);
	void write_file(ofstream &);
};
bool Student :: input(int x,int y, int &eror)
{
	Button sex[2];
	string m[2] = {" Nam ", "  Nu "};
	gotoxy(x,y);
	cout << "Ma sv : ";
	input_info(x + 7, y, MAXID , MAX_CHAR_LINE3, studentId, 0, 1, 0);
	gotoxy(x, y + 1);
	cout << "Ho sv : ";
	input_info(x + 7, y + 1, MAXNAME, MAX_CHAR_LINE3, studentLastName, 0, 1, 1);
	gotoxy(x, y + 2);
	cout << "Ten dem sv : ";
	input_info(x + 12, y + 2, MAXMIDDLE , MAX_CHAR_LINE3 + 5, studentMiddleName, 0, 1, 1);
	gotoxy(x, y + 3);
	cout << "Ten sv : ";
	input_info(x + 8, y + 3, MAXNAME, MAX_CHAR_LINE3, studentFirstName, 0, 1, 1);
	gotoxy(x, y + 4);
	cout << "Mat khau : ";
	input_info(x + 10, y + 4, MAXID, MAX_CHAR_LINE3, password, 1, 0, 0);
	gotoxy(x,y + 6);
	cout << "Gioi tinh : ";
	create_button(sex, x + 11, y + 5, 2, 10, 0, m, 8, 3);
	male = !menu_position(sex, 2);
	if(studentId[0] == '\0')
	{
		eror = 4;
		return 0;
	}
	if(studentLastName[0] == '\0' || studentFirstName[0] == '\0') //  kiem tra co so hay khong ...
	{
		eror = 3;
		return 0;
	 }
	if(password[0] == '\0')
	{
		eror = 5;
		return 0;
	}
	password = md5(password);
	return 1;
}
bool Student :: is_existed(string id)
{
	return ((studentId.compare(id)) == 0);
}
void Student :: show(int x, int y)
{
	gotoxy(x + 8, y);
	cout << studentId;
	gotoxy(x + 27, y);
	cout << studentLastName;
	gotoxy(x + VERTICAL1 + 1, y);
	cout << studentMiddleName;
	
	gotoxy(x + VERTICAL2 + 6, y);
	cout << studentFirstName;
	
	gotoxy(x + VERTICAL2 + 20, y);
	if(male) cout << "nam";
	else cout <<"nu";
}
void Student :: change_student(Student st)
{
	studentId = st.studentId;
	studentFirstName = st.studentFirstName;
	studentMiddleName = st.studentMiddleName;
	studentLastName = st.studentLastName;
	password = st.password;
	male = st.male;
}
void Student :: dele()
{
	listScore.dele_all();
}
void Student :: show_score(int x, int y, string subjectId)
{
	gotoxy(x + 10, y);
	cout << studentId;
	gotoxy(x + 30, y);
	cout << studentLastName << " " << studentMiddleName << " " << studentFirstName;
	gotoxy(x + VERTICAL2 + 5, y);
	if(male) cout << "Nam";
	else cout << "Nu";
	listScore.show_score(x, y, subjectId);
}
void Student :: dele_score(string idSubject)
{
	listScore.dele_score(idSubject); //testing
}
void Student :: change_id_score(string oldId,string newId)
{
	listScore.change_id_score(oldId, newId);
}
void Student :: read_file(ifstream &file)
{
	file.ignore();
	getline(file, studentId,'@');
	file.ignore();
	getline(file, studentLastName,'@');
	file.ignore();
	getline(file, studentMiddleName,'@');
	file.ignore();
	getline(file, studentFirstName,'@');
	file >> password >> male;
	listScore.read_file(file);
}
void Student :: write_file(ofstream &file)
{
	file << studentId << "@ ";
	file << studentLastName << "@ ";
	file << studentMiddleName << "@ ";
	file << studentFirstName << "@ " << password << ' ' << male << ' ';
	listScore.write_file(file);
}


class ListStudent : public List<Student>
{
	public:
	int numberStudent = 0;
	void insert_student(Student);
	node<Student> *findSt(int);
	void dele_all_student();
	void dele_student(int, int, int &);
	void show_list_student(int, int, int, int);
	void show_listscores(int, int, int, int, string);
	void dele_score(string);
	void change_id_score(string, string);
	void read_file(ifstream &);
	void write_file(ofstream &);
};
void ListStudent :: insert_student(Student data)
{
	insert_value(data);
	++numberStudent;
}
node<Student> *ListStudent :: findSt(int posSt)
{
	return find(posSt);
}
void ListStudent :: dele_all_student()
{ 
	node<Student> *p = first;
	while(p != NULL)
	{
		p->data.dele();
		p = p->next;
	}
	numberStudent = 0;
	clear();
}
void ListStudent :: dele_student(int x, int y, int &posStudent)
{
	if(numberStudent == 0) return;
	string title = "!!! XOA SINH VIEN !!!";
	string mess1 = "XOA THANH CONG !";
	string mess2 = "XOA THAT BAI !";
	node<Student> *findMyid = first;
	bool n;
	findMyid = find(posStudent);
	box_result_message(x, y, 10, title,"");
	n = yesno_message(x + 1,y + 5);
	if(!n) 
	{
		student_eror_message(x, y, title, 1,"",mess2);
		return;
	}
	findMyid->data.dele();
	remove(findMyid);
	student_eror_message(x, y, title, 1, "", mess1);
	--numberStudent;
	return;
	 
}
void ListStudent :: show_list_student(int x, int y, int front, int rear)
{
	show(x + 6, y, front, rear);
}
void ListStudent :: show_listscores(int x, int y, int front, int rear,string subjectId)
{
	node<Student> *p = first;
	int number = front + 1;
	int line = 0;
	int count = 0;
	while(count != front)
	{
		p = p->next;
		++count;
	}
	while(count != rear)
	{
		gotoxy(x, y + line);
		cout << number;
		p->data.show_score(x, y + line, subjectId);
		p = p->next;
		++number;
		++count;
		++line;
	}
}
void ListStudent :: dele_score(string idSubject)
{
	node<Student> *p = first;
	while(p != NULL)
	{
		p->data.dele_score(idSubject);
		p = p->next;
	}
}
void ListStudent :: change_id_score(string oldId,string newId)
{
	node<Student> *p = first;
	while(p != NULL)
	{
		p->data.change_id_score(oldId, newId);
		p = p->next;
	}
}
void ListStudent :: read_file(ifstream &file) // right
{	
	file >> numberStudent;
	for(int i = 0; i < numberStudent; ++i)
	{
		node<Student> *st = new node<Student>;
		st->data.read_file(file);
		insert(st);
	}
}
void ListStudent :: write_file(ofstream &file)
{
	file << numberStudent << '\n';
	node<Student> *p = first;
	for(int i = 0; i < numberStudent; ++i)
	{
		p->data.write_file(file);
		p = p->next;
		
	}
}

struct Class
{
	string classId;
	string className;
	ListStudent listStudent;
	bool input_class(int, int, int &);
	bool is_existed(string);
	void change_class(Class);
	bool insert_student_to_class(Student);
	void show(int, int);
	void show_listscores(int, int, int, int,string);
	void delete_info_class();
	void read_file(ifstream &); // right 4
	void write_file(ofstream &);
};


bool Class :: input_class(int x, int y, int &error)
{
	gotoxy(x , y);
	cout << "Ma lop:";
	input_info(x + 7, y, MAXID, MAX_CHAR_LINE3, classId, 0, 1, 0);									// input id	
	gotoxy(x, y + 1);
	cout << "Ten lop:";
	input_info(x + 8, y + 1, MAXMIDDLE, MAX_CHAR_LINE3 + 5, className, 0, 1, 0);								// input name
	if(classId[0] == '\0' || className[0] == '\0')
	{
		error = 4;
		return 0;
	}
	error = 1;
	return 1;
}
bool Class :: is_existed(string id)
{
	return ((classId.compare(id) == 0));
}
void Class :: change_class(Class change)
{
	classId = change.classId;
	className = change.className;
}
bool Class :: insert_student_to_class(Student data)
{
	listStudent.insert_student(data);
}
void Class :: show(int x, int y)
{
	gotoxy(x, y);
	cout << classId;
	gotoxy(x + VERTICAL1 - 10, y);
	cout << className;
	gotoxy(x + VERTICAL2 - 5, y);
	cout << listStudent.numberStudent;
}
void Class :: show_listscores(int x, int y, int front, int rear,string subjectId)
{
	listStudent.show_listscores(x + 6, y, front, rear, subjectId);
}
void Class :: delete_info_class()
{
	listStudent.dele_all_student();
}
void Class :: read_file(ifstream &file) // right 4
{
	file.ignore();
	getline(file,classId, '@' );
	file.ignore();
	getline(file,className, '@' );
	listStudent.read_file(file);
}
void Class :: write_file(ofstream &file)
{
	file << classId << "@ " << className << "@";
	listStudent.write_file(file);
}

class ListClass
{
	public:
	int numberClass = 0;
	Class cl[MAXCLASS];
	int empty()
	{
		return numberClass;
	}
	bool full();
	int search_class(string); //right
	node<Student> *find_student(string, int &); // find student in listclass , wClass: which class st in;
	void insert_student(int, int, int);
	void insert_class(int, int); // right
	void changeinfo_student(int, int, int, int);
	void changeinfo_class(int, int, int);
	void delete_class(int, int,int);
	void show_listclass(int , int , int &, int &); // right
	void read_file(string);
	void write_file(string);
};

bool ListClass :: full()
{
	return (numberClass == MAXCLASS);
}
int ListClass :: search_class(string classId)
{
	for(int i = 0; i < numberClass; ++i)
	{
		if(cl[i].is_existed(classId)) return i;
	}
	return -1;
}
node<Student> *ListClass :: find_student(string id, int &wClass) // find student in listclass , wClass: which class st in;
{
	node<Student> *find;
	for (int i = 0; i < numberClass; ++i)
	{
		find = cl[i].listStudent.find(id);
		if( find != NULL)
		{
			wClass = i;
			return find; // return the address of student 
		} 
	}
	wClass = -1;
	return NULL;
}
void ListClass :: insert_student(int posClass, int x, int y)
{
	string title = "!!! THEM SINH VIEN !!!";
	string mess1 = "THEM THANH CONG !";
	string mess2 = "THEM THAT BAI !";
	if(cl[posClass].listStudent.numberStudent == MAXSTUDENT)
	{
		student_eror_message(x, y, title, 6, "", mess2);
		return;
	} 
	bool n;
	int option = -1;
	int wClass;
	Student st;
	box_result_message(x, y, 16, title,"");
	if(st.input(x + 1, y + 4, option))
	{
		n = yesno_message(x + 1,y + 12);
		if(!n) 
		{
			student_eror_message(x, y, title, 1, "", mess2);
			return;
		}
		node<Student> *p = find_student(st.studentId, wClass); // compile lib error / fixed			
		if(p != NULL)
		{
			student_eror_message(x, y, title, 2, st.studentId, mess2);
			gotoxy(x + 5, y + 6);
			cout << "Cua lop:" << cl[wClass].classId;
			return;
		}
		cl[posClass].insert_student_to_class(st);
		student_eror_message(x, y, title, 1, "", mess1);
		return;
	}	
	student_eror_message(x, y, title, option, "", mess2);
	return;
}
void ListClass :: insert_class(int x, int y)
{
	int n, pos = -1;
	int option = -1;
	string title = "!!! THEM LOP !!!";
	string mess1 = "THEM THANH CONG !";
	string mess2 = "THEM THAT BAI !";
	Class clx;
	box_result_message(x, y, 10, title,"");
	if(clx.input_class(x + 1, y + 4, option))
	{
		n = yesno_message(x + 1,y + 6);
		if(!n) 
		{
			class_eror_message(x, y, title, 1, "", mess2);
			return ;
		}
		pos = search_class(clx.classId);
		if(pos != -1)
		{
			class_eror_message(x, y, title, 3, clx.classId, mess2);
			return ;
		}
		if(full())
		{
			class_eror_message(x, y, title, 2,"", mess2);
			return ;
		}
		cl[numberClass] = clx;
		++numberClass;	
		class_eror_message(x, y, title, 1,"", mess1);
		return;
	}
	class_eror_message(x, y, title, option,"", mess2);
}
void ListClass :: changeinfo_student(int posClass, int posStudent, int x, int y)
{
	if(cl[posClass].listStudent.numberStudent == 0) return;
	Student st;
	node<Student> *findMyid;
	node<Student> *p;
	int i = 0;
	int option = -1;
	bool n;
	int wClass;
	string title = "!!! SUA SINH VIEN !!!";
	string mess1 = "SUA THANH CONG !";
	string mess2 = "SUA THAT BAI !";
	box_result_message(4, y, 16, title,"");
	
	findMyid = cl[posClass].listStudent.findSt(posStudent);
	
	st.studentId = findMyid->data.studentId;
	st.studentLastName = findMyid->data.studentLastName;
	st.studentMiddleName = findMyid->data.studentMiddleName;
	st.studentFirstName = findMyid->data.studentFirstName;
	st.male = findMyid->data.male;
	if(st.input(x + 1, y + 4, option))
	{
		n = yesno_message(x + 1,y + 12);
		if(!n) 
		{
			student_eror_message(x, y, title, 1,"",mess2);
			return;
		}
		p = find_student(st.studentId, wClass);
		if(p != findMyid && p != NULL)
		{
			student_eror_message(x, y, title, 2, st.studentId, mess2);
			gotoxy(x + 5, y + 6);
			cout << "Cua lop:" << cl[wClass].classId;
			return;
		}
		findMyid->data.change_student(st);
		student_eror_message(x, y, title, 1, "", mess1);
		return;
	}
	student_eror_message(x, y, title, option, "", mess2);
	return;
	
}
void ListClass :: changeinfo_class(int x, int y, int pos)
{
	Class clx;
	int n;
	int option = -1;
	int f = -1;
	string title = "!!!   SUA LOP  !!!";
	string mess1 = "SUA THANH CONG !";
	string mess2 = "SUA THAT BAI !";
	box_result_message(x, y, 10, title,"");
	clx.classId = cl[pos].classId;
	clx.className = cl[pos].className;
	
	if(clx.input_class(x + 1, y + 4, option))
	{
		n = yesno_message(x + 1,y + 6);
		if(!n)
		{
			class_eror_message(x, y, title, 1, "", mess2);
			return ;
		}
		f = search_class(clx.classId);
		if(f != -1 && f != pos)
		{
			class_eror_message(x, y, title, 3, clx.classId, mess2);
			return ;
		}
		cl[pos].change_class(clx);
		class_eror_message(x, y, title, 1, "", mess1);
		return;
	}
		class_eror_message(x, y, title, option, "", mess2);
		return;
}
void ListClass :: delete_class(int x, int y,int n_class)
{
	string title = "!!!   XOA LOP   !!!";
	string mess1 = "XOA THANH CONG !";
	string mess2 = "XOA THAT BAI !";
	bool dele;
	box_result_message(x, y , 10, title,"");
	dele = yesno_message(x + 1, y + 6);
	if(dele) 
	{
		cl[n_class].delete_info_class();
		for(int i = n_class; i < numberClass; i++)
		{
			cl[i] = cl[i + 1];
		}
		--numberClass;
		class_eror_message(x, y, title, 1, "", mess1);
	}
	else class_eror_message(x, y, title, 1, "", mess2);
	ShowConsoleCursor(1);
}
void ListClass :: show_listclass(int x, int y, int &front, int &rear)
{
	int j = 0;
	for(int i = front; i < rear; ++i)
	{
		gotoxy(x + 8, y + j);
		cout << (i + 1);
		cl[i].show(x + 24,y + j);
		++j;
	}
}
void ListClass :: read_file(string fileName)
{
	ifstream read(fileName);
	read >> numberClass;
	for(int i = 0; i < numberClass; ++i)
	{
		cl[i].read_file(read);
	}
	read.close();
}
void ListClass :: write_file(string filename)
{
	ofstream write(filename);
	write << numberClass << endl;;
	for(int i = 0; i < numberClass; ++i) cl[i].write_file(write);
	write.close(); 
}





//*********************************************************************************************
//											Exam & List Exam
//*********************************************************************************************
struct Exam
{
	
	string examCode; // ma de thi
	int nQues; // so luong cau hoi thi
	int time; // thoi gian thi tinh bang phut
	bool is_existed(string);
	void show(int, int);
	bool input_exam(int, int, int &);
	void read_exam(ifstream &);
	void write_exam(ofstream &);
};
bool Exam::is_existed(string eC)
{
	return (examCode.compare(eC) == 0) ? 1 : 0;
}
void Exam::show(int x, int y)
{
	gotoxy(x + 19, y); cout << examCode;
	gotoxy(x + 46, y); cout << nQues;
	gotoxy(x + VERTICAL2 + 7, y); cout << time;
}
bool Exam::input_exam(int x, int y, int &error)
{
	gotoxy(x , y);
	cout << "Ma de:";
	input_info(x + 7, y, MAXID, MAX_CHAR_LINE3, examCode, 0, 1, 0);
	
	gotoxy(x, y + 1);
	cout << "So cau:";
	cin >> nQues;
	nQues = min(nQues, MAX_N_QUESTION);
	gotoxy(x, y + 2);
	cout << "Thoi gian:";
	cin >> time;
	if(examCode[0] == '\0')
	{
		error = 5;
		return 0;
	}
	error = 4;
	return 1;
}

void Exam:: read_exam(ifstream &file)
{
	file.ignore(); // clear endl
	getline(file, examCode, '@');
	file.ignore(); // clear space
	file >> nQues;
	file.ignore(); // clear space
	file >> time;
}
void Exam:: write_exam(ofstream &file)
{
	file << examCode << "@ ";
	file << nQues << " " << time;
} 

class ListExam : public List<Exam>
{
	public:
	string subId; // ma mon hoc cua de thi
	int total; // tong so de thi
	ListExam()
	{
		total = 0;
	}
	node<Exam> *find_exam(int posExam)
	{
		find(posExam);
	}
	void insert_exam(int, int);
	void show_list_exam(int, int, int, int);
	void delete_exam(int, int , int);
	void read_file(ifstream &);
	void write_file(ofstream &);
};
void ListExam::read_file(ifstream &file)
{
	file >> total;
	for(int i = 0; i < total; ++i)
	{
		node<Exam> *exam = new node<Exam>;
		exam->data.read_exam(file);
		insert(exam);
	}
}

void ListExam::write_file(ofstream &file)
{
	file << total;
	node<Exam> *exam = first;
	for(int i = 0; i < total; ++i)
	{
		file << endl;
		exam->data.write_exam(file);
		exam = exam->next;
	}
}

void ListExam::show_list_exam(int x, int y, int front, int rear)
{
	show(x + 6, y + 3, front, rear);
}
void ListExam::insert_exam(int x, int y)
{
	
	string title = "!!! THEM DE THI !!!";
	string mess1 = "THEM THANH CONG !";
	string mess2 = "THEM THAT BAI !";
	if(total == MAX_N_EXAM)
	{
		test_eror_message(x, y, title, 3, "", mess2);
		return;
	} 
	bool n;
	int option = -1;
	Exam exam;
	box_result_message(x, y, 10, title,"");
	if(exam.input_exam(x + 1, y + 4, option))
	{
		n = yesno_message(x + 1, y + 6);
		if(!n) 
		{
			test_eror_message(x, y, title, 1, "", mess2);
			return ;
		}
		node<Exam> *p = find(exam.examCode); // compile lib error / fixed
		if(p != NULL)
		{
			test_eror_message(x, y, title, 2, exam.examCode, mess2);
			return;
		}
		insert_value(exam);
		++total;
		test_eror_message(x, y, title, 1, "", mess1);
		return;
	}
	test_eror_message(x, y, title, option, "", mess2);
}
void ListExam::delete_exam(int x, int y, int pos)
{
	
	if(total == 0) return;
	string title = "!!! XOA DE THI !!!";
	string mess1 = "XOA THANH CONG !";
	string mess2 = "XOA THAT BAI !";
	int i = 0;
	bool n;
	string idSubject;
	node<Exam> *p = find(pos);
	box_result_message(x, y, 10, title,"");
	n = yesno_message(x + 1,y + 5);
	if(!n) 
	{
		test_eror_message(x, y, title, 1,"",mess2);
		return;
	}
	remove(p);
	test_eror_message(x, y, title, 1, "", mess1);
	--total;
	return;
}
//*********************************************************************************************
//											Exam & List Exam
//*********************************************************************************************


//*********************************************************************************************
//											Subject & List Subject
//*********************************************************************************************
struct Subject
{
	string subjectId;
	string subjectName;
	ListExam le;
	Subject()
	{
		le.subId = subjectId;
	}
	bool input(int, int, int &);
	bool is_existed(string);
	void change_info_subject(ListClass &,string , Subject); // oId : old id (not changed yet)
	void show(int, int);
	void read_file(ifstream &);
	void write_file(ofstream &);
};
bool Subject::input(int x,int y, int &error)
{
	gotoxy(x , y);
	cout << "Ma mon:";
	input_info(x + 7, y, MAXID, MAX_CHAR_LINE3,subjectId, 0, 1, 0);									// input id	
	gotoxy(x, y + 1);
	cout << "Ten mon:";
	input_info(x + 8, y + 1, MAXMIDDLE, MAX_CHAR_LINE3, subjectName, 0, 1, 0);								// input name
	if(subjectId[0] == '\0' || subjectName[0] == '\0')
	{
		error = 3;
		return 0;
	}
	error = 1;
	return 1;
}
bool Subject::is_existed(string id)
{
	return ((subjectId.compare(id) == 0));
}
void Subject::change_info_subject(ListClass &lc,string oId, Subject sub) // oId : old id (not changed yet)
{
	int numberClass = lc.numberClass;
	for(int i = 0; i < numberClass; ++i)
	{
		lc.cl[i].listStudent.change_id_score(oId, sub.subjectId);
	}
	subjectId = sub.subjectId;
	subjectName = sub.subjectName;
}
void Subject::show(int x, int y)
{
	gotoxy(x + 23, y);
	cout << subjectId;
	gotoxy(x + VERTICAL2 + 1, y);
	cout << subjectName;
}
void Subject::read_file(ifstream &file)
{
	file.ignore(); // clear endl
	getline(file, subjectId, '@');
	file.ignore(); // clear space
	getline(file, subjectName,'@');
	le.read_file(file);
}
void Subject::write_file(ofstream &file)
{
	file << subjectId << "@ " << subjectName << "@";
	le.write_file(file);
}


class ListSubject : public List<Subject>
{
	public:
	int numberSubject = 0;
	node<Subject> *find_subject(int posSubject) {find(posSubject);}
	
	void insert_subject(int, int);
	void change_subject(ListClass &, int, int, int); // test done
	void dele_subject(ListClass &, int, int,int); // test done
	void show_list_subject(int, int, int, int);
	void show_list_exam(int, int, int, int, int);
	void read_file(string); // right
	void write_file(string);
};

void ListSubject :: insert_subject(int x, int y)
{
	string title = "!!! THEM MON HOC !!!";
	string mess1 = "THEM THANH CONG !";
	string mess2 = "THEM THAT BAI !";
	if(numberSubject == MAXSUBJECT)
	{
		subject_eror_message(x, y, title, 4, "", mess2);
		return;
	} 
	bool n;
	int option = -1;
	Subject sub;
	box_result_message(x, y, 10, title,"");
	if(sub.input(x + 1, y + 4, option))
	{
		n = yesno_message(x + 1, y + 6);
		if(!n) 
		{
			subject_eror_message(x, y, title, 1, "", mess2);
			return ;
		}
		node<Subject> *p = find(sub.subjectId); // compile lib error / fixed
		if(p != NULL)
		{
			subject_eror_message(x, y, title, 2, sub.subjectId, mess2);
			return ;
		}
		insert_value(sub);
		++numberSubject;
		student_eror_message(x, y, title, 1, "", mess1);
		return ;
	}
	subject_eror_message(x, y, title, option, "", mess2);
	return ;
}

void ListSubject :: change_subject(ListClass &lc, int x, int y, int posSubject) // testing
{
	Subject sub;
	int n;
	int option = -1;
	int f = -1;
	string title = "!!!   SUA MON HOC  !!!";
	string mess1 = "SUA THANH CONG !";
	string mess2 = "SUA THAT BAI !";
	node<Subject> *findPos = find(posSubject);
	node<Subject> *findId;
	box_result_message(x, y, 10, title,"");
	sub.subjectId = findPos->data.subjectId;
	sub.subjectName = findPos->data.subjectName;
	if(sub.input(x + 1, y + 4, option))
	{
		n = yesno_message(x + 1,y + 6);
		if(!n)
		{
			subject_eror_message(x, y, title, 1, "", mess2);
			return ;
		}
		findId = find(sub.subjectId);
		if(findId != findPos && findId != NULL)
		{
			subject_eror_message(x, y, title, 2, sub.subjectId, mess2);
			return ;
		}
		findPos->data.change_info_subject(lc, findPos->data.subjectId, sub);
		subject_eror_message(x, y, title, 1, "", mess1);
		return;
	}
	subject_eror_message(x, y, title, option, "", mess2);
	return;
}
void ListSubject :: dele_subject(ListClass &lc, int x, int y,int posSubject) // test done
{
	if(numberSubject == 0) return;
	string title = "!!! XOA MON HOC !!!";
	string mess1 = "XOA THANH CONG !";
	string mess2 = "XOA THAT BAI !";
	int i = 0;
	bool n;
	string idSubject;
	node<Subject> *p = find(posSubject);
	box_result_message(x, y, 10, title,"");
	n = yesno_message(x + 1,y + 5);
	if(!n) 
	{
		subject_eror_message(x, y, title, 1,"",mess2);
		return;
	}
	idSubject = p->data.subjectId;
	for(int i = 0; i < lc.numberClass; ++i)
	{
		lc.cl[i].listStudent.dele_score(idSubject);
	}
	remove(p);
	subject_eror_message(x, y, title, 1, "", mess1);
	--numberSubject;
	return;
}

void ListSubject :: show_list_subject(int x, int y, int front, int rear)
{
	show(x + 6, y + 3, front, rear);
}
void ListSubject :: show_list_exam(int x, int y, int posSubject, int front, int rear)
{
	node<Subject> *p = find(posSubject);
	
	p->data.le.show_list_exam(x, y, front, rear);
}
void ListSubject :: read_file(string fileName) // right
{	
	ifstream file(fileName);
	file >> numberSubject;
	for(int i = 0; i < numberSubject; ++i) 
	{
		node<Subject> *sub = new node<Subject>;
		sub->data.read_file(file);
		insert(sub);
	}
}
void ListSubject :: write_file(string fileName)
{
	ofstream file(fileName);
	file << numberSubject << endl;
	node<Subject> *sub = first;
	for(int i = 0; i< numberSubject; ++i)
	{
		sub->data.write_file(file);
		sub = sub->next;
		file << endl;
	}
}

//*********************************************************************************************
//											Subject & List Subject
//*********************************************************************************************

