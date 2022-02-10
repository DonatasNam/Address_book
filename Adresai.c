#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct S_duomenys
{
    char vardas [20];
    char pavarde [20];
    char tele [15];
    char pastas[30];
    struct S_duomenys *po;
    struct S_duomenys *pries;
}duomenys;

/* duomenų įrašymas */
duomenys *irasas()
{
    printf("Įveskite adresato duomenis: \n");
    char input[100];
    fgets(input,99,stdin);
    duomenys *naujasAdr = malloc(sizeof(duomenys));
    if (naujasAdr == NULL){
        printf("Atminties klaida");
		exit(1);
    } else{
        sscanf(input,"%s %s %s %s", naujasAdr->vardas, naujasAdr->pavarde, naujasAdr->tele, naujasAdr->pastas);
        
        printf("Pridėtas adresatas:\nVardas: %s\nPavardė: %s\nTel.Nr: %s\nElektroninis paštas: %s\n",
         naujasAdr->vardas, 
         naujasAdr->pavarde, 
         naujasAdr->tele, 
         naujasAdr->pastas);
        printf("Įrašykite sekančią komandą. Jei norite komandą pakartoti spauskite 'Enter'\n");

        return naujasAdr;
    }

}

/* pridedama i pradzia*/
duomenys *pridetiipradzia(duomenys *pradzia) {
	duomenys *naujasAdr = irasas();
	if(pradzia != NULL) {
		pradzia->pries = naujasAdr;
		naujasAdr->po = pradzia;
	}
	
	return naujasAdr;
}

/*pridedama i gala*/
duomenys *pridetiigala(duomenys *pradzia) {
	duomenys *returnPtr = pradzia;
	duomenys *naujasAdr = NULL;
	
	if(pradzia == NULL) {
		naujasAdr = pridetiipradzia(pradzia);
		returnPtr = naujasAdr;
	} else {
		duomenys *kintamas = pradzia;
		while (kintamas->po != NULL) {
			kintamas = kintamas->po;
		}
		naujasAdr = irasas();
		kintamas->po = naujasAdr;
		naujasAdr->po = NULL;
		naujasAdr->pries = kintamas;
	}
	return returnPtr;
}

/*pridedama i saraso viduri*/
duomenys *iterpti(duomenys *pradziaPtr) {
	printf("Įterpti naują adresatą po adresato:\n");
    printf("Įrašyti elektroninį paštą:");
	char input[25];
	fgets(input, 24, stdin);
	
	duomenys *sekantisAdr = pradziaPtr;
	duomenys *naujasAdr = NULL;
	
	if(strncmp(input, sekantisAdr->pastas, strlen(sekantisAdr->pastas)) == 0) {
		naujasAdr = irasas();
	} else {
		while(sekantisAdr->po != NULL) {
			sekantisAdr = sekantisAdr->po;
			if(strncmp(input, sekantisAdr->pastas, strlen(sekantisAdr->pastas)) == 0) {
				naujasAdr = irasas();
				break;
			}
		}
	}
	
	if(naujasAdr != NULL) {
		naujasAdr->po = sekantisAdr->po;
		if(naujasAdr->po != NULL) {
			naujasAdr->po->pries = naujasAdr;
		}
		sekantisAdr->po = naujasAdr;
		naujasAdr->pries = sekantisAdr;
	} else {
		printf("adresatas nerastas\n");
	}
	
	return pradziaPtr;
}

void isvedimas(duomenys *pradzia) {
    int count = 0;
	duomenys *dabartinisAdr = pradzia;
    if (dabartinisAdr == NULL){
        printf("Adresų knygutė tusčia\n");
    }else{
	    while(dabartinisAdr != NULL) {
            count++;
		    printf("Eil.Nr.: %d Adresatas: %s %s Tel.Nr.: %s El.Paštas:%s\n",
                count,
			    dabartinisAdr->vardas,
                dabartinisAdr->pavarde,
                dabartinisAdr->tele,
                dabartinisAdr->pastas);
		    dabartinisAdr = dabartinisAdr->po;
		
	    }	
    }
}

void paieska(duomenys *pradzia){
	char command[16];
	int count = 0;
	int input;
	char innput[16];
	duomenys *dabartinisAdr = pradzia;
	printf("Ieškoti pagal skaičių įrašykite 'skaicius', įrašykite 'duomenys' \n");
	fgets(innput,15,stdin);
	sscanf(innput,"%s",command);
	if (strncmp(command, "skaicius", 9) == 0){

		printf("Kelintą įrašą norite surasti:");
		scanf("%d", &input);
		while(dabartinisAdr != NULL) {
			count++;

			if(input == count){
				printf("Eil.Nr.: %d Adresatas: %s %s Tel.Nr.: %s El.Paštas:%s\n",
                	count,
			    	dabartinisAdr->vardas,
                	dabartinisAdr->pavarde,
                	dabartinisAdr->tele,
                	dabartinisAdr->pastas);
		    	dabartinisAdr = dabartinisAdr->po;
				break;
			}else{
			printf("Adresatas nerastas\n");		
			}
		}
	} else if(strncmp(command, "duomenys", 9) == 0){
		printf("įrašykite vardą, pavardę, tel.nr arba elektroninį paštą \n");
		char info[20];
    	fgets(info,19,stdin);
			while(dabartinisAdr != NULL) {
				count++;
				if(strncmp(info,dabartinisAdr->vardas,strlen(dabartinisAdr->vardas))==0){
					printf("Eil.Nr.: %d Adresatas: %s %s Tel.Nr.: %s El.Paštas:%s\n",
                		count,
			    		dabartinisAdr->vardas,
                		dabartinisAdr->pavarde,
                		dabartinisAdr->tele,
                		dabartinisAdr->pastas);
		    			dabartinisAdr= dabartinisAdr->po;
					break;
				}else if(strncmp(info,dabartinisAdr->pavarde,strlen(dabartinisAdr->pavarde))==0){
					printf("Eil.Nr.: %d Adresatas: %s %s Tel.Nr.: %s El.Paštas:%s\n",
                		count,
			    		dabartinisAdr->vardas,
                		dabartinisAdr->pavarde,
                		dabartinisAdr->tele,
                		dabartinisAdr->pastas);
		    			dabartinisAdr = dabartinisAdr->po;
					break;
				}else if(strncmp(info,dabartinisAdr->tele,strlen(dabartinisAdr->tele))==0){
					printf("Eil.Nr.: %d Adresatas: %s %s Tel.Nr.: %s El.Paštas:%s\n",
                		count,
			    		dabartinisAdr->vardas,
                		dabartinisAdr->pavarde,
                		dabartinisAdr->tele,
                		dabartinisAdr->pastas);
		    			dabartinisAdr = dabartinisAdr->po;
					break;
				}else if(strncmp(info,dabartinisAdr->pastas,strlen(dabartinisAdr->pastas))==0){
					printf("Eil.Nr.: %d Adresatas: %s %s Tel.Nr.: %s El.Paštas:%s\n",
                		count,
			    		dabartinisAdr->vardas,
                		dabartinisAdr->pavarde,
                		dabartinisAdr->tele,
                		dabartinisAdr->pastas);
		    			dabartinisAdr = dabartinisAdr->po;
					break;
				}else{
					printf("Adresatas nerastas\n");
				}
			break;
			}		
	}
}

/*Istrinti pasirinktus*/
duomenys *Delete(duomenys *pradzia) {

	printf("Kelintą įrašą norite ištrinti:");
    int numeris = 0;
	int input;
	scanf("%d", &input);
	
	duomenys *trinamasAdr = pradzia;
	duomenys *adrtodelete = NULL;
	    while(trinamasAdr != NULL) {
		numeris++;	    
		if(input == numeris){
			adrtodelete = trinamasAdr;
			break;
		} else{
			printf("Adresatas nerastas\n");
			break;
		}

		trinamasAdr = trinamasAdr->po;
	}
	
	if(pradzia != NULL && adrtodelete == pradzia) {
		if(adrtodelete->po != NULL) {
			adrtodelete->po->pries = NULL;
			pradzia = adrtodelete->po;
		} else {
			pradzia = NULL;
		}
	} else {
		if(adrtodelete != NULL) {
			if(adrtodelete->pries != NULL) {
				adrtodelete->pries->po = adrtodelete->po;
			}
			
			if(adrtodelete->po != NULL) {
				adrtodelete->po->pries = adrtodelete->po;
			}
		}
	}
	
	if(adrtodelete != NULL) {
		adrtodelete = NULL;
		free(adrtodelete);
	}

	numeris = 0;
	return pradzia;
    
	
}

/* Istrinti viska */
void DeleteAll(struct S_duomenys *pradzia){

    struct S_duomenys *naikinamasAdr = pradzia;
    while(naikinamasAdr != NULL) {

		pradzia = pradzia->po;
		free(naikinamasAdr);
		naikinamasAdr= pradzia;

	}
}

/* malloc atlaisvinimas*/
void MemFree(duomenys *pradzia) {
	
	duomenys *freeMe = pradzia;
	duomenys *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = freeMe->po;
		free(freeMe);
		freeMe = holdMe;
	}	
}

/*
duomenys* load_addresses(duomenys *pradzia)
{	FILE*file =fopen("adresine.txt","r");
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        duomenys *naujasAdr = NULL;
        if(strcmp(line, "\n") == 0) {
            exit(1);
        }
		duomenys *returnPtr = pradzia;
	
		if(pradzia == NULL) {
			duomenys *naujasAdr = malloc(sizeof(duomenys));
			if (naujasAdr == NULL){
        	printf("Atminties klaida");
			exit(1);
			}
			fscanf(file,"%s %s %s %s", naujasAdr->vardas, naujasAdr->pavarde, naujasAdr->tele, naujasAdr->pastas);
			 printf("Pridėtas adresatas:\nVardas: %s\nPavardė: %s\nTel.Nr: %s\nElektroninis paštas: %s\n",
         		naujasAdr->vardas, 
         		naujasAdr->pavarde, 
         		naujasAdr->tele, 
         		naujasAdr->pastas);
		if(pradzia != NULL) {
			pradzia->pries = naujasAdr;
			naujasAdr->po = pradzia;
		}
		return naujasAdr;
		returnPtr = naujasAdr;
		} else {
			duomenys *kintamas = pradzia;
			while (kintamas->po != NULL) {
				kintamas = kintamas->po;
			}
			duomenys *naujasAdr = malloc(sizeof(duomenys));
			if (naujasAdr == NULL){
        	printf("Atminties klaida");
			exit(1);
			}
			fscanf(file,"%s %s %s %s", naujasAdr->vardas, naujasAdr->pavarde, naujasAdr->tele, naujasAdr->pastas);
			printf("Pridėtas adresatas:\nVardas: %s\nPavardė: %s\nTel.Nr: %s\nElektroninis paštas: %s\n",
         		naujasAdr->vardas, 
         		naujasAdr->pavarde, 
         		naujasAdr->tele, 
         		naujasAdr->pastas);
			return naujasAdr;
			kintamas->po = naujasAdr;
			naujasAdr->po = NULL;
			naujasAdr->pries = kintamas;
		}
		return returnPtr;

    }
	fclose(file);
}
*/

/* MAIN */
int main(){
    printf("\n\n **Programos pradžia** \n\n");
	duomenys *pradzia = NULL;
	char command[16];
	char input[16];	
	
	//load_addresses(pradzia);
	isvedimas(pradzia); 
	
	while( fgets( input, 15, stdin) ) {
		
		sscanf(input,"%s",command);	
		
		if ( strncmp(command, "Baigti", 7) == 0) {
			printf("\n\n----Programa baigta----\n");
			break;		
		} else if ( strncmp(command, "Prideti", 8) == 0) {
           pradzia=pridetiigala(pradzia);
        } else if ( strncmp(command, "Spausdinti", 11) == 0) {
            isvedimas(pradzia);
        }else if ( strncmp(command, "Iterpti", 8) == 0) {
            if(pradzia == NULL) {
				pradzia = pridetiipradzia(pradzia);
			} else {
				pradzia = iterpti(pradzia);
			}
        }else if ( strncmp(command, "Trinti", 7) == 0) {
            Delete(pradzia);
            isvedimas(pradzia);
        }else if ( strncmp(command, "Naikinti", 7) == 0) {
            DeleteAll(pradzia);
            isvedimas(pradzia);
        } else if ( strncmp(command, "Ieskoti", 8) == 0) {
            paieska(pradzia);
		}
    }
    MemFree(pradzia);
    return 0;
}