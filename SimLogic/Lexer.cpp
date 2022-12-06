#include "Lexer.h"

Message Lexer::produce_tokens(std::string in) {
	char start = in.at(0);
	switch (start)
	{
	case '{':
	{
		if(in.back()!='}')
		break;
	}
	}
    Message right;
    right.message = "OK";
    return right;
}

Message Lexer::read_file(std::string in)
{
    std::ifstream ifs;
    ifs.open(in);
    if (!ifs) {
        ifs.close();
        Message wrong;
        wrong.message = "Read failed. Path: " + in + "\n";
        wrong.incorrect = true;
        return wrong;
    }

    std::string a;
    while (std::getline(ifs, a)) //when reading from file, space and newline are both used as separators
    {
        m_linevec.push_back(a);
    }
    ifs.close();
    Message right;
    right.message = "OK";
    return right;
}