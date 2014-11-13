#ifndef __opTS_H__
#define __opTS_H__


#define MAX_TS 1000

#define ETQ_ENT		0
#define ETQ_SAL		1
#define ETQ_ELSE	2


// Funciones para operar con la TS

void introTS(stEntrada entrada, tEntrada tipoTS);
tDato buscaTS(char *id, int *pos);
void impTipo(tDato tipo);
void sacarTS(void);
void buscarPROC(char *identif, int *posIni, int *numParam);
unsigned char buscarPARAM(tDato tipo);
char *buscarEtqTS(unsigned char tipo);
int sacarCtrlTS(void);

#endif
