#include <string.h>
#include "HString.h"

HString::HString():
	AString(),
	itsNumber (0),
	itsLocation (NULL)
{
}

HString::HString(const HString & rhs):
	AString(rhs.GetStr())
	{
		fillLoc();
	}

HString::HString(const AString & rhs):
	AString(rhs)
	{
		fillLoc();
	}

HString::HString(const char * const str):
	AString(str)
	{
		fillLoc();
	}

HString::HString(const char ch):
	AString(ch)
	{
		fillLoc();
	}

HString::~HString()
{
	itsNumber = 0;
	delete [] itsLocation;
}

HString& HString::operator=(const HString & rhs)
{
	if (this == &rhs)
		return *this;

	itsLength=rhs.GetLen();
	delete [] itsString;
	itsString = new char[itsLength+1];

	strcpy(itsString,rhs.GetStr());

	delete[] itsLocation;

//	fillLoc();	//비효율적.
	itsNumber=rhs.GetNum();
	itsLocation = new int[itsNumber/LocRate+1];
	for(size_t i=0;i<itsNumber/LocRate+1;i++)
		itsLocation[i]=rhs.GetLoc(i*LocRate);

	return *this;
}

void HString::operator+=(const HString& rhs)
{
	itsLength+=rhs.GetLen();

	char *temp = new char[itsLength+1];

	strcpy(temp,itsString);
	strcat(temp,rhs.GetStr());

	delete [] itsString;
	itsString = temp;

	delete[] itsLocation;
	fillLoc();
}

void HString::operator+=(const char ch)
{
	char * temp = new char[itsLength+2];

	strcpy(temp,itsString);
	temp[itsLength++] = ch;
	temp[itsLength] = '\0';

	delete [] itsString;
	itsString = temp;

// 꼭 위치를 추가 해야하는 상황에서만 추가.
	if( itsNumber % LocRate == 0 )
	{
		delete[] itsLocation;
		fillLoc();
	}
	else
		itsNumber++;
}

// LocRate(e.g. 10개) 단위로 저장된 위치부터 원하는 위치를 찾아준다.
int HString::GetLoc(int p) const	
{
	if( !itsNumber || p<0 || p>=itsNumber )
		return -1;

	int start = itsLocation[p / LocRate];
	
	for(int count=0,i=0;count<LocRate;count++,i++)
	{
		if( p % LocRate == count )
			return (int)(start+i);
		if(Is2byteCharacter(itsString[start+i]))
			i++;
	}
	return -1;
}

void HString::Clear()
{
	AString::Clear();
	//char * temp = new char[1];
	//*temp = '\0';

	//delete[] itsString;
	//itsString = temp;
	//itsLength = 0;
	
	fillLoc();
}

HString HString::SubStr( int start, int end ) const
{
	if( !itsNumber || start >= itsNumber || end < 0 || start > end )
		return "";

	start = ( start <= 0 ) ? 0 :GetLoc(start);
	end = ( end < itsNumber )? GetLoc(end) : GetLoc(itsNumber-1);

	if(Is2byteCharacter(itsString[end]))
		end++;

	int SubStrLen = end-start+1;
	char *temp = new char[SubStrLen+1];

	strncpy(temp,&itsString[start],SubStrLen);
	temp[SubStrLen] = '\0';	

	HString ret( temp );
	delete[] temp;

	return ret;
}

int HString::Find( char ch, int position ) const
{
	char *ptr;

	if( !itsNumber || position >= itsNumber || Is2byteCharacter(ch) )
		return -1;

	if( position < 0 )
		position = 0;

	if((ptr=strchr(&itsString[GetLoc(position)],ch)) == NULL)
		return -1;

	int n = ptr-itsString;

	for(int i=position;i<itsNumber;i++)
		if(GetLoc(i)==n)
			return (int)i;

	return -1;
}

int HString::Find( HString str, int position ) const
{
	char * ptr;

	if( !itsNumber || position >= itsNumber )
		return -1;

	if( position < 0 )
		position = 0;

	if( (ptr=strstr(&itsString[GetLoc(position)],str.GetStr())) == NULL)
		return -1;

	int n = ptr-itsString;

	for(int i=position;i<itsNumber;i++)
		if(GetLoc(i)==n)
			return i;

	return -1;
}

// LocRate(e.g. 10개) 마다 위치를 한번씩 저장한다. 문자열 처음부터 끝까지 선형 접근한다.
void HString::fillLoc()
{
	itsLocation = new int[itsLength/LocRate+1];
	
	itsNumber=0;
	for(int count=0,i=0;i<itsLength;i++,itsNumber++)
	{
		if(itsNumber%LocRate==0)
			itsLocation[count++]=i;

		if(Is2byteCharacter(itsString[i]))
			i++;
	}
}

