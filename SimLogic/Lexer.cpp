#include "Lexer.h"
#include "Circuit.h"

// **note on substr: s.substr(start_idx,length) not s.substr(start_idx,end_idx)**
// to get start -> end: s.substr(start_idx,end_idx-start_idx+1)

Message Lexer::produce_tokens(std::string in) {
	if (in.length() < 2)
	{
		Message wrong;
		wrong.message = "Unknown token: " + in + "\n";
		wrong.incorrect = true;
		return wrong;
	}
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
		if (in.at(1) == '/')
		{
			m_cstack.pop();
			break;
		}
		//std::shared_ptr<Circuit> c(new Circuit(in.substr(1, in.length() - 1)));
		auto c = std::make_shared<Circuit>(in.substr(1, in.length() - 2));
		m_cvec.push_back(c);
		m_cstack.push(c);
		std::cout << "{ ok";
		break;
	}
	case 'I':
	{
		if (in.substr(0, in.find(':')) != "IN")
		{
			Message wrong;
			wrong.message = "Unknown token: " + in.substr(0, in.find(':')) + "\n";
			wrong.incorrect = true;
			return wrong;
		}
		std::string temp = in.substr(in.find(':') + 1);
		while (temp != "")
		{
			std::string input;
			if (temp.find(',') == std::string::npos)
			{
				input = temp;
				temp = "";
			}
			else
			{
				input = temp.substr(0, temp.find(','));
				temp = temp.substr(temp.find(',') + 1);
			}
			//std::shared_ptr<Component> i(new Input(input));
			m_cstack.top()->add_component(std::make_shared<Input>(input));
		}
		std::cout << "inp ok";
		break;
	}
	case 'A':
	{
		if (in.substr(0, in.find(':')) != "AND")
		{
			Message wrong;
			wrong.message = "Unknown token: " + in.substr(0, in.find(':')) + "\n";
			wrong.incorrect = true;
			return wrong;
		}
		std::string temp = in.substr(in.find(':') + 1);
		while (temp != "")
		{
			std::string input;
			if (temp.find(',') == std::string::npos)
			{
				input = temp;
				temp = "";
			}
			else
			{
				input = temp.substr(0, temp.find(','));
				temp = temp.substr(temp.find(',') + 1);
			}
			if ((input.find('#') == std::string::npos) || (input.find('#') == input.length() - 1))
			{
				Message wrong;
				wrong.message = "Missing input identifier for gate AND: " + input + "\n";
				wrong.incorrect = true;
				return wrong;
			}
			std::string name = input.substr(0, input.find('#'));
			int num = std::stoi(input.substr(input.find('#') + 1));
			m_cstack.top()->add_component(std::make_shared<And>(name, num));
		}
		std::cout << "and ok";
		break;
	}
	case 'O':
	{
		switch (in.at(1))
		{
		case 'R':
		{
			if (in.substr(0, in.find(':')) != "OR")
			{
				Message wrong;
				wrong.message = "Unknown token: " + in.substr(0, in.find(':')) + "\n";
				wrong.incorrect = true;
				return wrong;
			}
			std::string temp = in.substr(in.find(':') + 1);
			while (temp != "")
			{
				std::string input;
				if (temp.find(',') == std::string::npos)
				{
					input = temp;
					temp = "";
				}
				else
				{
					input = temp.substr(0, temp.find(','));
					temp = temp.substr(temp.find(',') + 1);
				}
				if ((input.find('#') == std::string::npos) || (input.find('#') == input.length() - 1))
				{
					Message wrong;
					wrong.message = "Missing input identifier for gate OR: " + in + "\n";
					wrong.incorrect = true;
					return wrong;
				}
				std::string name = input.substr(0, input.find('#'));
				int num = std::stoi(input.substr(input.find('#') + 1));
				m_cstack.top()->add_component(std::make_shared<Or>(name, num));
			}
			std::cout << "or ok";
			break;
		}
		case 'U':
		{
			if (in.substr(0, in.find(':')) != "OUT")
			{
				Message wrong;
				wrong.message = "Unknown token: " + in.substr(0, in.find(':')) + "\n";
				wrong.incorrect = true;
				return wrong;
			}
			std::string temp = in.substr(in.find(':') + 1, in.length());
			while (temp != "")
			{
				std::string input;
				if (temp.find(',') == std::string::npos)
				{
					input = temp;
					temp = "";
				}
				else
				{
					input = temp.substr(0, temp.find(','));
					temp = temp.substr(temp.find(',') + 1);
				}
				m_cstack.top()->add_component(std::make_shared<Output>(input));
			}
			std::cout << "out ok";
			break;
		}
		}
		break;
	}
	//at some point add Xor
	case '(':
	{
		if (in.find(')') == std::string::npos)
		{
			Message wrong;
			wrong.message = "Unmatched \'(\': " + in + "\n";
			wrong.incorrect = true;
			return wrong;
		}
		std::string temp = in.substr(1, in.find(')') - 1);
		std::vector<std::shared_ptr<Component>> tempcvec;
		while (temp != "")
		{
			std::string input;
			if (temp.find(',') == std::string::npos)
			{
				input = temp;
				temp = "";
			}
			else
			{
				input = temp.substr(0, temp.find(','));
				temp = temp.substr(temp.find(',') + 1);
			}
			std::shared_ptr<Component> finding = m_cstack.top()->find_component(input); // Lexer does not own this component
			if (finding == NULL)
			{
				Message wrong;
				wrong.message = "Component not found: " + input + "\n";
				wrong.incorrect = true;
				return wrong;
			}
			tempcvec.push_back(finding);
		}
		if (in.find("->") == std::string::npos)
		{
			Message wrong;
			wrong.message = "Missing \'->\': " + in + "\n";
			wrong.incorrect = true;
			return wrong;
		}
		std::string into = in.substr(in.find('>') + 1);
		std::shared_ptr<Component> finding = m_cstack.top()->find_component(into);
		if (finding == NULL)
		{
			Message wrong;
			wrong.message = "Component not found: " + into + "\n";
			wrong.incorrect = true;
			return wrong;
		}
		for (auto& c : tempcvec)
		{
			c->add_child(finding);
		}
		std::cout << "( ok";
		break;
	}
	default:
	{
		Message wrong;
		wrong.message = "Unknown token:" + in.substr(0, in.find(':')) + "\n";
		wrong.incorrect = true;
		return wrong;
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
	int c = 0;
	for (std::string s : m_linevec)
	{
		Message temp = produce_tokens(s);
		if (temp.incorrect)
		{
			return temp;
		}
		std::cout << ++c << std::endl;
	}
	Message right;
	right.message = "OK\n";
	return right;
}

void Lexer::output_linevec()
{
	int c = 0;
	for (auto i : m_linevec)
	{
		std::cout << ++c << ": " << i << "\n";
	}
}

void Lexer::output_circ()
{
	m_cvec.at(0)->print();
}