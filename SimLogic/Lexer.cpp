#include "Lexer.h"
#include "Circuit.h"

// **note on substr: s.substr(start_idx,length) not s.substr(start_idx,end_idx)**
// to get start -> end: s.substr(start_idx,end_idx-start_idx+1)

//todo: check for # on xor and not, notify user that (xor|not)#num is incorrect:
//XOR on numerous inputs is not standardized
//NOT is strictly 1 in 1 out

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
			break;
		}
		}
		break;
	}
	case 'N':
	{
		if (in.substr(0, in.find(':')) != "NOT")
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
			m_cstack.top()->add_component(std::make_shared<Not>(input));
		}
		break;
	}
	case 'X':
	{
		if (in.substr(0, in.find(':')) != "XOR")
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
			m_cstack.top()->add_component(std::make_shared<Xor>(input));
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
	}
	Message right;
	right.message = "OK\n";
	return right;
}

Message Lexer::evaluate_circ()
{
	//check later if the circuit is {main}
	std::cout << "input values(0 or 1) for circuit " << m_cvec.at(0)->get_name() << ":\n";
	std::shared_ptr<std::vector<std::shared_ptr<Component>>> invec = m_cvec.at(0)->get_inputs();
	for (size_t i = 0; i < invec->size(); ++i)
	{
		std::cout << "input " << invec->at(i)->get_name() << ": ";
		int val = -1;
		std::cin >> val;
		if ((val != 0) && (val != 1))
		{
			Message wrong;
			wrong.message = "Incorrect input\n";
			wrong.incorrect = true;
			return wrong;
		}
		if(val==1)
			invec->at(i)->propagate(true);
		else
			invec->at(i)->propagate(false);
	}
	std::string build = "";
	std::shared_ptr<std::vector<std::shared_ptr<Component>>> outvec = m_cvec.at(0)->get_outputs();
	for (size_t i = 0; i < outvec->size(); ++i)
	{
		build = build + outvec->at(i)->get_name() + ": " + std::to_string(outvec->at(i)->get_state()) + "\n";
	}
	Message right;
	right.message = build;
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