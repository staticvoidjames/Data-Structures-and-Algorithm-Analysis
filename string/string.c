#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 40
#define OK 1
#define ERROR -1

typedef char String[MAXSIZE + 1];

int StrAssign(String str,char *chars)
{
	int i,length = strlen(chars);
    if(length > MAXSIZE)
    {
        return ERROR;
    }
    str[0] = length;
    for(i = 1; i <= length; i++)
    {
        str[i] = chars[i-1];
    }
	return OK;
}

int StrCopy(String str,String S)
{
	int i;
	for(i = 0;i <= S[0];i ++)
		str[i] = S[i];
	return OK;
}

int isEmpty(String str)
{
    return str[0] == 0;
}

int length(String str)
{
    return str[0];
}

int clear(String str)
{
    str[0] = 0;
    return OK;
}

int strcompare(String str1,String str2)
{
    int i;
    for(i = 1;i <= length(str1) && i <= length(str2);i ++)
    {
        if(str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
    }
    return str1[0] - str2[0];
}

int Concat(String str1,String str2,String result)
{
    int i;
     for(i = 1;i <= str1[0];i ++)
    {
        result[i] = str1[i];
    }

    if(str1[0] + str2[0] <= MAXSIZE)
    {
        for(i = 1;i <= str2[0];i ++)
        {
            result[str1[0] + i] = str2[i];
        }
        result[0] = str1[0] + str2[0];
        return OK;
    }
    else
    {
        for(i = 1;i <= MAXSIZE - str1[0];i++)
			result[str1[0] + i] = str2[i];
		result[0] = MAXSIZE;
        return ERROR;
    }
}

int sub_string(String result,String str,int position,int length)
{
    int i;
    if(position < 0 || position > str[0] || length < 0 || position + length > str[0])
    {
        return ERROR;
    }
    for(i = 1;i <= length;i ++)
    {
        result[i] = str[position + i - 1];
    }
    result[0] = length;
    return OK;
}

void print_string(String str)
{
    int i;
    if(isEmpty(str))
    {
        puts("空字符串");
		return;
    }
    for(i = 1;i <= str[0];i ++)
    {
        printf("%c",str[i]);
    }
    puts("");
}

int Index(String S,String T,int pos)
{
	int i = pos,j = 1;
	if(i < 1 || pos > S[0])
	{
		return ERROR;
	}
	while(i <= S[0] && j <= T[0])
	{
		if(S[i] == T[j])
		{
			i ++;
			j ++;
		}
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if(j > T[0])
	{
		return i - T[0];
	}
	else
	{
		return ERROR;
	}
}

int StrInsert(String S,int pos,String T)
{ 
	int i;
	if(pos<0||pos>S[0]-1)
		return ERROR;
	if(S[0]+T[0]<=MAXSIZE)
	{
		for(i=S[0];i>=pos;i--)
			S[i+T[0]]=S[i];

		for(i=pos;i<pos+T[0];i++)
			S[i]=T[i-pos+1];
		
		S[0]=S[0]+T[0];
		return OK;
	}
	else
	{
		for(i=MAXSIZE;i<=pos;i--)
			S[i]=S[i-T[0]];
		for(i=pos;i<pos+T[0];i++)
			S[i]=T[i-pos+1];
		S[0]=MAXSIZE;
		return ERROR;
	}
}

int StrDelete(String S,int pos,int len)
{ 
	int i;
	if(pos<1 || pos + len > S[0] || len < 0)
		return ERROR;
	for(i=pos+len;i<=S[0];i++)
		S[i-len]=S[i];
	S[0]-=len;
	return OK;
}

int Replace(String S,String T,String V)
{ 
	int i=1; /*  从串S的第一个字符起查找串T */
	if(isEmpty(T)) /*  T是空串 */
		return ERROR;
	do
	{
		i=Index(S,T,i); /*  结果i为从上一个i之后找到的子串T的位置 */
		if(i != ERROR) /*  串S中存在串T */
		{
			StrDelete(S,i,length(T)); /*  删除该串T */
			StrInsert(S,i,V); /*  在原串T的位置插入串V */
			i+=length(V); /*  在插入的串V后面继续查找串T */
		}
	}while(i != ERROR);
	return OK;
}

int main()
{
	int i,j,k;
	char s;
	String t,s1,s2;

	printf("请输入串s1: abcd\n");
	StrAssign(s1,"abcd");
	printf("串长为%d 串空否？%d(1:是 0:否)\n",length(s1),isEmpty(s1));

	StrCopy(s2,s1);
	printf("拷贝s1生成的串为: ");
	print_string(s2);

	printf("请输入串s2: efghijk\n");
	StrAssign(s2,"efghijk");
	
	i=strcompare(s1,s2);
	if(i<0)
		s='<';
	else if(i==0)
		s='=';
	else
		s='>';
	printf("串s1%c串s2\n",s);

	Concat(s1,s2,t);
	printf("串s1联接串s2得到的串t为: ");
	print_string(t);

	if(k == ERROR)
		printf("串t有截断\n");

	clear(s1);
	printf("清为空串后,串s1为: ");
	print_string(s1);
	printf("串长为%d 串空否？%d(1:是 0:否)\n",length(s1),isEmpty(s1));

	printf("请输入子串的起始位置,子串长度: ");
	i=2;
	j=3;
	printf("%d,%d \n",i,j);

	sub_string(s2,t,i,j);
	printf("子串s2为: ");
	print_string(s2);

	printf("从串t的第pos个字符起,删除len个字符，请输入pos,len: ");
	i=4;
	j=2;
	printf("%d,%d \n",i,j);
	StrDelete(t,i,j);
	printf("删除后的串t为: ");
	print_string(t);

	i=length(s2)/2;
	StrInsert(s2,i,t);
	printf("在串s2的第%d个字符之前插入串t后,串s2为:\n",i);
	print_string(s2);

	i=Index(s2,t,1);
	printf("s2的第%d个字母起和t第一次匹配\n",i);

	sub_string(t,s2,1,1);
	printf("串t为：");
	print_string(t);

	Concat(t,t,s1);
	printf("串s1为：");
	print_string(s1);

	Replace(s2,t,s1);
	printf("用串s1取代串s2中和串t相同的串后,串s2为: ");
	print_string(s2);

    return 0;
}

