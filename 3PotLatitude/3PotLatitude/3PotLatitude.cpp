// 3PotLatitude.cpp : This file contains the 'main' function. Program execution begins and ends there.


// We have 3 pots
// first    = 2L
// second   = 3L
// third    = 5L
// At the beginning the 2L and the 3L pots are empty, only the 5L pots filled with liquid
// Destination : 5L pots should have 4L liquid

#include <iostream>
#include <vector>

class Pot{
public:
	int firstpot;
	int secondpot;
	int thirdpot;

	void operator=(const Pot& pot) {
		this->firstpot = pot.firstpot;
		this->secondpot = pot.secondpot;
		this->thirdpot = pot.thirdpot;
	}

	void Equal(int f, int s, int t) {
		this->firstpot = f;
		this->secondpot = s;
		this->thirdpot = t;
	}
};

class Operators {
public:
	int from;
	int target;
    void CoutThisPot() {
        std::cout << this->from << " --> " << this->target << std::endl;
    }
};

class State {
	State* head;
	State* parent;
	State* children;
	int pot[3];
	std::vector<State*>OpenNextState;
	std::vector<State*>ClosedNextState;
	std::vector<Operators> nonusedvalidoperators;
	Operators lastusedoperator;

public:
	bool operator==(const State& state) {
		if (this->pot[0] == state.pot[0] &&
			this->pot[1] == state.pot[1] &&
			this->pot[2] == state.pot[2])
			return true;
		return false;
	}

	bool operator==(const std::vector<Pot> vectorpot) {
		for (int vectorindex = 0; vectorindex < vectorpot.size(); vectorindex++)
		{
			if (this->pot[0] == vectorpot[vectorindex].firstpot &&
				this->pot[1] == vectorpot[vectorindex].secondpot &&
				this->pot[2] == vectorpot[vectorindex].thirdpot)
				return true;
		}
		return false;
	}

	void CoutThisPot() {
		std::cout << "(" << this->pot[0] << "," << this->pot[1] << "," << this->pot[2] << ")" << std::endl;
	}

	void EqualThisPot(State* state) {
		this->pot[0] = state->pot[0];
		this->pot[1] = state->pot[1];
		this->pot[2] = state->pot[2];
	}


	bool TargetState() {
		if (this == NULL) {
			std::cout << "Had not found solution :<" << std::endl;
			return false;
		}

		if (this->pot[2] == 4) {
			std::cout << std::endl << std::endl << "Target state reached!!!" << std::endl << "Its path:" << std::endl;
			State* state = this->head;
			while (state != NULL) {
				state->CoutThisPot();
				state = state->children;
			}
			return true;
		}
		return false;
	}

	bool FromNotEmpty(State* fromsteteptr, int fromindex) {
		if (fromsteteptr->pot[fromindex] > 0)
			return true;
		return false;
	}

	bool NotPouringToItself(int fromindex, int targetpotindex) {
		if (fromindex == targetpotindex)
			return false;
		return true;
	}

	bool TargetPotIsNotFull(State* tostateptr, int maxpotcapacitypotcapacity[3], int targetpotindex) {
		if (tostateptr->pot[targetpotindex] == maxpotcapacitypotcapacity[targetpotindex])
		{
			return false;
		}
		return true;
	}

	bool ValidOperation(State* stateptr, int maxpotcapacity[3], int fromindex, int targetpotindex) {
		if (!FromNotEmpty(stateptr, fromindex))
			return false;
		if (!NotPouringToItself(fromindex, targetpotindex))
			return false;
		if (!TargetPotIsNotFull(stateptr, maxpotcapacity, targetpotindex))
			return false;
		return true;
	}


	void GatheringValidOperators(int maxpotcapacity[3]) {
		int index = 0;
		for (int frompot = 0; frompot < 3; frompot++)
		{
			for (int targetpot = 0; targetpot < 3; targetpot++)
			{
				if (ValidOperation(this, maxpotcapacity, frompot, targetpot))
				{
					this->nonusedvalidoperators[index] = { frompot,targetpot };
					index++;
				}
			}
		}
	}

	bool StillLeftValidOperator(State* currentstateptr) {
		if (currentstateptr->nonusedvalidoperators[0].from == -1)
			return false;
		return true;
	}

	bool StillLeftValidOperator() {
		if (this->nonusedvalidoperators[0].from == -1)
			return false;
		return true;
	}

	//A lehetseges operátorokat {from, targetpot} párokban tároljuk a tömbben
	//Az utolsó elemtõl indulunk es nézzük van-e használható operátor
	//Ha van használható operátor akkor azt átrakjuk a használtoperátorok közé ÉS a helyére {-1, -1} párt szúrunk be	
	void ChoosingAValidOperator() {
		for (int operatorindex = 5; operatorindex >= 0; operatorindex--)
		{
			if (this->nonusedvalidoperators[operatorindex].from > -1) {
				this->lastusedoperator = nonusedvalidoperators[operatorindex];
				nonusedvalidoperators[operatorindex] = { -1,-1 };
				break;
			}
		}
	}

	bool ThisStateIsUnexplorered(std::vector<Pot> StatesThatAreAlreadyExplorered) {
		for (int vektorindex = 0; vektorindex < StatesThatAreAlreadyExplorered.size(); vektorindex++)
		{
			if (this->pot[0] == StatesThatAreAlreadyExplorered[vektorindex].firstpot &&
				this->pot[1] == StatesThatAreAlreadyExplorered[vektorindex].secondpot &&
				this->pot[2] == StatesThatAreAlreadyExplorered[vektorindex].thirdpot) {
				return false;
			}
		}
		return true;
	}

	void Pouring(int ammountofpouring) {
		this->pot[this->lastusedoperator.from] -= ammountofpouring;
		this->pot[this->lastusedoperator.target] += ammountofpouring;
	}

	bool IsThisStateAlreadyExplorered(int maxpotcapacity[3], std::vector<Pot> StatesThatAreAlreadyExplorered, int& ammountofpouring) {
		State* tmpstate = new State();
		tmpstate->EqualThisPot(this);
		tmpstate->lastusedoperator = this->lastusedoperator;
		ammountofpouring = this->GetTheAmmountOfPouring(maxpotcapacity);
		tmpstate->Pouring(ammountofpouring);

		bool isthestateunexplorered = tmpstate->ThisStateIsUnexplorered(StatesThatAreAlreadyExplorered);
		return isthestateunexplorered;
	}


	int GetTheAmmountOfPouring(int maxpotcapacity[3]) {
		if (maxpotcapacity[this->lastusedoperator.target] - this->pot[this->lastusedoperator.target] > this->pot[this->lastusedoperator.from])
			return this->pot[this->lastusedoperator.from];

		return maxpotcapacity[this->lastusedoperator.target] - this->pot[this->lastusedoperator.target];
	}

	void CreateNewLinkedListElement(State* uj, int maxpotcapacity[3], int ammountofpouring) {
		uj = new State;
		uj->parent = this;
		uj->head = this->head;
		this->children = uj;
		uj->EqualThisPot(this);
		uj->lastusedoperator = this->lastusedoperator;
		uj->Pouring(ammountofpouring);

	}
	State() {
		head = NULL;
		parent = NULL;
		children = NULL;		
	}
	~State() {};

};

int main()
{

    std::cout << "Hello World!\n";
}