//#include "Container.h"
//
//struct ThisContainer
//{
//};
//
//template<typename _Type>
//Container<_Type>::Container(int Amount)
//{
//	this->StartOfContainer = new _Type[Amount];
//	this->EndOfContainer = StartOfContainer + Amount;
//	this->ContainerPointer = StartOfContainer;
//	this->ContainerAmount = Amount;
//    this->SizeOfContainer = (uint8_t*)EndOfContainer - (uint8_t*)StartOfContainer;
//}
//
//
//template<typename _Type>
//GLsizeiptr Container<_Type>::CurrentSize()
//{
//	return (uint8_t*)ContainerPointer - (uint8_t*)StartOfContainer;
//}
//
//template<typename _Type>
//_Type* Container<_Type>::MakeContainer(int Amount)
//{
//	_Type* Container = new _Type[Amount];
//	return Container;
//}
//
//
//template<typename _Type>
//void Container<_Type>::DeleteContainer()
//{
//	delete[] this->StarOfContainer;
//}
//
//
