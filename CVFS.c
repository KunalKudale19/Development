#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
//#include<iostream.h>
//#include<io.h>

#define MAXINODE 50

#define READ 1
#define WRITE 2

#define MAXFILESIZE 2048

#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1
#define END 2

typedef struct superblock
{
	int TotalInode;
	int FreeInodes;
}SUPERBLOCK,*PSUPERBLOCK;

typedef struct inode
{
	char FileName[50];
	int InodeNumber;
	int FileSize;
	int FileActualSize;
	int FileType;
	char *Buffer;
	int LinkCount;
	int ReferenceCount;
	int permission;	//1 2 3
	struct inode* next;
}INODE,*PINODE,**PPINODE;

typedef struct filetable
{
	int readoffset;
	int writeoffset;
	int count;
	int mode;	//1 2 3
	PINODE ptrinode;
}FILETABLE,*PFILETABLE;

typedef struct ufdt
{
	PFILETABLE ptrfiltable;
}UFDT;

UFDT UFDTArr[50];
SUPERBLOCK SUPERBLOCKobj;
PINODE head=NULL;

void man(char* name)
{
	if(name==NULL)return;
	
	if(strcmp(name,"create")==0)
	{
		printf("Description: Used to create a new regular file\n");
		printf("Usage: create File_Name Permission\n");
	}
	else if(strcmp(name,"read")==0)
	{
		printf("Description: Used to read data from the file\n");
		printf("Usage: read File_Name No_of_Bytes_to_Read\n");
	}
	else if(strcmp(name,"write")==0)
	{
		printf("Description: Used to write data into the file\n");
		printf("Usage: write File_Name\n After this enter the data that we want to write\n");
	}
	else if(strcmp(name,"ls")==0)
	{
		printf("Description: Used to list all information of files\n");
		printf("Usage: ls\n");
	}
	else if(strcmp(name,"stat")==0)
	{
		printf("Description: Used to display information of file\n");
		printf("Usage: stat File_Name\n");
	}
	else if(strcmp(name,"fstat")==0)
	{
		printf("Description: Used to display information of file\n");
		printf("Usage: fstat File_Descriptor\n");
	}
	else if(strcmp(name,"truncate")==0)
	{
		printf("Description: Used to remove data from file\n");
		printf("Usage: truncate File_Name\n");
	}
	else if(strcmp(name,"open")==0)
	{
		printf("Description: Used to open existing file\n");
		printf("Usage:open File_Name mode\n");
	}
	else if(strcmp(name,"close")==0)
	{
		printf("Description: Used to close opened file\n");
		printf("Usage: close File_Name\n");
	}
	else if(strcmp(name,"cloaseall")==0)
	{
		printf("Description: Used to close all opened files\n");
		printf("Usage: cloaseall\n");
	}
	else if(strcmp(name,"lseek")==0)
	{
		printf("Description: Used to change file offset\n");
		printf("Usage: lseek File_Name ChangeInOffset StartPoint\n");
	}
	else if(strcmp(name,"rm")==0)
	{
		printf("Description: Used to delete the file\n");
		printf("Usage: rm File_Name\n");
	}
	else
	{
		printf("No manual entry available\n");
	}
}

void DisplayHelp()
{
	printf("ls : To list out all files\n");
	printf("clear : To clear console\n");
	printf("open : To open the file\n");
	printf("close : To close the file\n");
	printf("closeall : To close all opened files\n");
	printf("ls : To read contents from file\n");
	printf("write : To write contents into file\n");
	printf("exit : To terminate the file system\n");
	printf("stat : To display information of file using file name\n");
	printf("fstat : To display information of file using file descriptor\n");
	printf("truncate : To remove all data from file\n");
	printf("rm : To delete the file\n");
}

int GetFDFromName(char* name)
{
	int i=0;
	
	while(i<50)
	{
		if(UFDTArr[i].ptrfiltable!=NULL)
			if(strcmp((UFDTArr[i].ptrfiltable->ptrinode->FileName),name)==0)
				break;
		i++;
	}
	
	if(i==50)  return -1;
	else		return i;
}

PINODE Get_Inode(char* name)
{
	PINODE temp=head;
	int i=0;
	
	if(name==NULL)
		return NULL;
	
	while(temp!=NULL)
	{
		if(strcmp(name,temp->FileName)==0)
			break;
		temp=temp->next;
	}
	return temp;
}

void CreateDILB()
{
	int i=1;
	PINODE newn=NULL;
	PINODE temp=head;
	
	while(i<=MAXINODE)
	{
		newn=(PINODE)malloc(sizeof(INODE));
		
		newn->LinkCount=0;
		newn->ReferenceCount=0;
		newn->FileType=0;
		newn->FileSize=0;
		
		newn->Buffer=NULL;
		newn->next=NULL;
		
		newn->InodeNumber=i;
		
		if(temp==NULL)
		{
			head=newn;
			temp=head;
		}
		else
		{
			temp->next=newn;
			temp=temp->next;
		}
		i++;
	}
	printf("DILB created successfully\n");
}

void InitialseSuperBlock()
{
	int i=0;
	while(i<MAXINODE)
	{
		UFDTArr[i].ptrfiltable=NULL;
		i++;
	}
	
	SUPERBLOCKobj.TotalInode=MAXINODE;
	SUPERBLOCKobj.FreeInodes=MAXINODE;
}

int CreateFile(char* name,int permission)
{
	int i=0;
	PINODE temp=head;
	
	if((name==NULL)||(permission==0)||(permission>3))
		return -1;
	
	if(SUPERBLOCKobj.FreeInodes==0)
		return -2;
	
	(SUPERBLOCKobj.FreeInodes)--;
	
	if(Get_Inode(name)!=NULL)
		return -3;
	
	while(temp!=NULL)
	{
		if(temp->FileType==0)
			break;
		temp=temp->next;
	}
	
	while(i<50)
	{
		if(UFDTArr[i].ptrfiltable==NULL)
			break;
		i++;
	}
	
	UFDTArr[i].ptrfiltable=(PFILETABLE)malloc(sizeof(FILETABLE));
	
	UFDTArr[i].ptrfiltable->count=1;
	UFDTArr[i].ptrfiltable->mode=permission;
	UFDTArr[i].ptrfiltable->readoffset=0;
	UFDTArr[i].ptrfiltable->writeoffset=0;
	
	UFDTArr[i].ptrfiltable->ptrinode=temp;
	
	strcpy(UFDTArr[i].ptrfiltable->ptrinode->FileName,name);
	UFDTArr[i].ptrfiltable->ptrinode->FileType=REGULAR;
	UFDTArr[i].ptrfiltable->ptrinode->ReferenceCount=1;
	UFDTArr[i].ptrfiltable->ptrinode->LinkCount=1;
	UFDTArr[i].ptrfiltable->ptrinode->FileSize=MAXFILESIZE;
	UFDTArr[i].ptrfiltable->ptrinode->FileActualSize=0;
	UFDTArr[i].ptrfiltable->ptrinode->permission=permission;
	UFDTArr[i].ptrfiltable->ptrinode->Buffer=(char*)malloc(sizeof(MAXFILESIZE));
	
	return i;
}

//rm_File("Demo.txt")
int rm_File(char* name)
{
	int fd=0;
	
	fd=GetFDFromName(name);
	if(fd==-1)
		return -1;
	
	(UFDTArr[fd].ptrfiltable->ptrinode->LinkCount)--;
	
	if(UFDTArr[fd].ptrfiltable->ptrinode->LinkCount==0)
	{
		UFDTArr[fd].ptrfiltable->ptrinode->FileType=0;
		//free(UFDTArr[fd].ptrfiltable->ptrinode->Buffer)
		free(UFDTArr[fd].ptrfiltable);
	}
	
	UFDTArr[fd].ptrfiltable=NULL;
	(SUPERBLOCKobj.FreeInodes)++;
}

int ReadFile(int fd,char* arr,int isize)
{
	int read_size=0;
	
	if(UFDTArr[fd].ptrfiltable==NULL)	return -1;
	
	if(UFDTArr[fd].ptrfiltable->mode!=READ && UFDTArr[fd].ptrfiltable->mode!=READ+WRITE)	return -2;
	
	if(UFDTArr[fd].ptrfiltable->ptrinode->permission!=READ && UFDTArr[fd].ptrfiltable->ptrinode->permission!=READ+WRITE) return -2;
	
	if(UFDTArr[fd].ptrfiltable->readoffset==UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize) return -3;
	
	if(UFDTArr[fd].ptrfiltable->ptrinode->FileType!=REGULAR)	return -4;
	
	read_size=(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)-(UFDTArr[fd].ptrfiltable->readoffset);
	if(read_size<isize)
	{
		strncpy(arr,(UFDTArr[fd].ptrfiltable->ptrinode->Buffer)+(UFDTArr[fd].ptrfiltable->readoffset),read_size);
	
	UFDTArr[fd].ptrfiltable->readoffset=UFDTArr[fd].ptrfiltable->readoffset+read_size;
	}
	else
	{
		strncpy(arr,(UFDTArr[fd].ptrfiltable->ptrinode->Buffer)+(UFDTArr[fd].ptrfiltable->readoffset),isize);

		(UFDTArr[fd].ptrfiltable->readoffset)=(UFDTArr[fd].ptrfiltable->readoffset)+isize;
	}

	return isize;
}

int WriteFile(int fd,char* arr,int isize)
{
	if(((UFDTArr[fd].ptrfiltable->mode)!=WRITE) && ((UFDTArr[fd].ptrfiltable->mode)!=READ+WRITE)) return -1;
	
	if(((UFDTArr[fd].ptrfiltable->ptrinode->permission)!=WRITE) && ((UFDTArr[fd].ptrfiltable->ptrinode->permission)!=READ+WRITE)) return -1;
	
	if((UFDTArr[fd].ptrfiltable->writeoffset)==MAXFILESIZE)	return -2;
	
	if(UFDTArr[fd].ptrfiltable->ptrinode->FileType!=REGULAR)	return -3;
	
	strncpy((UFDTArr[fd].ptrfiltable->ptrinode->Buffer)+(UFDTArr[fd].ptrfiltable->writeoffset),arr,isize);
	
	(UFDTArr[fd].ptrfiltable->writeoffset)=(UFDTArr[fd].ptrfiltable->writeoffset)+isize;
	
	(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)=(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)+isize;
	
	return isize;
}

int OpenFile(char* name,int mode)
{
	int i=0;
	PINODE temp=NULL;
	
	if(name==NULL || mode<0)
		return -1;
	
	temp=Get_Inode(name);
	if(temp==NULL)
		return -2;
	
	if(temp->permission<mode)
		return -3;
	
	while(i<50)
	{
		if(UFDTArr[i].ptrfiltable==NULL)
			break;
		i++;
	}
	
	UFDTArr[i].ptrfiltable=(PFILETABLE)malloc(sizeof(FILETABLE));
	if(UFDTArr[i].ptrfiltable==NULL)	return -1;
	UFDTArr[i].ptrfiltable->count=1;
	UFDTArr[i].ptrfiltable->mode=mode;
	if(mode==READ+WRITE)
	{
		UFDTArr[i].ptrfiltable->readoffset=0;
		UFDTArr[i].ptrfiltable->writeoffset=0;
	}
	else if(mode==READ)
	{
		UFDTArr[i].ptrfiltable->readoffset=0;
	}
	else if(mode==WRITE)
	{
		UFDTArr[i].ptrfiltable->writeoffset=0;
	}
	UFDTArr[i].ptrfiltable->ptrinode=temp;
	(UFDTArr[i].ptrfiltable->ptrinode->ReferenceCount)++;
	
	return i;
}

void CloseFileByName(int fd)
{
	UFDTArr[fd].ptrfiltable->readoffset=0;
	UFDTArr[fd].ptrfiltable->writeoffset=0;
	(UFDTArr[fd].ptrfiltable->ptrinode->ReferenceCount)--;
}

int CloseFileByName(char* name)
{
	int i=0;
	i=GetFDFromName(name);
	if(i==-1)
		return -1;
	
	UFDTArr[i].ptrfiltable->readoffset=0;
	UFDTArr[i].ptrfiltable->writeoffset=0;
	(UFDTArr[i].ptrfiltable->ptrinode->ReferenceCount)--;
	
	return 0;
}

void CloseAllFile()
{
	int i=0;
	while(i<50)
	{
		if(UFDTArr[i].ptrfiltable!=NULL)
		{
			UFDTArr[i].ptrfiltable->readoffset=0;
			UFDTArr[i].ptrfiltable->writeoffset=0;
		   (UFDTArr[i].ptrfiltable->ptrinode->ReferenceCount)--;
			break;
		}
		i++;
	}
}

int LseekFile(int fd,int size,int from)
{
	if((fd<0)||(from>2))	return -1;
	if(UFDTArr[fd].ptrfiltable==NULL)	return -1;
	
	if(((UFDTArr[fd].ptrfiltable->mode)==READ) || ((UFDTArr[fd].ptrfiltable->mode)==READ+WRITE))
	{
		if(from==CURRENT)
		{
			if(((UFDTArr[fd].ptrfiltable->readoffset)+size)>UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)	return -1;
			if(((UFDTArr[fd].ptrfiltable->readoffset)+size)<0)	return -1;
			(UFDTArr[fd].ptrfiltable->readoffset)=(UFDTArr[fd].ptrfiltable->readoffset)+size;
		}
		else if(from==START)
		{
			if(size>(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize))	return -1;
			if(size<0) return -1;
			(UFDTArr[fd].ptrfiltable->readoffset)=size;
		}
		else if(from==END)
		{
			if((UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)+size>MAXFILESIZE)	return -1;
			if(((UFDTArr[fd].ptrfiltable->readoffset)+size)<0)	return -1;
			(UFDTArr[fd].ptrfiltable->readoffset)=(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)+size;
		}
	}
	else if(UFDTArr[fd].ptrfiltable->mode==WRITE)
	{
		if(from==CURRENT)
		{
			if(((UFDTArr[fd].ptrfiltable->writeoffset)+size)>MAXFILESIZE)	return -1;
			if(((UFDTArr[fd].ptrfiltable->writeoffset)+size)<0)	return -1;
			if(((UFDTArr[fd].ptrfiltable->writeoffset)+size)>(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize))
			(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)=(UFDTArr[fd].ptrfiltable->writeoffset)+size;
			(UFDTArr[fd].ptrfiltable->writeoffset)=(UFDTArr[fd].ptrfiltable->writeoffset)+size;
		}
		else if(from==START)
		{
			if(size>MAXFILESIZE)	return -1;
			if(size<0)	return -1;
			if(size>(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize))
					(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)=size;
				(UFDTArr[fd].ptrfiltable->writeoffset)=size;
		}
		else if(from==END)
		{
			if((UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)+size>MAXFILESIZE)	return -1;
			if(((UFDTArr[fd].ptrfiltable->writeoffset)+size)<0)		return -1;
			(UFDTArr[fd].ptrfiltable->writeoffset)=(UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize)+size;
		}
	}
}

void ls_file()
{
	int i=0;
	PINODE temp=head;
	
	if(SUPERBLOCKobj.FreeInodes==MAXINODE)
	{
		printf("ERROR:There are no files\n");
		return;
	}
	
	printf("\nFile Name\tInode number\tFile size\tLink count\n");
	printf("-------------------------------------------------------------\n");
	while(temp!=NULL)
	{
		if(temp->FileType!=0)
		{
			printf("%s\t\t%d\t\t%d\t\t%d\n",temp->FileName,temp->InodeNumber,temp->FileActualSize,temp->LinkCount);
		}
		temp=temp->next;
	}
	printf("---------------------------------------------------------------\n");
}

int fstat_file(int fd)
{
	int i=0;
	PINODE temp=head;
	
	if(fd<0)	return -1;
	
	if(UFDTArr[fd].ptrfiltable==NULL)	return -2;
	
	temp=UFDTArr[fd].ptrfiltable->ptrinode;
	
	printf("----------Statiscal information about file-------\n");
	printf("File name: %s\n",temp->FileName);
	printf("Inode number :%d\n",temp->InodeNumber);
	printf("File size:%d\n",temp->FileSize);
	printf("Actual File size:%d\n",temp->FileActualSize);
	printf("Link Count:%d\n",temp->LinkCount);
	printf("Reference count:%d\n",temp->ReferenceCount);
	
	if(temp->permission==1)
		printf("File permission:Read only\n");
	else if(temp->permission==2)
		printf("File permission:Write\n");
	else if(temp->permission==3)
		printf("File permission:Read&Write\n");
	printf("----------------------------------------------------\n");
	
	return 0;
}

int stat_file(char* name)
{
	int i=0;
	PINODE temp=head;
	
	if(name==NULL)	return -1;
	
	while(temp!=NULL)
	{
		if(strcmp(name,temp->FileName)==0)
			break;
		temp=temp->next;
	}
	
	if(temp==NULL) 	return -2;
	
	printf("----------Statiscal information about file-------\n");
	printf("File name: %s\n",temp->FileName);
	printf("Inode number :%d\n",temp->InodeNumber);
	printf("File size:%d\n",temp->FileSize);
	printf("Actual File size:%d\n",temp->FileActualSize);
	printf("Link Count:%d\n",temp->LinkCount);
	printf("Reference count:%d\n",temp->ReferenceCount);
	
	if(temp->permission==1)
		printf("File permission:Read only\n");
	else if(temp->permission==2)
		printf("File permission:Write\n");
	else if(temp->permission==3)
		printf("File permission:Read&Write\n");
	printf("----------------------------------------------------\n");
	
	return 0;
}

int truncate_File(char* name)
{
	int fd=GetFDFromName(name);
	if(fd==-1)
		return -1;
	
	memset(UFDTArr[fd].ptrfiltable->ptrinode->Buffer,0,1024);
	UFDTArr[fd].ptrfiltable->readoffset=0;
	UFDTArr[fd].ptrfiltable->writeoffset=0;
	UFDTArr[fd].ptrfiltable->ptrinode->FileActualSize=0;
}

int main()
{
	char* ptr=NULL;
	int ret=0,fd=0,count=0;
	char command[4][80],str[80],arr[1024];
	
	InitialseSuperBlock();
	CreateDILB();
	
	while(1)
	{
		fflush(stdin);			//Used to clear buffer 
		strcpy(str," ");
		
		printf("\n Marvellous VFS : >");
		
		fgets(str,80,stdin);		//scanf("%[^'\n']s",str);
		
		count=sscanf(str,"%s%s%s%s",command[0],command[1],command[2],command[3]);		//reads data from character string
		
		if(count==1)
		{
			if(strcmp(command[0],"ls")==0)
			{
				ls_file();
			}
			else if(strcmp(command[0],"closeall")==0)
			{
				CloseAllFile();
				printf("All files closed successfully\n");
				continue;
			}
			else if(strcmp(command[0],"clear")==0)
			{
				system("cls");
				continue;
			}
			else if(strcmp(command[0],"help")==0)
			{
				DisplayHelp();
				continue;
			}
			else if(strcmp(command[0],"exit")==0)
			{
				printf("Terminating the Marvellous Virtual File System\n");
				break;
			}
			else
			{
				printf("ERROR : Command not found\n");
				continue;
			}
		}
		else if(count==2)
		{
			if(strcmp(command[0],"stat")==0)
			{
				ret=stat_file(command[1]);
				if(ret==-1)
					printf("ERROR: Incorrect parameters\n");
				if(ret==-2)
					printf("ERROR : There is no such file\n");
				continue;
			}
			else if(strcmp(command[0],"fstat")==0)
			{
				ret=fstat_file(atoi(command[1]));
				if(ret==-1)
					printf("ERROR: Incorrect parameters\n");
				if(ret==-2)
					printf("ERROR : There is no such file\n");
				continue;
			}
			else if(strcmp(command[0],"close")==0)
			{
				ret=CloseFileByName(command[1]);
				if(ret==-1)
					printf("ERROR: There is no such file\n");
				continue;
			}
			else if(strcmp(command[0],"rm")==0)
			{
				ret=rm_File(command[1]);
				if(ret==-1)
					printf("ERROR: There is no duch file\n");
				continue;
			}
			else if(strcmp(command[0],"man")==0)
			{
				man(command[1]);
			}
			else if(strcmp(command[0],"write")==0)
			{
				fd=GetFDFromName(command[1]);
				if(fd==-1)
				{
					printf("ERROR: Incorrect parameters\n");
					continue;
				}
				printf("Enter the data\n");
				scanf("%[^'\n']s",arr);
				
				ret=strlen(arr);
				if(ret==0)
				{
					printf("ERROR: Incorrect parameters\n");
					continue;
				}
				ret=WriteFile(fd,arr,ret);
				if(ret==-1)
					printf("ERROR: Access Denied\n");
				if(ret==-2)
					printf("ERROR: There is no sufficient memory to write\n");
				if(ret==-3)
					printf("ERROR: it is not regular file\n");
			}
			else if(strcmp(command[0],"truncate")==0)
			{
				ret=truncate_File(command[1]);
				if(ret==-1)
					printf("Incorrect parameters\n");
			}
			else
			{
				printf("ERROR: Command not found\n");
				continue;
			}
		}
		else if(count==3)
		{
			if(strcmp(command[0],"create")==0)
			{
				ret=CreateFile(command[1],atoi(command[2]));
				if(ret>=0)
					printf("File created successfully with file descriptor: %d\n",ret);
				if(ret==-1)
					printf("ERROR: Incorrect parameters\n");
				if(ret==-2)
					printf("ERROR: there is no inodes\n");
				if(ret==-3)
					printf("ERROR: File already exists\n");
				if(ret==-4)
					printf("ERROR: Memory allocation failure\n");
				continue;
			}
			else if(strcmp(command[0],"open")==0)
			{
				ret=OpenFile(command[1],atoi(command[2]));
				if(ret>0)
					printf("File opened successfully with fil descriptor : %d\n",ret);
				if(ret==-1)
					printf("ERROR: Incorrect parameters\n");
				if(ret==-2)
					printf("ERROR: File not present\n");
				if(ret==-3)
					printf("ERROR: Permission denied\n");
				continue;
			}
			else if(strcmp(command[0],"read")==0)
			{
				fd=GetFDFromName(command[1]);
				if(fd==-1)
				{
					printf("ERROR: Incorrect parameters\n");
					continue;
				}
				ptr=(char*)malloc(sizeof(atoi(command[2]))+1);
				if(ptr==NULL)
				{
					printf("Memory allocation failure\n");
					continue;
				}
				ret=ReadFile(fd,ptr,atoi(command[2]));
				if(ret==-1)
					printf("ERROR: File does not exists\n");
				if(ret==-2)
					printf("ERROR: Permission denied\n");
				if(ret==-3)
					printf("ERROR: Reached at the end of the file\n");
				if(ret==-4)
					printf("ERROR: It is not a regular file\n");
				if(ret==0)
					printf("ERROR: File is empty\n");
				if(ret>0)
				{
					write(2,ptr,ret);
				}
				continue;
			}
			else
			{
				printf("ERROR :Command not found!!!\n");
				continue;
			}
		}
		else if(count==4)
		{
			if(strcmp(command[0],"lseek")==0)
			{
				fd=GetFDFromName(command[1]);
				if(fd==-1)
				{
					printf("Incorrect parameters\n");
					continue;
				}
				ret=LseekFile(fd,atoi(command[2]),atoi(command[3]));
				if(ret==-1)
				{
					printf("ERROR : Unable to perform lseek\n");
				}
			}
			else
			{
				printf("\nERROR: Command not found!!!\n");
				continue;
			}
		}
		else
		{
			printf("\nERROR: Command not found!!!\n");
			continue;
		}
	}
	return 0;
}