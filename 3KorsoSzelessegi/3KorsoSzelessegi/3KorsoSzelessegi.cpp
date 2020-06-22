// 3KorsoSzelessegi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <Windows.h>
#include <crtdbg.h>



class Operatorok {
public:
	int honnan;
	int hova;

	void kiir() {
		std::cout << this->honnan + 1 << " -> " << this->hova + 1;
	}
};

struct Allapot
{
	int elso;
	int masodik;
	int harmadik;
};

class Csucs {
public:
	Csucs* elso;
	Csucs* elozo;
	Csucs* kovetkezo;
	int korso[3] = { 0,0,0 };
	int melyseg;
	bool nyilteacsucs;
	std::vector<Csucs*> nyiltgyermekcsucsok;
	std::vector<Csucs*> zartgyermekcsucsok;
	Operatorok lehetsegesoperatorok[6];
	Operatorok hasznaltoperator;

	bool operator==(const Csucs& csucs) {
		if (this->korso[0] == csucs.korso[0] &&
			this->korso[1] == csucs.korso[1] &&
			this->korso[2] == csucs.korso[2])
			return true;
		return false;
	}

	bool operator==(const std::vector<Allapot> vectorkorso) {
		for (int vectorindex = 0; vectorindex < vectorkorso.size(); vectorindex++)
		{
			if (this->korso[0] == vectorkorso[vectorindex].elso &&
				this->korso[1] == vectorkorso[vectorindex].masodik &&
				this->korso[2] == vectorkorso[vectorindex].harmadik)
				return true;
		}
		return false;
	}

	void EgyenloMasikKorso(Csucs* csucs) {
		this->korso[0] = csucs->korso[0];
		this->korso[1] = csucs->korso[1];
		this->korso[2] = csucs->korso[2];
	}

	bool Celallapot() {
		if (this == NULL ) {
			std::cout << "Nincs Megoldas :<" << std::endl;
			return false;
		}		

		if (this->korso[2] == 4) {			
			std::cout << std::endl << std::endl << "Celallapotba ert!!!" << std::endl << "Melynek utvonala:" << std::endl;
			Csucs* csucs = this;
			while (this->elso!=csucs)
			{
				csucs->elozo->kovetkezo = csucs;
				csucs = csucs->elozo;
			}
			while (csucs != NULL) {
				std::cout << "Melyseg: " << csucs->melyseg<<"  ";
				csucs->kiirkorso();
				csucs = csucs->kovetkezo;
			}
			return true;
		}

		if (this==this->elso && this->nyilteacsucs==false)
		{
			std::cout << "Nincs Megoldas :<" << std::endl;
			return false;
		}
		
		
		return false;
	}

	bool VanNyiltGyermekCsucs() {
		if (this->nyiltgyermekcsucsok.size()==0)		
			return false;
		return true;
	}

	bool HonnanNemUres(Csucs* honnancsucsptr, int honnanindex) {
		if (honnancsucsptr->korso[honnanindex] > 0)
			return true;
		return false;
	}

	bool NemOnmagabaOnt(int honnanindex, int hovaindex) {
		if (honnanindex == hovaindex)
			return false;
		return true;
	}

	bool HovaNincsTele(Csucs* hovacsucsptr, int max[3], int hovaindex) {
		if (hovacsucsptr->korso[hovaindex] == max[hovaindex])
		{
			return false;
		}
		return true;
	}

	bool OperatoralkAlmazasElofeltetel(Csucs* csucsptr, int max[3], int honnanindex, int hovaindex) {
		if (!HonnanNemUres(csucsptr, honnanindex))
			return false;
		if (!NemOnmagabaOnt(honnanindex, hovaindex))
			return false;
		if (!HovaNincsTele(csucsptr, max, hovaindex))
			return false;
		return true;
	}

	void OperatorKigyujtes(int max[3]) {
		int index = 0;
		for (int HonnanOnt = 0; HonnanOnt < 3; HonnanOnt++)
		{
			for (int HovaOnt = 0; HovaOnt < 3; HovaOnt++)
			{
				if (OperatoralkAlmazasElofeltetel(this, max, HonnanOnt, HovaOnt))
				{
					this->lehetsegesoperatorok[index] = { HonnanOnt,HovaOnt };
					index++;
				}
			}
		}
	}

	bool VaneLehetsegesOperator(Csucs* jelenlegicsucsptr) {
		if (jelenlegicsucsptr->lehetsegesoperatorok[0].honnan == -1)
			return false;
		return true;
	}

	bool VanOperator() {
		if (this->lehetsegesoperatorok[0].honnan == -1)
			return false;
		return true;
	}

	//A lehetseges operátorokat {honnan, hova} párokban tároljuk a tömbben
	//Az utolsó elemtõl indulunk es nézzük van-e használható operátor
	//Ha van használható operátor akkor azt átrakjuk a használtoperátorok közé ÉS a helyére {-1, -1} párt szúrunk be	
	void OperatorKivalasztas() {
		for (int operatorindex = 5; operatorindex >= 0; operatorindex--)
		{
			if (this->lehetsegesoperatorok[operatorindex].honnan > -1) {
				this->hasznaltoperator = lehetsegesoperatorok[operatorindex];
				lehetsegesoperatorok[operatorindex] = { -1,-1 };
				break;
			}
		}
	}

	bool NemVoltMegACsucs(std::vector<Allapot> CsucsVoltMar) {
		for (int vektorindex = 0; vektorindex < CsucsVoltMar.size(); vektorindex++)
		{
			if (this->korso[0] == CsucsVoltMar[vektorindex].elso &&
				this->korso[1] == CsucsVoltMar[vektorindex].masodik &&
				this->korso[2] == CsucsVoltMar[vektorindex].harmadik) {
				return false;
			}
		}
		return true;
	}

	void Ontes(int ontottmennyiseg) {
		this->korso[this->hasznaltoperator.honnan] -= ontottmennyiseg;
		this->korso[this->hasznaltoperator.hova] += ontottmennyiseg;
	}

	bool OperatorralEloallitottCsucsVolteMar(int max[3], std::vector<Allapot> VectorCsucsVoltMar, int& ontottmennyiseg) {
		Csucs* csi = new Csucs();
		csi->EgyenloMasikKorso(this);
		csi->hasznaltoperator = this->hasznaltoperator;
		ontottmennyiseg = this->OntottMennyiseg(max);
		csi->Ontes(ontottmennyiseg);

		bool nemvoltacsucs = csi->NemVoltMegACsucs(VectorCsucsVoltMar);
		return nemvoltacsucs;
	}

	int OntottMennyiseg(int maxertek[3]) {
		if (maxertek[this->hasznaltoperator.hova] - this->korso[this->hasznaltoperator.hova] > this->korso[this->hasznaltoperator.honnan])
			return this->korso[this->hasznaltoperator.honnan];

		return maxertek[this->hasznaltoperator.hova] - this->korso[this->hasznaltoperator.hova];
	}

	void UjCsucsFelvetele(Csucs* uj, int max[3], int ontottmennyiseg, std::vector<Csucs*>& kiterjesztesrevarocsucsptr) {
		uj = new Csucs;
		uj->elozo = this;
		uj->elso = this->elso;			
		//this->kovetkezo = uj;
		uj->EgyenloMasikKorso(this);
		uj->hasznaltoperator = this->hasznaltoperator;
		uj->melyseg = uj->elozo->melyseg + 1;
		uj->Ontes(ontottmennyiseg);
		uj->OperatorKigyujtes(max);
		//uj->kiirkorsonincssortores(); std::cout << "szuloje:"; this->kiirkorso();
		this->nyiltgyermekcsucsok.push_back(uj);
		kiterjesztesrevarocsucsptr.push_back(uj);
	}

	void kiirkorso() {
		std::cout << "(" << this->korso[0] << "," << this->korso[1] << "," << this->korso[2] << ")" << std::endl;
	}

	void kiirkorsonincssortores() {
		std::cout << "(" << this->korso[0] << "," << this->korso[1] << "," << this->korso[2] << ") ";
	}

	void kiirlehetsegesoperator() {
		std::cout << "Honnan  ->  Hova" << std::endl;
		for (int operatorsorszam = 0; operatorsorszam < 6; operatorsorszam++)
			if (this->lehetsegesoperatorok[operatorsorszam].honnan > -1)
				this->lehetsegesoperatorok[operatorsorszam].kiir();
	}

	void kiirhasznaltoperator() {
		this->hasznaltoperator.kiir();
	}

	Csucs() {
		for (int operatorsorszam = 0; operatorsorszam < 6; operatorsorszam++)
			lehetsegesoperatorok[operatorsorszam] = { -1,-1 };
		elso = NULL;
		kovetkezo = NULL;
		elozo = NULL;
		hasznaltoperator = { -1,-1 };
		nyilteacsucs = true;
		melyseg = 0;
	}
	~Csucs() {}
};

std::ostream& operator<<(std::ostream& os, const Allapot allapot) {
	os <<"("<< allapot.elso << "," << allapot.masodik << "," << allapot.harmadik << ")" << std::endl;
	return os;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int maxertek[3] = { 2,3,5 };
	std::vector<Allapot> voltmarilyenkorsoallapot;
	std::vector<Csucs*> Kiterjesztesrevarocsucsptr;
	int utoljarakiterjesztettcsucsindex = -1;

	Csucs* uj;
	Csucs* tmp;

	uj = new Csucs();
	uj->korso[2] = 5;
	uj->elso = uj;
	uj->OperatorKigyujtes(maxertek);
	tmp = uj;	
	voltmarilyenkorsoallapot.push_back({ tmp->korso[0],tmp->korso[1],tmp->korso[2] });
	Kiterjesztesrevarocsucsptr.push_back(uj);
	utoljarakiterjesztettcsucsindex++;


	while (!tmp->Celallapot() && tmp != NULL && utoljarakiterjesztettcsucsindex<Kiterjesztesrevarocsucsptr.size()) {
		//std::cout << "Ezt terjesztjuk ki" << std::endl;
		uj = Kiterjesztesrevarocsucsptr[utoljarakiterjesztettcsucsindex];
		//uj->kiirkorso();
		tmp = uj;
		Csucs* tmpcsucs;
		while (uj->VanOperator()) {
			uj->OperatorKivalasztas();
			int ontottmennyiseg = 0;

			bool csucsnemvoltmeg = uj->OperatorralEloallitottCsucsVolteMar(maxertek, voltmarilyenkorsoallapot, ontottmennyiseg);
			if (csucsnemvoltmeg) {
				tmp->UjCsucsFelvetele(uj, maxertek, ontottmennyiseg, Kiterjesztesrevarocsucsptr);
				tmpcsucs = tmp->nyiltgyermekcsucsok[tmp->nyiltgyermekcsucsok.size() - 1];
				voltmarilyenkorsoallapot.push_back({ tmpcsucs->korso[0], tmpcsucs->korso[1], tmpcsucs->korso[2] });			
			}
		}
		

		tmpcsucs = uj;
		
		if (tmpcsucs->nyiltgyermekcsucsok.size() ==0) 
		{			
			//std::cout << "belepünk a lezaras if-be" << std::endl;
			while (tmpcsucs->nyiltgyermekcsucsok.size() ==0)
			{
				//std::cout << "belepunk a WHILE lezaras if-be" << std::endl;
				tmpcsucs->nyilteacsucs = false;

				if (tmpcsucs != tmpcsucs->elso)
				{
					std::vector<Csucs*> tmpgyermekcsucsptr;
					for (int nyiltgyermekindex = 0; nyiltgyermekindex < tmpcsucs->elozo->nyiltgyermekcsucsok.size(); nyiltgyermekindex++)
					{
						if (tmpcsucs->elozo->nyiltgyermekcsucsok[nyiltgyermekindex]->nyilteacsucs == false)
						{
							Csucs* tmpnyiltgyermekptr = tmpcsucs->elozo->nyiltgyermekcsucsok[nyiltgyermekindex];
							tmpcsucs->elozo->zartgyermekcsucsok.push_back(tmpnyiltgyermekptr);
							tmpcsucs->elozo->nyiltgyermekcsucsok.pop_back();
							//std::cout << std::endl << "Lezarjuk: "; tmpcsucs->kiirkorso();
							//std::cout << "Szulojenek ennyi nyilt csucsa van meg:" << tmpcsucs->elozo->nyiltgyermekcsucsok.size() << std::endl;
							
						}
						else
						{
							tmpgyermekcsucsptr.push_back(tmpcsucs->elozo->nyiltgyermekcsucsok[nyiltgyermekindex]);
						}
					}
					tmpcsucs->elozo->nyiltgyermekcsucsok.clear();
					for (int i = 0; i < tmpgyermekcsucsptr.size(); i++)
					{
						tmpcsucs->elozo->nyiltgyermekcsucsok.push_back(tmpgyermekcsucsptr[i]);
					}
					tmpcsucs = tmpcsucs->elozo;					
				}
				else
				{
					tmpcsucs->nyilteacsucs = false;
					break;
				}
			}
		}
		utoljarakiterjesztettcsucsindex++;	
		
	}
	for (int i = 0; i < Kiterjesztesrevarocsucsptr.size(); i++)
	{
		delete Kiterjesztesrevarocsucsptr[i];
	}
//	delete uj, tmp;

	//{shared ptr %!!}
	return 0;
}
