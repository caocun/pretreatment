#include <iostream>
#include  <fstream>
using  namespace std;

#define R 10
#define C 8

int DFA[R][C]= \
{
	      /* /   *  \   '   " \n other */
	/*0*/{0, 1, 0, 0, 8, 6, 0, 0},
	/*1*/{0, 2, 3, 0, 8, 0, 0, 0},
	/*2*/{0, 2, 2, 4, 2, 2, 0, 2},
	/*3*/{0, 3, 5, 3, 3, 3, 3, 3},
	/*4*/{0, 2, 2, 4, 2, 2, 4, 2},
	/*5*/{0, 0, 5, 3, 3, 3, 3, 3},
	/*6*/{0, 6, 6, 7, 6, 0, 6, 6},
	/*7*/{0, 6, 6, 7, 6, 6, 6, 6},
	/*8*/{0, 8, 8, 9, 0, 8, 8, 8},
	/*9*/{0, 8, 8, 8, 8, 8, 8, 8}
};

int code(char ch)
{
	int chars = 7;
	switch(ch)
	{
	case '/': chars=1;break;
	case '*': chars=2;break;
	case '\\':chars=3;break;
	case '\'':chars=4;break;
	case '\"':chars=5;break;
	case '\n':chars=6;break;
	default:chars=7;break;
	}
	return chars;
}
int Judge(char curch)
{
	if((curch == ' '||curch == '\t' || curch=='\r' || curch == '\n' || curch == '\\')) return 1;
	else return 0;
}
void  Pretreat(const char*src, const char *des)
{
	if(src == NULL || des == NULL) return;
	int i = 0;
	int j = 0;
	ifstream infile(src);
	if(infile.fail())
	{
		cout<<"open  "<<src<< "  fail!"<<endl;
		return;
	}
	ofstream outfile(des, ios::out);
	if(outfile.fail())
	{
		cout<<"open or create "<<des<< "  fail!"<<endl;
		return;
	}
	infile.seekg(0,ios::end);     
	unsigned int size=static_cast<unsigned int>(infile.tellg()); 
	infile.seekg(0,ios::beg);    

	char *rbuffer = new char [sizeof(char)*size];
	char *wbuffer = new char [sizeof(char)*size];
	memset(rbuffer, '\0', size);
	memset(wbuffer, '\0', size);

	infile.get(rbuffer, size, infile.eof());
	char curch=' ';
	char prech = ' ';
	int prestate = DFA[0][0];
	int curstate = DFA[0][0];
	int space = 0;
	while((curch = rbuffer[i])!='\0')
	{
		curstate = DFA[curstate][code(curch)];

		switch (curstate)
		{
		case 0:
			if(prestate == 1  && code(prech) == 1)
			{
				wbuffer[j++] = prech;
			}
			else if(code(curch) == 1)
			{
				break;
			}
			if(Judge(curch)&& space == 0)
			{
				//if(curch == '\n')
				//{
				//	wbuffer[j++] ='\n';
				//}
				//else
				//{
			    	wbuffer[j++] =' ';
			   //}
				space = 1;
				break;
			}
			else if(Judge(curch)&& space == 1)
			{
				break;
			}
			else
			{
				space = 0;
			}
		case 6:
		case 7:
		case 8:
		case 9:
			wbuffer[j++] = curch;break;
		}	
		prestate = curstate;
		prech = curch;
		i++;
	}
	outfile<<wbuffer;
	delete [] rbuffer;
	delete [] wbuffer;
	infile.close();
	outfile.close();
}

int main()
{
	char *src = "D:\\DREAM\\project\\project\\deal.cpp";
	char *des="D:\\result.cpp";
	Pretreat(src, des);
	return 0;
}
