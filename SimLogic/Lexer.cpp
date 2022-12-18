#include "Lexer.h"
#include "Circuit.h"

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
		//Circuit c(in.substr(1, in.length() - 1));
		std::unique_ptr<Circuit> c(new Circuit(in.substr(1, in.length() - 1)));
		m_cvec.push_back(std::move(c));
		m_cstack.push(std::move(c));
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
		std::string temp = in.substr(in.find(':') + 1, in.length());
		while (temp.length() > 0)
		{
			std::string input;
			if (temp.find(',') == std::string::npos)
			{
				std::string input = temp;
			}
			else
			{
				std::string input = temp.substr(0, temp.find(','));
				temp = temp.substr(temp.find(',') + 1);
			}
			Input i(input);
			m_cstack.top()->add_component(&i);
		}
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
		std::string temp = in.substr(in.find(':') + 1, in.length());
		while (temp.length() > 0)
		{
			std::string input;
			if (temp.find(',') == std::string::npos)
			{
				std::string input = temp;
			}
			else
			{
				std::string input = temp.substr(0, temp.find(','));
				temp = temp.substr(temp.find(',') + 1);
			}
			if ((input.find('#') == std::string::npos) || (input.find('#') == input.length() - 1))
			{
				Message wrong;
				wrong.message = "Missing input identifier for gate AND: " + in + "\n";
				wrong.incorrect = true;
				return wrong;
			}
			std::string name = input.substr(0, input.find('#'));
			int num = std::stoi(input.substr(input.find('#') + 1));

			And a(name, num);
			m_cstack.top()->add_component(&a);
		}
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
			std::string temp = in.substr(in.find(':') + 1, in.length());
			while (temp.length() > 0)
			{
				std::string input;
				if (temp.find(',') == std::string::npos)
				{
					std::string input = temp;
				}
				else
				{
					std::string input = temp.substr(0, temp.find(','));
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

				Or o(name, num);
				m_cstack.top()->add_component(&o);
			}
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
			while (temp.length() > 0)
			{
				std::string input;
				if (temp.find(',') == std::string::npos)
				{
					std::string input = temp;
				}
				else
				{
					std::string input = temp.substr(0, temp.find(','));
					temp = temp.substr(temp.find(',') + 1);
				}
				Output o(input);
				m_cstack.top()->add_component(&o);
			}
			break;
		}
		}
		break;
	}
	case '(':
	{
		if (in.find(')') == std::string::npos)
		{
			Message wrong;
			wrong.message = "Unmatched \'(\': " + in + "\n";
			wrong.incorrect = true;
			return wrong;
		}
		std::string temp = in.substr(1, in.find(')'));
		std::vector<Component*> tempcvec;
		while (temp.length() > 0)
		{
			std::string input;
			if (temp.find(',') == std::string::npos)
			{
				std::string input = temp;
			}
			else
			{
				std::string input = temp.substr(0, temp.find(','));
				temp = temp.substr(temp.find(',') + 1);
			}
			Component* finding = m_cstack.top()->find_component(input);
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
		Component* finding = m_cstack.top()->find_component(into);
		if (finding == NULL)
		{
			Message wrong;
			wrong.message = "Component not found: " + into + "\n";
			wrong.incorrect = true;
			return wrong;
		}
		for (Component* c : tempcvec)
		{
			c->add_child(finding);
		}
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
	for (std::string s : m_linevec)
	{
		produce_tokens(s);
	}
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

void Lexer::output_circ()
{
	m_cvec.at(0)->print();
}