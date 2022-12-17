#include "Lexer.h"
#include "Circuit.h"

Message Lexer::produce_tokens(std::string in) {
	char start = in.at(0);
	switch (start)
	{
	case '{':
	{
        if (in.back() != '}')
        {
            Message wrong;
            wrong.message = "Circuit header incomplete\n";
            wrong.incorrect = true;
            return wrong;
        }
        Circuit c(in.substr(1,in.length()-1));
        m_cvec.push_back(&c);
        m_cstack.push(&c);
		break;
	}
    case 'I':
    {
        if (in.substr(0, in.find(':')) != "IN")
        {
            Message wrong;
            wrong.message = "Unknown token:" + in.substr(0, in.find(':')) +"\n";
            wrong.incorrect = true;
            return wrong;
        }
        std::string temp = in.substr(in.find(':')+1,in.length());
        while (temp.length() > 0)
        {
            int comma = temp.find(',');
            std::string input = temp.substr(0,comma);
            Input i(input);
            m_cstack.top()->add_component(&i);
            temp = temp.substr(comma+1);
        }
        break;
    }
    case 'A':
    {
        if (in.substr(0, in.find(':')) != "AND")
        {
            Message wrong;
            wrong.message = "Unknown token:" + in.substr(0, in.find(':')) +"\n";
            wrong.incorrect = true;
            return wrong;
        }
        std::string temp = in.substr(in.find(':')+1,in.length());
        while (temp.length() > 0)
        {
            int comma = temp.find(','); //search for # later
            std::string input = temp.substr(0,comma);
            std::string name = input.substr(0, input.find('#'));
            int num = std::stoi(input.substr(input.find('#') + 1));

            /*And a(input);
            m_cstack.top()->add_component(&a);
            temp = temp.substr(comma + 1);*/
        }
        break;
    }
	}
    Message right;
    right.message = "OK\n";
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
    right.message = "OK\n";
    return right;
}

void Lexer::output_linevec()
{
    for (auto i : m_linevec)
    {
        std::cout << i << "\n";
    }
}