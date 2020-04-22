#pragma once

class Operatorok {
public:
	int honnan;
	int hova;

	void kiir() {
		std::cout << this->honnan+1 << " -> " << this->hova+1;
	}
};
