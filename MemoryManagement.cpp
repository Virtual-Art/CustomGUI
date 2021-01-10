#include "MemoryManagement.h"


//Check if heap has reached it's limit
template<typename _Type>
string MemoryManagment<_Type>::Megabytes(int Bytes)
{
	//BMP = Bytes Per Megabytes (1 Million)
	double BPM = 1000000;
	double Megabytes = Bytes / BPM;

	string s = to_string(Megabytes);
	s = +"MB";
	return s;
}

template<typename _Type>
string MemoryManagment<_Type>::Kilobytes(int Bytes)
{
	//BMP = Bytes Per Megabytes (1 Million)
	double BPM = 1000;
	double Megabytes = Bytes / BPM;

	string s = to_string(Megabytes);
	s = +"KB";
	return s;
}

template<typename _Type>
_Type* MemoryManagment<_Type>::MakeContainer(int Amount)
{
	_Type* Object = new _Type[Amount];
	_Type* ContainerStop = Object + Amount;
	return Object;
}
