#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<string>
#include<string.h>
#define MAX_DIGITS 10
using namespace std;

char* convStr2Char(string& str,char* Char)       //Chuyển kiểu dl String sang Char
{
    for(int i=0;i<=50;i++)
    {
        Char[i] = str[i];
    }
    return Char;

}
//Tạo 1 đối tượng tiến trình gồm các thuộc tính
/* T_Processing: Tổng thời gian xử lý xong của 1 chương tiến trình
   T_appear: Thời gian xuất hiện của tiến trình
   T_wait: THời gian phải chờ để được xử lý của tiến trình
   T_start: THời điểm tiến trình bắt đầu được xử lý
   T_complete: THời điểm tiến trình bắt đầu được xử lý
   name: Tên của tiến trình (VD: Program1.exe, Program2.exe....)
*/
class Process
{
public:
    //Các thuộc tính
	int T_Processing, T_appear, T_wait, T_start, T_complete;
	string name;

	//Hàm tạo tiến trình
	Process(string _name ="", int _T_processing=0, int _T_appear=0)
	{
		this->name = _name;
		this->T_Processing = _T_processing;
		this->T_appear = _T_appear;
	}

	//Tạo toán tử gán (dấu =) 
	/* VD: Khi gán P1 = P2 thì các thuộc tính (name,T_processing,....) của P2 sẽ gán cho P1

	*/
	Process& operator=(Process& _P)
	{
		this->name = _P.name;
		this->T_Processing = _P.T_Processing;
		this->T_appear = _P.T_appear;
		return *this;
	}

	//Đảo 2 tiến trình

	//Toán tử << để hiển thị các thuộc tính của tiến trình
	friend ostream& operator<<(ostream& os, Process& _P);
};
	/* VD: Swap(P1,P2) : Lúc này các thuộc tính của P2 sẽ gán cho P1, P1 sẽ gán cho P2
	*/
void Swap(Process& P1, Process& P2)
{
	Process temp;
	temp = P1;
	P1 = P2;
	P2 = temp;
}
ostream& operator<<(ostream& os, Process& _P)
{
	os << _P.name << "\t" << _P.T_Processing << "\t" << _P.T_appear <<endl;
	return os;
}

//Tạo đối tượng để chứa các tiến trình (class Process)
class ListProcess
{
public:
	Process* P;				//Con trỏ quản lý các tiến trình đưa vào
	int N;                  //Số lượng các tiến trình đưa vào

	/*temp , temp2 chỉ sử dụng nếu cần thêm tiến trình (nếu nhập 1 khi chạy chương trình)
	 Nếu nhập 0 thì k cần quan tâm*/
	Process* temp;		//Con trỏ quản lý các tiến trình mặc định ban đầu
	Process* temp2;       //Con trỏ quản lý các tiến trình thêm vào (được sử dụng nếu có nhu cầu thêm tiến trình)

    Process* Q;           //Con trỏ Quản lý hàng chờ
    int iQ;               //Số lượng các tiến trình đang trong hàng chờ

	//Hàm tạo ListProcess chứa các tiến trình
	ListProcess()
	{	
		N = 0;                   //Khởi tạo ban đầu số lượng tiến trình cần xử lý = 0
		temp = new Process[50];    //Với dung lượng chứa được tối đa 50 tiến trình
		temp2 = new Process[50];
        Q = new Process[50];       //Tạo hàng chờ với dung lượng chứa tối đa 50 tiến trình
        iQ = 0;	                  //Với số lượng tiến trình ban đầu trong hàng chờ bằng 0
	}

	//Thêm tiến trình vào cuối hàng chờ
    void AddtoQueuing(Process& _P)
	{
		iQ++;
		Q[iQ] = _P;
//		cout<<"\nProcess is Queuing: ";
		for(int i=1; i<=iQ; i++)
		{
//			cout<<Q[i].name<<"\t";
		}
	}

	//Thêm tiến trình vào danh sách các tiến trình cần được xử lý
	void AddtoList(Process& _P)
	{
		N++;
		temp[N] = _P;
	}

	//Tạo danh sách các tiến trình cần dược xử lý
	void CreateList()
	{	
		P = new Process[N+1];
		for(int i=1; i<=N; i++)
		{
			P[i] = temp[i];
		}
		cout<<"List Program"<<endl;
		for(int i=1; i<=N; i++)
		{
			cout<<P[i];
		}		
	}

	//Sau khi thêm tiến trình vào danh sách thì phải cập nhật và hiển thị ra màn hình
	void UpdateandShow()
	{	
		//Thêm tiến trình vào danh sách các tiến trình cần được xử lý
		int M;   //Số tiến trình muốn đưa thêm vào
		int select;
		cout<<"Do you want to Add Process to List? (1/0) ";   //1 là có, 0 là không

		cin>>select;
		switch(select)
		{	
			//Nếu có thì trước tiên nhập số tiến trình cần thêm vào
			//Sau đó nhập tên tiến trình, Tổng thời gian xử lý xong mỗi tiến trình, thời gian xuất hiện của mỗi tiến trình
			case 1:
			//Nhập số tiến trình muốn đưa thêm vào là M
				cout<<"Enter the number of Process: ";
				cin>>M;
				for(int i=N+1; i<= M+N; i++)
				{
					cout<<"Enter Name Process["<<i<<"]: ";
					cin>>temp2[i].name;
					cout<<"Enter Processing Time of Process["<<i<<"]: ";
					cin>>temp2[i].T_Processing;
					cout<<"Enter Appear Time of Process["<<i<<"]: ";
					cin>>temp2[i].T_appear;
				}
				//Cập nhập lại danh sách các tiến trình sau khi thêm M tiến trình
				P = new Process[M+N+1];
				for(int i=1; i<=N; i++)    //Số lượng tiến trình ban đầu là N (5)
				{
					P[i] = temp[i];
				}
				for(int i=N+1; i<= M+N; i++)   
				{
					P[i] = temp2[i];
				}	
				//Hiển thị danh sách tiến trình sau khi thêm
				cout << "List Program" << endl;
				for (int i =1;i<=N+M;i++)
				{	
					cout << P[i];
				}
                N = N + M;
				break;			
		
			case 0:   //Không đưa thêm tiến trình nào vào
			
				cout << "List Program" << endl;
				for (int i =1;i<=N;i++)
				{	
					cout << P[i];
				}
		}
    }
	
	//Sau khi lấy tiến trình ra khỏi hàng chờ để đưa vào xử lý thì phải cập nhật lại hàng chờ
	//Tiến trình được lấy ra khỏi hàng chờ sẵn sàng được xử lý : ready
    void GetandUpdateQueuing(Process& ready)
	{	
		//Sắp xếp các tiến trình trong hàng chờ (tiến trình có T_procesiing nhỏ thì đưa lên trước)
		for(int i=1; i< iQ; i++)
		{
			for(int j=i+1; j<= iQ; j++)
			{
				if(Q[j].T_Processing < Q[i].T_Processing)
				{
					Swap(Q[j],Q[i]);
				}
			}
		}
		ready = Q[1];    //Q[1] là tiến trình có T_processing nhỏ nhất
		//Cập nhật lại hàng chờ sau khi lấy Q[1] ra
		for(int i=1; i<iQ; i++)
		{
			Q[i] = Q[i+1];
		}
		Q[iQ].name = "";
		Q[iQ].T_Processing = 0;
		Q[iQ].T_appear = 0;
		iQ--;
	//	cout<<"\nProcess is Queuing: ";
		if(iQ>0)
		{
			for(int i=1; i<=iQ; i++)
			{
		//		cout<<Q[i].name<<"\t";
			}
		}
		else
		{
			// cout<<"Empty"<<endl;
		}
	}

	//Hàm tính toán các thuộc tính thuật toán SJF (T_wait, T_start, T_complete)
    void ScheduleSJF()
	{   
		Process ready;          //Tiến trình sẵn sàng để được xử lý
		P[1].T_start = P[1].T_appear;        //Tiến trình 1 xuất hiện đầu tiên nên được xử lý luôn
		P[1].T_complete = P[1].T_start + P[1].T_Processing;     
		for(int i=1; i<= N; i++)
		{	
		//	cout<<"\n"<<"T = "<<P[i].T_start<<" "<<P[i].name<<" is Processing"<<endl;
			//Khi xử lý xong hết N tiến trình thì dừng
			if(i==N)
			{	
				break;
			}
			//Nếu 1 tiến trình xuất hiện trong khoảng thời gian tiến trình trước nó đang xử lý thì đưa tiến trình đó vào hàng chờ
			for(int j = i+1; j<=N; j++)
			{
				if((P[j].T_appear > P[i].T_start)&&(P[j].T_appear < (P[i].T_start + P[i].T_Processing)))
				{
					AddtoQueuing(P[j]);
				}			
			}
	//		cout<<"\nNumber of Process is Queuing "<<iQ<<endl;

			//Lấy tiến trình có T_processing ngắn nhất ra khỏi hàng chờ 
			if(iQ >0 )      //Nếu có tiến trình trong hàng chờ thì thực hiện
			{
				GetandUpdateQueuing(ready);
				P[i+1].T_start = P[i].T_start + P[i].T_Processing;
				/*Đổi chỗ tiến trình ready và tiến trình P[i+1] để sau khi tiến trình 
				P[i] xử lí xong thì tiến trình ready được xử lý luôn	*/
				Swap(ready,P[i+1]);
			}
			else
			/*Nếu sau khi tiến trình P[i] xử lí xong mà trong hàng chờ k có tiến trình nào
			 thì tiến trình xuất hiện sau P[i] được đưa vào xử lý luôn*/
			{	
				P[i+1].T_start = P[i+1].T_appear;
				continue;
			}
		}

		//Tinh T_wait;
		for(int i=1; i<=N; i++)
		{
			P[i].T_wait = P[i].T_start - P[i].T_appear;
			if(P[i].T_wait<0)
			{
				P[i].T_wait = 0;
			}
		}
		//Tinh T_complete;
		for(int i=1; i<=N; i++)
		{	
			P[i].T_complete = P[i].T_start + P[i].T_Processing;
		}
	}

	//HIển thị bảng kết quả
	void ShowResultSJF()
	{	
		float average_wait;       //Thời gian chờ trung bình của tất cả các tiến trình
		float sum = 0;
		cout<<"====================================================="<<endl;
		cout<<"Program\tProcessing\tAppear\tWait\tStart\tComplete"<<endl;
		for(int i=1; i<=N; i++)
		{
			cout<<P[i].name<<"\t"<<P[i].T_Processing<<"\t"<<P[i].T_appear<<"\t"<<P[i].T_wait<<"\t"<<P[i].T_start<<"\t"<<P[i].T_complete<<endl;
		}
		for(int i = 1; i<=N; i++)
		{
			sum += P[i].T_wait;
		}
		cout<<"Average Wait time: "<<sum/N<<endl;
		cout<<"====================================================="<<endl;		
	}

	//Trả về số lượng tiến trình đưa vào để xử lý
	int ReturnN()
	{
		return N;
	}

	//Hàm mô phỏng thuật toán SJF
	void SimualtionSJF()
	{
		cout<<"====================================================="<<endl;
		cout<<"SIMULATION Shortest Job First"<<endl;
		for(int i = 0; i<=100; i++)
		{	
			cout<<"T = "<<i<<endl;
			for(int j=1; j<=N; j++)
			{	

				if(P[j].T_appear == i)
				{
					cout<<P[j].name<<": Add to Queuing"<<endl;
				}
				if(P[j].T_start == i)
				{
					cout<<P[j].name<<": Start Processing"<<endl;

					//Đoạn này dùng để ghép chuỗi, xử lý chuỗi để mở terminal chạy các chương trình con mô phỏng
					char* name = new char[50];
            		char* program = new char[50];
					program = convStr2Char(P[j].name,program);
					char* space = new char[50];
					strcpy(space, " ");
					char* space_name = strcat(program,space);
					char num_char[MAX_DIGITS + sizeof(char)];
					sprintf(num_char, "%d", P[j].T_Processing);
					char* link1 = strcat(space_name,num_char);   //Program1.exe 11
					char* terminal = new char[50];
					strcpy(terminal,"gnome-terminal -q -- ./program/");
					char* link = strcat(terminal,link1);
					system(link);              //Câu lệnh để tạo ra cửa sổ terminal mới
				}
				if(P[j].T_complete == i)
				{
					cout<<P[j].name<<": Completed"<<endl;
				}
			}
			sleep(1);                //Hàm chờ 1 giây rồi thực hiện lệnh tiếp theo
			if(P[N].T_complete == i)     
			{
				break;
			}
		}
		cout<<"====================================================="<<endl;
	}

	//Tính toán các thuộc tính của thuật toán FCFS (T_wait, T_start, T_complete)
	//FCFS: tiến trình nào T_appear nhỏ hơn thì thực hiện trước
	void ScheduleFCFS()
	{
		P[1].T_start = P[1].T_appear;
		P[1].T_complete = P[1].T_complete + P[1].T_Processing;

		for(int i = 1; i<=N; i++){
			int j = i+1 ;
			if(P[j].T_appear<P[i].T_complete)
			{
				P[j].T_start = P[i].T_complete;	
			}
			else
			{
				P[j].T_start = P[j].T_appear;			
			}
			P[j].T_complete = P[j].T_start + P[j].T_Processing;
			P[j].T_wait = P[j].T_start - P[j].T_appear;
		}
	}

	//hàm hiênr thị kết quả tính toán các thuộc tính của FCFS
	void ShowResultFCFS()
	{
		cout<<"====================================================="<<endl;
		cout<<"Program\tProcessing\tAppear\tWait\tStart\tComplete"<<endl;
		for(int i=1; i<=N; i++)
		{
			cout<<P[i].name<<"\t"<<P[i].T_Processing<<"\t"<<P[i].T_appear<<"\t"<<P[i].T_wait<<"\t"<<P[i].T_start<<"\t"<<P[i].T_complete<<endl;
		}
		float sumwait = 0;
		for(int i=1; i<=N; i++)
		{
			sumwait += P[i].T_wait;
		}
		cout<<"Average Wait time: "<<sumwait/N<<endl;
		cout<<"====================================================="<<endl;	

	}

	//Hàm mô phỏng thuật toán FCFS
	void SimualtionFCFS()
	{
		cout<<"====================================================="<<endl;
		cout<<"SIMULATION First Come First Serve"<<endl;
		for(int i = 0; i<=100; i++)
		{	
			cout<<"T = "<<i<<endl;
			for(int j=1; j<=N; j++)
			{	

				if(P[j].T_appear == i)
				{
					cout<<P[j].name<<": Add to Queuing"<<endl;
				}
				if(P[j].T_start == i)
				{
					cout<<P[j].name<<": Start Processing"<<endl;

					char* name = new char[50];
            		char* program = new char[50];
					program = convStr2Char(P[j].name,program);
					char* space = new char[50];
					strcpy(space, " ");
					char* space_name = strcat(program,space);
					char num_char[MAX_DIGITS + sizeof(char)];
					sprintf(num_char, "%d", P[j].T_Processing);
					char* link1 = strcat(space_name,num_char);   //Program1.exe 11
					char* terminal = new char[50];
					strcpy(terminal,"gnome-terminal -q -- ./program/");
					char* link = strcat(terminal,link1);
					system(link);
				}
				if(P[j].T_complete == i)
				{
					cout<<P[j].name<<": Completed"<<endl;
				}
			}
			sleep(1);
			if(P[N].T_complete == i)
			{
				break;
			}
		}
		cout<<"====================================================="<<endl;
	}	
	
};
int main()
{
	//Tạo 5 tiến trình sử dụng hàm tạo
	Process P1("Program1.exe", 11, 0);
	Process P2("Program2.exe", 7, 3);
	Process P3("Program3.exe", 19,8);
	Process P4("Program4.exe", 4, 13);
	Process P5("Program5.exe", 9, 17);
	
	ListProcess List;
	//Thêm các tiến trình vào cuối danh sách
	List.AddtoList(P1);
	List.AddtoList(P2);
	List.AddtoList(P3);
	List.AddtoList(P4);
	List.AddtoList(P5);	
	List.CreateList();
	List.UpdateandShow();

	int select;
	while(1)
	{
		cout<<"\nEnter the number of Schedule: ";  //Nhập 0 hoặc 1
		cout<<"\n0. Exit Simulation";        //Thoát mô phỏng
		cout<<"\n1. First Come First Serve";	
		cout<<"\n2. Shortest Job First \n";		
		cin>>select;
		if(select == 0)
		break;
		else
		{
			switch(select)
			{	
				case 1:
				{
					List.ScheduleFCFS();	
					List.SimualtionFCFS();
					List.ShowResultFCFS();
				}
				break;
				case 2:
				{
					List.ScheduleSJF();
					List.SimualtionSJF();
					List.ShowResultSJF();
				}
				break;
				default:
					break;
			}
		}
	}
	return 0;
}
