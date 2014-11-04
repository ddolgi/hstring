#ifndef __HString_H__
#define __HString_H__

#include "AString.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Title  : HString(HanGeul-String) Class.
// Author : jhbyun@nlp.korea.ac.kr
// Date   : 2006.9.6
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HanPhonemeLoc 0xa4
#define HanPhonemeLocJ 0xa1
#define HanPhonemeLocM 0xbf

static bool Is2byteCharacter(char ch) { return ch<0; } 
static bool IsHan(char ch) { return (unsigned char)ch >= 0xb0 && (unsigned char)ch <= 0xc8; };
static bool IsHanPhoneme(char ch) { return (unsigned char)ch == HanPhonemeLoc; };

#define LocRate 10	//위치 저장 비율  - 예 : 10 -> 10문자당 한 번씩 위치를 기억.

class HString : public AString	// AString을 상속하는 class. 그러나 offset이 2byte문자 처리됨.
{
public :
	HString();
	HString(const HString &);
	HString(const AString &);
	HString(const char * const);
	HString(const char);
	~HString();

	HString & operator= (const HString &);
	void operator+=(const HString&);
	void operator+=(const char);
	AString operator[](int offset) const { return GetNth(offset); };

	int GetNum() const { return itsNumber; }
	int GetLoc(int p) const;	// private?
	AString GetNth(int offset) const
		{ return (offset>=itsNumber || offset < 0 )? "" : SubStr(offset,offset).GetStr(); }

	void Clear();


	// 이후 함수들에서 쓰이는 위치는 n번째 문자를 나타낸다.
	HString Left( int nCount ) const			{ return SubStr( 0, nCount-1 ); }
	HString Right( int nCount ) const			{ return SubStr( itsNumber - nCount, itsNumber-1 ); }
	HString Mid( int nFirst ) const				{ return SubStr( nFirst, itsNumber-1 ); }
	HString Mid( int nFirst, int nCount ) const	{ return SubStr( nFirst, nFirst+nCount-1 );  }

	HString SubStr( int start, int end ) const;

	int Find( char , int position = 0 ) const;
	int Find( HString , int position = 0 ) const;
	HString Delete( int nIndex, int nCount = 1 ) const
		{ return ( nIndex >= itsNumber ) ? HString(*this) : Left( nIndex ) + Mid( nIndex+nCount ); }

private :
	void fillLoc();

	int itsNumber;	// 문자의 개수 ( 2byte 문자 포함 )
	int * itsLocation;	// 문자 위치정보 배열
};

#endif


