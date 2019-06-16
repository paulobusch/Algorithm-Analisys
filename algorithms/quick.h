#ifndef QUICKA_H
#define QUICKA_H

//====== DEPEND�NCIAS =======

//======= PROT�TIPOS ========
void quickSort(int values[], int began, int end);

//===== IMPLEMENTA��O =======
void quickSort(int values[], int began, int end){
	int i, j, pivo, aux;
	i = began;
	j = end-1;
	pivo = values[(began + end) / 2];
	while(i <= j)
	{
		while(values[i] < pivo && i < end)
		{
			i++;
		}
		while(values[j] > pivo && j > began)
		{
			j--;
		}
		if(i <= j)
		{
			aux = values[i];
			values[i] = values[j];
			values[j] = aux;
			i++;
			j--;
		}
	}
	if(j > began)
		quickSort(values, began, j+1);
	if(i < end)
		quickSort(values, i, end);
}

#endif