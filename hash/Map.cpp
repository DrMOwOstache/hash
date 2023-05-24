#include "Map.h"
#include "MapIterator.h"

int Map::hashElem(int n, int i) const
{
	if (capacity != 0)
	{
		if (n >= 0)
			return (n + i * i) % capacity;
		return (n * -1 + i * i) % capacity;
	}
	return -1;
}

void Map::resizeList()
{
	if (capacity == 0)
		capacity = 1;
	else
		capacity *= 2;
	TElem* auxList = new TElem[nrElem];
	for (int i = 0; i < nrElem; i++)
		auxList[i] = listOfElem[i];

	listOfElem = new TElem[capacity];
	for(int i=0;i<capacity;i++)
		listOfElem[i].first = NULL_TVALUE, listOfElem[i].second = NULL_TVALUE;

	int auxSize = nrElem;
	nrElem = 0;
	for (int i = 0; i < auxSize; i++)
		add(auxList[i].first, auxList[i].second);

	delete[] auxList;
}

Map::Map() {
	this->nrElem = 0;
	this->capacity = 0;
	this->nrElem = 0;
	this->listOfElem = new TElem[capacity];
}

Map::~Map() {
	if (this->listOfElem != nullptr)
	{
		delete[] this->listOfElem;
	}
}

TValue Map::add(TKey c, TValue v){
	if (capacity == 0)
		resizeList();
	int h = hashElem(c,0);
	for (int i = 1; listOfElem[h].first != c; h = hashElem(h, i), i++)
		if (listOfElem[h].second == NULL_TVALUE || listOfElem[h].first == NULL_TVALUE)
		{
			listOfElem[h].first = c;
			listOfElem[h].second = v;
			nrElem++;
			if(nrElem == capacity)
				resizeList();
			return NULL_TVALUE;
		}
	int aux = listOfElem[h].second;
	listOfElem[h].second = v;
	return aux;
}

TValue Map::search(TKey c) const{
	
	if (capacity != 0)
	{
		for (int i = 1, h = hashElem(c, 0); listOfElem[h].first != NULL_TVALUE; h = hashElem(h, i), i++)
			if (listOfElem[h].first == c)
				return listOfElem[h].second;
	}
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	
	if (capacity != 0)
	{
		for (int i = 1, h = hashElem(c, 0); listOfElem[h].first != NULL_TVALUE; h = hashElem(h, i), i++)
			if (listOfElem[h].first == c)
			{
				nrElem--;
				int aux = listOfElem[h].second;
				listOfElem[h].second = NULL_TVALUE;
				return aux;
			}
	}
	return NULL_TVALUE;
}


int Map::size() const {
	return nrElem;
}

bool Map::isEmpty() const{
	if(listOfElem == nullptr || capacity == 0 || nrElem == 0)
		return true;
	return false;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



