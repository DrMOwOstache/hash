#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	iter = 0;
	while (valid() && (map.listOfElem[iter].first == NULL_TVALUE || map.listOfElem[iter].second == NULL_TVALUE))
		iter++;
}


void MapIterator::first() {
	iter = 0;
	while (valid() && (map.listOfElem[iter].first == NULL_TVALUE || map.listOfElem[iter].second == NULL_TVALUE))
		iter++;
}


void MapIterator::next() {
	if (valid())
	{
		iter++;
		while (valid() && (map.listOfElem[iter].first == NULL_TVALUE || map.listOfElem[iter].second == NULL_TVALUE))
			iter++;
	}
	else
		throw exception();
}


TElem MapIterator::getCurrent(){
	if (valid())
		return map.listOfElem[iter];
	else
		throw exception();
}


bool MapIterator::valid() const {
	if (iter < map.capacity)
		return true;
	return false;
}



