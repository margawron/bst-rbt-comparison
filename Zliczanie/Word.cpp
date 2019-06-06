
#include <string.h>
#include "Word.h"


Word::Word(std::string content_) :content(content_), times_used(0) {}

Word Word::operator++(int dummy)
{
	this->times_used++;
	return *this;
}

bool Word::operator<(Word & rhs)
{
	return this->content < rhs.content;
}

bool Word::operator==(Word & rhs)
{
	return this->content == rhs.content;
}

bool Word::operator>(Word & rhs)
{
	return this->content > rhs.content;
}

bool Word::operator<=(Word & rhs)
{
	return this->content <= rhs.content;
}

bool Word::operator>=(Word & rhs)
{
	return this->content >= rhs.content;
}

int Word::times_appeard()
{
	return this->times_used;
}

char * Word::get_content()
{
	return _strdup(content.c_str());
}

std::istream & operator>>(std::istream & istream, Word & rhs)
{
	istream >> rhs.content; 
	return istream;
}

std::ostream & operator<<(std::ostream & ostream, Word & rhs)
{
	ostream << rhs.content << " : " << rhs.times_used;
	return ostream;
}
