#include "data.h"
#include <stdio.h>
#include <stdlib.h>

int validaData(Data data){
	if(data.dia <= 31 && data.mes <= 12){
		if(data.ano >= 1000 && data.ano <= 9999){
			if((data.dia < 29 && data.mes == 2) || (data.mes == 2 && data.dia < 30 && (data.ano % 4 == 0 && (data.ano % 400 == 0 || data.ano % 100 != 0))))
				return 1;
			else if(data.dia <= 30 && (data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11))
				return 1;
			else if(data.dia <= 31 && (data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12))
				return 1;
		}
	}

	return 0;
}