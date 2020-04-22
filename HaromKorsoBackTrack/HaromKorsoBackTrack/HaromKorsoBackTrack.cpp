#include <stdlib.h>
#include <iostream>
#include "Csucs.h"

int main(){
	int maxertek[3] = { 2,3,5 };
	std::vector<Allapot> csucsvoltmar;

	Csucs* head;
	Csucs* uj;
	Csucs* tmp;
	Csucs egy;

	uj = new Csucs();
	uj->korso[2] = 5;
	uj->elso = uj;
	uj->OperatorKigyujtes(maxertek);
	tmp = uj;
	head = uj;
	csucsvoltmar.push_back({ head->korso[0],head->korso[1],head->korso[2]});
	
	while (!tmp->Celallapot() && tmp!=NULL)
	{	
		if (tmp->VanOperator())
		{
			tmp->OperatorKivalasztas();
			int ontottmennyiseg = 0;

			tmp->kiirkorso(); 
			bool csucsnemvoltmeg = tmp->OperatorralEloallitottCsucsVolteMar(maxertek,csucsvoltmar,ontottmennyiseg);
			if (csucsnemvoltmeg)
			{
				tmp->UjCsucsFelvetele(uj, maxertek, ontottmennyiseg);
				tmp->kovetkezo->elozo = tmp;
				tmp->kovetkezo->elso = tmp->elso;
				tmp = tmp->kovetkezo;
				uj = tmp;			
				csucsvoltmar.push_back({ tmp->korso[0], tmp->korso[1], tmp->korso[2]});
			}
			else
			{
				tmp->kiirhasznaltoperator(); std::cout << " operatorra letezo csucsot kapnank" << std::endl;
			}

		}
		else
		{
			Csucs* csucstorles = tmp;
			tmp = tmp->elozo;
			uj = tmp;
			delete csucstorles;
		}
	}
	return 0;
}