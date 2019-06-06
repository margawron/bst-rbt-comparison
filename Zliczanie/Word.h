#ifndef _WORD_H_
#define _WORD_H_

#include <string>
#include <ostream>

class Word {

	int times_used;
	std::string content;

public:
	Word(std::string content_);
	Word operator++(int dummy);
	friend std::istream& operator>>(std::istream& istream, Word& rhs);
	friend std::ostream& operator<<(std::ostream& ostream, Word& rhs);
	bool operator<(Word& rhs);
	bool operator==(Word& rhs);
	bool operator>(Word& rhs);
	bool operator<=(Word& rhs);
	bool operator>=(Word& rhs);
	int times_appeard();
	char * get_content();

};

#endif
