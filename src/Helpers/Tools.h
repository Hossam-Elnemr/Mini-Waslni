#pragma once
# include "Globals.h"
# include "QMessageBox.h"
class Tools {
public:
	static bool isSpecialChar(char c);
    static bool validateName(string name, QMainWindow*); // validations on edge/node/graph/user name
    void static FirstCharacter(QMainWindow*);
    void static bridgeFound(QMainWindow*);
    bool static isEqual(string s1, string s2);
};
