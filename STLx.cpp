/*Project Name - User Defined STL(Standard Template Library) using generic programing.*/



#include<iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>		//Template header
struct snode				//structure for Singlly Linked List
{
	T data;
	struct snode* next;
};

template<typename T>		//Template header
struct dnode				//structure for Doubly Linked List
{
	T data;
	struct dnode* next;
	struct dnode* prev;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Class declaration of all Linked List*/

template<class T>
class SinglyLL
{
	private:
			snode <T>* first;
			int size;
	
	public:
			SinglyLL();
			void InsertFirst(T);
			void InsertLast(T);
			void InsertAtPos(T,int);
			void DeleteFirst();
			void DeleteLast();
			void DeleteAtPos(int);
			void Display();
			int Count();
};


template<class T>
class Doublly
{
	private:
			dnode <T>* first;
			int size;
			
	public:
			Doublly();
			void Display();
			int Count();
			void InsertFirst(T);
			void InsertLast(T);
			void InsertAtPos(T,int);
			void DeleteFirst();
			void DeleteLast();
			void DeleteAtPos(int);
};


template<class T>
class SinglyCL
{
	private:
			snode <T>* first;
			snode <T>* last;
			int size;
			
	public:
			SinglyCL();
			void Display();
			int Count();
			void InsertFirst(T);
			void InsertLast(T);
			void InsertAtPos(T,int);
			void DeleteFirst();
			void DeleteLast();
			void DeleteAtPos(int);
};

template<class T>
class DoublyCL
{
	private:
			dnode <T>* first;
			dnode<T>* last;
			 int size;
			 
	public:
			DoublyCL()
			{
				first=NULL;
				last=NULL;
				size=0;
			}
			
			void Display();
			int Count();
			void InsertFirst(T no);
			void InsertLast(T no);
			void InsertAtPos(T no,int ipos);
			void DeleteFirst();
			void DeleteLast();
			void DeleteAtPos(int ipos);
};


/*End of class declaration*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Classes definitions*/

template<class T>
SinglyLL<T>::SinglyLL()
{
	first=NULL;
	size=0;
}

template<class T>			
void SinglyLL<T>::InsertFirst(T no)
{
	snode <T>* newn=new snode<T>;		//newn=(PNODE)malloc(sizeof(NODE));
				
	newn->data=no;
	newn->next=NULL;
				
	if(first==NULL)
	{
		first=newn;
	}
	else
	{
		newn->next=first;
		first=newn;
	}
	size++;
}
			
template<class T>
void SinglyLL<T>::InsertLast(T no)
{
	snode <T>* newn=new snode<T>;		//newn=(PNODE)malloc(sizeof(NODE));
				
	newn->data=no;
	newn->next=NULL;
				
	if(first==NULL)
	{
		first=newn;
	}
	else
	{
		snode <T>* temp=first;
					
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=newn;
	}
	size++;
}
			
template<class T>
void SinglyLL<T>::InsertAtPos(T no,int ipos)
{
	int iCnt=Count();
				
	if((ipos<1)||(ipos>iCnt+1))
	{
		cout<<"Invalid position\n";
		return;
	}
				
	if(ipos==1)
	{
		InsertFirst(no);
	}
	else if(ipos==iCnt+1)
	{
		InsertLast(no);
	}
	else
	{
		snode <T>* temp=first;
		snode <T>* newn=new snode<T>;
		newn->data=no;
		newn->next=NULL;
		for(int i=1;i<ipos-1;i++)
		{
			temp=temp->next;
		}
		newn->next=temp->next;
		temp->next=newn;
		size++;
	}
}
			
template<class T>
void SinglyLL<T>::DeleteFirst()
{
	snode <T>* temp=first;
	if(first!=NULL)
	{
		first=first->next;
		delete temp;
					
		size--;
	}
}
			
template<class T>
void SinglyLL<T>::DeleteLast()
{
	snode <T>* temp=first;
	if(first==NULL)
	{
		return;
	}
				
	else if(first->next==NULL)
	{
		delete first;
		first==NULL;
		size--;
	}
	else
	{
		while(temp->next->next!=NULL)
		{
			temp=temp->next;
		}
		delete temp->next;
		temp->next=NULL;
					
		size--;
	}
}
			
template<class T>
void SinglyLL<T>::DeleteAtPos(int ipos)
{
	int iCnt=Count();
				
	if((ipos<1)||(ipos>iCnt+1))
	{
		cout<<"Invalid position\n";
		return;
	}
				
	if(ipos==1)
	{
		DeleteFirst();
	}
	else if(ipos==iCnt+1)
	{
		DeleteLast();
	}
	else
	{
		snode <T>* temp=first;
		for(int i=1;i<ipos-1;i++)
		{
			temp=temp->next;
		}
		snode <T>* targeted=temp->next;
		temp->next=targeted->next;
		delete targeted;
		size--;
	}
}
			
template<class T>
void SinglyLL<T>::Display()
{
	snode <T>* temp=first;
	while(temp!=NULL)
	{
		cout<<"|"<<temp->data<<"|->"<<"\t";
		temp=temp->next;
	}
	cout<<"NULL"<<endl;
	cout<<endl;
}
			
template<class T>			
int SinglyLL<T>::Count()
{
	return size;
}

/*End of Singly Linear LL */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Doublly Linear generic */

template<class T>
Doublly<T>::Doublly()
{
	first=NULL;
	size=0;
}
			
template<class T>
void Doublly<T>::Display()
{
	dnode <T>* temp=first;
	while(temp!=NULL)
	{
		cout<<"|"<<temp->data<<"|->"<<"\t";
		temp=temp->next;
	}
	cout<<"NULL"<<endl;
}
			
template<class T>
int Doublly<T>::Count()
{
	return size;
}
			
template<class T>
void Doublly<T>::InsertFirst(T no)
{
	dnode <T>* newn=new dnode<T>;
	newn->data=no;
	newn->next=NULL;
	newn->prev=NULL;
				
	if(first==NULL)
	{
		first=newn;
	}
	else
	{
		newn->next=first;
		first->prev=newn;
		first=newn;
	}
	size++;
}
			
template<class T>
void Doublly<T>::InsertLast(T no)
{
	dnode <T>* temp=first;
	dnode <T>* newn=new dnode<T>;
	newn->data=no;
	newn->next=NULL;
	newn->prev=NULL;
				
	if(first==NULL)
	{
		first=newn;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=newn;
		newn->prev=temp;
	}
	size++;
}
			
template<class T>
void Doublly<T>::InsertAtPos(T no,int iPos)
{
	int iCnt=Count();
				
	if((iPos<1) || (iPos>iCnt+1))
	{
		cout<<"Invalid position\n";
		return;
	}
				
	if(iPos==1)
	{
		InsertFirst(no);
	}
	else if(iPos==iCnt+1)
	{
		InsertLast(no);
	}
	else
	{
		dnode <T>* temp=first;
		dnode <T>* newn=new dnode<T>;
		newn->data=no;
		newn->next=NULL;
		newn->prev=NULL;
					
		for(int i=1;i<iPos-1;i++)
		{
			temp=temp->next;
		}
		newn->next=temp->next;
		temp->next->prev=newn;
		temp->next=newn;
		newn->prev=temp;
		size++;
	}
}
			
template<class T>
void Doublly<T>::DeleteFirst()
{
	dnode <T>* temp=first;
	if(first!=NULL)
	{
		first=first->next;
		first->prev=NULL;
		delete temp;
		size--;
	}
}

template<class T>
void Doublly<T>::DeleteLast()
{
	dnode <T>* temp=first;
	if(first==NULL)
	{
		return;
	}
	else if(first->next==NULL)
	{
		delete first;
		first=NULL;
		size--;
	}
	else
	{
		while(temp->next->next!=NULL)
		{
			temp=temp->next;
		}
		delete temp->next;
		temp->next=NULL;
		size--;
	}
}
			
template<class T>
void Doublly<T>::DeleteAtPos(int iPos)
{
	int iCnt=Count();
				
	if((iPos<1)||(iPos>iCnt+1))
	{
		cout<<"Invalid position\n";
		return;
	}
				
	if(iPos==1)
	{
		DeleteFirst();
	}
	else if(iPos==iCnt+1)
	{
		DeleteLast();
	}
	else
	{
		dnode <T>* temp=first;
		for(int i=1;i<iPos-1;i++)
		{
			temp=temp->next;
		}
		dnode <T>* targeted=temp->next;
		temp->next=targeted->next;
		targeted->prev=temp;
		delete targeted;
		size--;
	}
}
			
/*End of doublly linear LL using Generic*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Singly Circular LL*/


template<class T>
SinglyCL<T>::SinglyCL()
{
	first=NULL;
	last=NULL;
	size=0;
}

template<class T>
void SinglyCL<T>::Display()
{
	snode <T>* temp=first;
	if((first==NULL)&&(last==NULL))
	{
		return;
	}
				
	do
	{
		cout<<"|"<<temp->data<<"|-> ";
		temp=temp->next;
	}while(temp!=last->next);
				
	cout<<endl;
}
			
template<class T>
int SinglyCL<T>::Count()
{
	return size;
}
			
template<class T>
void SinglyCL<T>::InsertFirst(T no)
{
	snode <T>* newn=new snode<T>;
				
	newn->data=no;
	newn->next=NULL;
				
	if((first==NULL)&&(last==NULL))
	{
		first=newn;
		last=newn;
	}
	else
	{
		newn->next=first;
		first=newn;
	}
		last->next=first;
		size++;
}
			
template<class T>
void SinglyCL<T>::InsertLast(T no)
{
	snode <T>* newn=new snode<T>;
				
	newn->data=no;
	newn->next=NULL;
				
	if((first==NULL)&&(last==NULL))
	{
		first=newn;
		last=newn;
	}
	else
	{
		last->next=newn;
		last=newn;
	}
	last->next=first;
	size++;
}
			
template<class T>
void SinglyCL<T>::InsertAtPos(T no,int ipos)
{
	if((ipos<1)&&(ipos>size+1))
	{
		cout<<"Invalid position\n";
		return;
	}
				
	if(ipos==1)
	{
		InsertFirst(no);
	}
	else if(ipos==size+1)
	{
		InsertLast(no);
	}
	else
	{
		snode <T>* newn=new snode<T>;
		newn->data=no;
		newn->next=NULL;
				
		snode <T>* temp=first;
		for(int i=1;i<ipos-1;i++)
		{
			temp=temp->next;
		}
		newn->next=temp->next;
		temp->next=newn;
		size++;
	}
}
			
template<class T>
void SinglyCL<T>::DeleteFirst()
{
	if((first==NULL)&&(last==NULL))
	{
		return;
	}
	else if(first==last)
	{
		delete first;
		first=NULL;
		last=NULL;
	}
	else
	{
		first=first->next;
		delete last->next;
		last->next=first;
	}
	size--;
}
			
template<class T>
void SinglyCL<T>::DeleteLast()
{
	snode <T>* temp=first;
	if((first==NULL)&&(last==NULL))
	{
		return;
	}
	else if(first==last)
	{
		delete first;
		first=NULL;
		last=NULL;
	}
	else
	{
		while(temp->next!=last)
		{
			temp=temp->next;
		}
		delete last;
		last=temp;
		last->next=first;
	}
	size--;
}
			
template<class T>
void SinglyCL<T>::DeleteAtPos(int ipos)
{
	if((ipos<1)&&(ipos>size+1))
	{
		cout<<"Invalid position\n";
		return;
	}
				
	if(ipos==1)
	{
		DeleteFirst();
	}
	else if(ipos==size)
	{
		DeleteLast();
	}
	else
	{
		snode <T>* temp=first;
		snode<T>* targeted=NULL;
		for(int i=1;i<ipos-1;i++)
		{
			temp=temp->next;
		}
		targeted=temp->next;
		temp->next=targeted->next;
		delete targeted;
		size--;
	}
}

/*End of Singly Circular LL*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Doublly Circular*/

template<class T>
void DoublyCL<T>::InsertFirst(T no)
{
	dnode <T>* newn=new dnode<T>;
	
	newn->data=no;
	newn->next=NULL;
	newn->prev=NULL;
	
	if((first==NULL)&&(last==NULL))
	{
		first=newn;
		last=newn;
	}
	else
	{
		newn->next=first;
		first->prev=newn;
		first=newn;
	}
	last->next=first;
	first->prev=last;
	size++;
}

template<class T>
void DoublyCL<T>::InsertLast(T no)
{
	dnode <T>* newn=new dnode<T>;
	
	newn->data=no;
	newn->next=NULL;
	newn->prev=NULL;
	
	if((first==NULL)&&(last==NULL))
	{
		first=newn;
		last=newn;
	}
	else 
	{
		last->next=newn;
		newn->prev=last;
		last=newn;
	}
	
	last->next=first;
	first->prev=last;
	size++;
}

template<class T>
void DoublyCL<T>::DeleteFirst()
{
	if((first==NULL)&&(last==NULL))
	{
		return;
	}
	else if(first==last)
	{
		delete first;
		first=NULL;
		last=NULL;
	}
	else
	{
		first=first->next;
		delete last->next;
		first->prev=last;
		last->next=first;
	}
	
	size--;
}

template<class T>
void DoublyCL<T>::DeleteLast()
{
	if((first==NULL)&&(last==NULL))
	{
		return;
	}
	else if(first==last)
	{
		delete first;
		first=NULL;
		last=NULL;
	}
	else
	{
		last=last->prev;
		delete last->next;
		first->prev=last;
		last->next=first;
	}
	
	size--;
}

template<class T>
void DoublyCL<T>::InsertAtPos(T no,int ipos)
{
	if((ipos<1)||(ipos>size+1))
	{
		cout<<"Invalid position\n";
		return;
	}
	
	if(ipos==1)
	{
		InsertFirst(no);
	}
	else if(ipos==size+1)
	{
		InsertLast(no);
	}
	else
	{
		dnode <T>* newn=new dnode<T>;
		
		newn->data=no;
		newn->next=NULL;
		newn->prev=NULL;
		
		dnode <T>* temp=first;
		for(int i=1;i<ipos-1;i++)
		{
			temp=temp->next;
		}
		newn->next=temp->next;
		temp->next->prev=newn;
		temp->next=newn;
		newn->prev=temp;
		size++;
	}
}

template<class T>
void DoublyCL<T>::DeleteAtPos(int ipos)
{
	if((ipos<1)&&(ipos>size+1))
	{
		cout<<"Invalid position\n";
		return;
	}
	
	if(ipos==1)
	{
		DeleteFirst();
	}
	else if(ipos==size+1)
	{
		DeleteLast();
	}
	else
	{
		dnode <T>* temp=first;
		for(int i=1;i<ipos-1;i++)
		{
			temp=temp->next;
		}
		temp->next=temp->next->next;
		delete temp->next->prev;
		temp->next->prev=temp;
		size--; 
	}
}

template<class T>
void DoublyCL<T>::Display()
{
	dnode <T>* temp=first;
	
	for(int i=1;i<=size;i++)
	{
		cout<<"|"<<temp->data<<"|->";
		temp=temp->next;
	}
	cout<<endl;
}

template<class T>
int DoublyCL<T>::Count()
{
	return size;
}

/* End od doublly circular*/

/*End of class definitions*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	SinglyLL <char>cobj;
	int iret=0;
	
	cobj.InsertFirst('s');
	cobj.InsertFirst('u');
	cobj.InsertFirst('o');
	
	cobj.InsertFirst('l');
	cobj.InsertFirst('l');
	cobj.InsertFirst('e');
	cobj.InsertFirst('v');
	cobj.InsertFirst('r');
	cobj.InsertFirst('a');
	cobj.InsertFirst('M');
	
	cobj.Display();
	
	iret=cobj.Count();
	cout<<"Number of elements of Singlly LL are: \n"<<iret<<"\n";
	
	Doublly <int>iobj;
	
	iobj.InsertFirst(60);
	iobj.InsertFirst(50);
	
	iobj.InsertFirst(40);
	iobj.InsertFirst(30);
	iobj.InsertFirst(20);
	iobj.InsertFirst(10);
	
	iobj.Display();
	
	iret=iobj.Count();
	cout<<"Number of elements of Doubbly LL are:\n"<<iret<<"\n";
	
	SinglyCL <float>fobj;
	
	fobj.InsertFirst(60.5);
	fobj.InsertFirst(50.5);
	
	fobj.InsertFirst(40.5);
	fobj.InsertFirst(30.5);
	fobj.InsertFirst(20.5);
	fobj.InsertFirst(10.5);
	
	fobj.Display();
	
	iret=fobj.Count();
	cout<<"Number of elements of Singlly Circular LL are: \n"<<iret<<"\n";
	
	DoublyCL<double>dobj;
	
	dobj.InsertFirst(60.5);
	dobj.InsertFirst(50.5);
	
	dobj.InsertFirst(40.5);
	dobj.InsertFirst(30.5);
	dobj.InsertFirst(20.5);
	dobj.InsertFirst(10.5);
	
	dobj.Display();
	
	iret=dobj.Count();
	cout<<"Number of elements of Doubly Circular LL are: \n"<<iret<<"\n";
	
	return 0;
}
