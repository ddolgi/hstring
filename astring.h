#ifndef __AString_H__
#define __AString_H__

////////////////////////////////////////////////////////////////////////////////
// Title  : AString(Alphabet-String) Class.
// Author : jhbyun@nlp.korea.ac.kr
// Date   : 2006.9.6
////////////////////////////////////////////////////////////////////////////////

class AString
{
public:
	AString();
	AString(const AString &);
	AString(const char *const);
	AString(const char);
	~AString();

	AString & operator= (const AString &);
	void 	operator+=(const AString &);
//	void 	operator+=(const char);
	AString operator+(const AString &);
//	AString operator+(const char ch);
	friend AString operator+(const AString&, const AString&);
//	friend AString operator+(const char ch, const AString&);
	bool 	operator==( const AString & rhs ) const;
	bool 	operator!=( const AString & rhs ) const { return !(*this==rhs); }

	char & 	operator[](int);
	char 	operator[](int p) const { return GetAt(p); };

	int 	GetLen() const { return itsLength; }
	const char * GetStr() const { return itsString; }
	char * 	GetStrP() const { return itsString; }
	char 	GetAt(int offset) const
	{ return ( offset >= itsLength || offset < 0 )? '\0' : itsString[offset]; }

	bool 	SetAt(int , const char );

	bool 	IsEmpty() const { return !itsLength; }
	void	Clear();

	AString Left( int nCount ) const 			{ return SubStr( 0, nCount-1 ); }
	AString Right( int nCount ) const			{ return SubStr( itsLength-nCount, itsLength-1 ); }
	AString Mid( int nFirst ) const				{ return SubStr( nFirst, itsLength-1 ); }
	AString Mid( int nFirst, int nCount ) const	{ return SubStr( nFirst, nFirst+nCount-1 ); }

	AString SubStr( int start, int end ) const;

	int		Find( char , int position = 0 ) const;
	int		Find( AString , int position = 0 )  const;
	AString Delete( int nIndex, int nCount = 1 ) const
	{ return ( nCount >= itsLength )? *this : Left( nIndex ) + Mid( nIndex+nCount ); }

protected :
	char * itsString;
	int itsLength;
};

#endif

