#include <iostream>
#include <cstring>
#include <string>
#include <limits>

using namespace std;

struct Node {
	int data;
	Node *next;
};
void Show_list(Node *first) {
	Node *curr=first;
	do {
		cout<<curr->data;
		if(curr->next!=nullptr)
			cout<<" -> ";
		curr=curr->next;
	} while (curr!=nullptr);
	cout<<endl;
}
void Delete_element(Node **first,Node **last) {
	Node *current=*first;
	Node *prev=nullptr;
	int delete_element=0;
	cout<<"please enter element value"<<endl;
	cin>>delete_element;
	if(current->data==delete_element) {
		if(current==(*first) &&(*first)!=(*last)) {
			(*first)=(*first)->next;
			delete current;
			Show_list(*first);
			return;
		} else if(current==(*first) &&(*first)==(*last)) {
			(*first)=nullptr;
			(*last)=(*first);
			delete current;
			Show_list(*first);
			return;
		}
	}
	prev=current;
	current=current->next;
	while(current!=nullptr) {
		if(current->data==delete_element && current!=(*last)) {
			prev->next=current->next;
			delete current;
			Show_list(*first);
			return;
		} else if(current->data==delete_element && current==(*last)) {
			(*last)=prev;
			(*last)->next=nullptr;
			delete current;
			Show_list(*first);
			return;
		}
		prev=current;
		current=current->next;
	}
	cout<<"list don't have this element"<<endl;
}
void Change_element(Node **first) {
	Node *current=*first;
	int element_position;
	int new_element;
	int count=0;
	cout<<"please enter element position and new element value"<<endl;
	cin>>element_position>>new_element;
	while(current!=nullptr) {
		if(count==element_position) {
			current->data=new_element;
			Show_list(*first);
			return;
		}
		current=current->next;
		count++;
	}
	cout<<"list don't have this element"<<endl;
}
void Find_elements(Node *first) {
	Node *current=first;
	int element=0;
	int count=0;
	bool a=false;
	cout<<"please enter element for find"<<endl;
	cin>>element;
	while(current!=nullptr) {
		if(current->data==element) {
			cout<<count<<" ";
			a=true;
		}
		count++;
		current=current->next;
	}
	cout << endl;
	if(a==false)
		cout<<"list don't have this element"<<endl;
}
void List_sort(Node *first) {
	for(Node *current=first; current!=nullptr; current=current->next) {
		for(Node *current1=first; current1!=nullptr; current1=current1->next) {
			if((current->data)<(current1->data)) {
				swap(current->data,current1->data);
			}
		}
	}
	Show_list(first);
}
void Check_numbers(const char *argv,int *&numbers_array,int &numbers_count) {
	for(int i=0; i<strlen(argv); i++) {
		if(argv[i]>='0' && argv[i]<='9')
			;
		else numbers_count++;
	}
	numbers_count++;
	numbers_array=new int[numbers_count];
	for(int i=0; i<numbers_count; i++) {
		numbers_array[i]=0;
	}
	int y=0;
	for(int i=0; i<strlen(argv)+1; i++)
		if(argv[i]>='0'&&argv[i]<='9')
			numbers_array[y]=numbers_array[y]*10+argv[i]-'0';
		else y++;
}
void Fill_array(int numbers_array[],int argc,char **argv) {
	for(int i=0; i<argc-1; i++)
		numbers_array[i]=atoi(argv[i+1]);
}
void Fill_list(int numbers_array[],int numbers_count,Node **first,Node **last) {
	for(int i=0; i<numbers_count; i++) {
		Node *node=new Node {numbers_array[i],nullptr};
		if((*last) == nullptr) {
			(*last)=node;
			(*first)=(*last);
			continue;
		}
		(*last)->next = node;
		(*last) = node;
		delete node;
	}
}

void Add_list(Node **first,Node **last) {
	int *numbers_array=nullptr;
	int numbers_count=0;
	string str;
	cout<<"Please enter elements"<<endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin,str);
	Check_numbers(str.c_str(),numbers_array,numbers_count);
	Fill_list(numbers_array,numbers_count,first,last);
	Show_list(*first);
}
void Print_menu() {
	cout<<"choise operation"<<endl;
	cout<<"1: show list"<<endl;
	cout<<"2: add element to list"<<endl;
	cout<<"3: delete element from list"<<endl;
	cout<<"4: find an element of list"<<endl;
	cout<<"5: replace the item with another one"<<endl;
	cout<<"6: sort list"<<endl;
	cout<<"7: finish program"<<endl;
	cout<<endl;
}


int main(int argc,char *argv[]) {
	int *numbers_array=nullptr;
	int numbers_count=0;
	numbers_count=argc-1;
	numbers_array=new int[numbers_count];
	Fill_array(numbers_array,argc,argv);
	Node *last=nullptr;
	Node *first=nullptr;
	Fill_list(numbers_array,numbers_count,&first,&last);
	int choice;
	string choice_exit;
	while(true)
	{
		Print_menu();
		cin>>choice;
		switch(choice) {
			case 1:
				if(first != nullptr)
					Show_list(first);
				else
					cerr<<"list is empty"<<endl;
				break;
			case 2:
				Add_list(&first,&last);
				break;
			case 3:
				if(first!=nullptr)
					Delete_element(&first,&last);
				else
					cout<<"list is empty, please first create list"<<endl;
				break;
			case 4:
				Find_elements(first);
				break;
			case 5:
				Change_element(&first);
				break;
			case 6:
				if(first!=nullptr)
					List_sort(first);
				else
					cout<<"list is empty, please first create list"<<endl;
				break;
			case 7:
			    cout << "Are you sure? y/n" << endl;
			    cin >> choice_exit;
			    if (choice_exit=="y" || choice_exit=="Y" || choice_exit=="yes" || choice_exit=="Yes")
				return 0;
				if (choice_exit=="n" || choice_exit=="N" || choice_exit=="No" || choice_exit=="no")
			    break;
			    cout << "Unknown command" << endl << endl;
			    break;
		}
	}
}
