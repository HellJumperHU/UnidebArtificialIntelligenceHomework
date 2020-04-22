#pragma once
#include <vector>
#include "Operator.h"
#include "Allapot.h"

class Csucs{
public:
	int korso[3] = { 0,0,0 };
	Operatorok lehetsegesoperatorok[6];
	Operatorok hasznaltoperator;
	Csucs* elso; 
	Csucs* elozo;
	Csucs* kovetkezo;

	bool operator==(const Csucs& csucs) {
		if (this->korso[0] == csucs.korso[0] &&
			this->korso[1] == csucs.korso[1] &&
			this->korso[2] == csucs.korso[2])
			return true;
		return false;
	}

	bool operator==(const std::vector<Allapot> vectorkorso){
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
		if (this == NULL) {
			std::cout << "Nincs Megoldas :<" << std::endl;
			return false;
		}

		if (this->korso[2] == 4) {
			std::cout << std::endl << std::endl << "Celallapotba ert!!!" << std::endl << "Melynek utvonala:" << std::endl;
			Csucs* csucs = this->elso;
			while (csucs != NULL) {
				csucs->kiirkorso();
				csucs = csucs->kovetkezo;
				
			}
			return true;
		}
		return false;
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
		for (int operatorindex = 5; operatorindex >=0; operatorindex--)
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

	bool OperatorralEloallitottCsucsVolteMar(int max[3],std::vector<Allapot> VectorCsucsVoltMar, int& ontottmennyiseg) {
		Csucs* csi = new Csucs();
		csi->EgyenloMasikKorso(this);
		csi->hasznaltoperator = this->hasznaltoperator;
		ontottmennyiseg = this->OntottMennyiseg(max);
		csi->Ontes(ontottmennyiseg);

		bool nemvoltacsucs= csi->NemVoltMegACsucs(VectorCsucsVoltMar);
		return nemvoltacsucs;
	}


	int OntottMennyiseg(int maxertek[3]) {
		if (maxertek[this->hasznaltoperator.hova] - this->korso[this->hasznaltoperator.hova] > this->korso[this->hasznaltoperator.honnan])
			return this->korso[this->hasznaltoperator.honnan];

		return maxertek[this->hasznaltoperator.hova] - this->korso[this->hasznaltoperator.hova];
	}

	void UjCsucsFelvetele(Csucs * uj,int max[3],int ontottmennyiseg) {
		uj = new Csucs;
		uj->elozo = this;
		uj->elso = this->elso;
		this->kovetkezo = uj;
		uj->EgyenloMasikKorso(this);
		uj->hasznaltoperator = this->hasznaltoperator;
		uj->Ontes(ontottmennyiseg);
		uj->OperatorKigyujtes(max);
	}


#pragma region Kiiras
	void kiirkorso() {
		std::cout << "(" << this->korso[0] << "," << this->korso[1] << "," << this->korso[2] << ")" << std::endl;
	}
	
	void kiirlehetsegesoperator() {
		std::cout << "Honnan  ->  Hova" << std::endl;
		for (int operatorsorszam = 0; operatorsorszam < 6; operatorsorszam++)
			if(this->lehetsegesoperatorok[operatorsorszam].honnan>-1)
				this->lehetsegesoperatorok[operatorsorszam].kiir();
	}

	void kiirhasznaltoperator() {
		this->hasznaltoperator.kiir();
	}

#pragma endregion

	Csucs() {
		for (int operatorsorszam = 0; operatorsorszam < 6; operatorsorszam++)
			lehetsegesoperatorok[operatorsorszam] = { -1,-1 };
		elso = NULL;
		kovetkezo = NULL;
		elozo = NULL;
		hasznaltoperator = {-1,-1};
	}
	~Csucs(){}
};