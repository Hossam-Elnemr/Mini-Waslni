# include "Tools.h"
bool Tools::isSpecialChar(char c) {
	return c == '*' || c == '^' || c == '#' || c == '@' || c == '>' || c == '<' || c == ')' || c == ';'
		|| c == '!' || c == '&' || c == '%' || c == '(' || c == ')' || c == '~' || c == '$' || c == '?'
		|| c == '{' || c == '}' || c == '[' || c == ']' || c == ':' || c == '|' || c == '+' || c == '-';
}

bool Tools::validateName(string name, QMainWindow* w) {
    if(name.empty() || !((name[0]<='z' && name[0]>='a') || (name[0]<='Z' && name[0]>='A'))) {
        FirstCharacter(w);
        return false;
    }
    return true;
}

bool Tools::validateSize(string name, QMainWindow* w) {
    return name.size() <= 2;
}

void Tools::FirstCharacter(QMainWindow* w) {
    QMessageBox::warning(w, "Invalid Input", "First character MUST be alphabet.");
}

bool Tools::isEqual(string s1, string s2) {
    if(s1.size() != s2.size())
        return false;
    int sz = s1.size();
    for(int i = 0; i<sz; ++i) {
        s1[i] = tolower(s1[i]);
        s2[i] = tolower(s2[i]);
    }
    cout << "Testing equal: " << s1 << ' ' << s2 << '\n';
    return s1 == s2;
}
