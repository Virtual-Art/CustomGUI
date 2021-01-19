#ifndef CONTAINER
#define CONTAINER

#include <iostream>
#include <memory>

using namespace std;

template <typename _Type>
class Container
{
public:

	_Type* StartOfContainer;
	_Type* UsagePointer;
	_Type* SourcePointer;
	_Type* DestinationPointer;
	_Type* EndOfContainer;
	_Type* BookMark;
	_Type* SpacePointer;
	//_Type ContainerDefault;
	GLsizeiptr MaxSize;
	GLsizeiptr CurrentSize;
	float StorageUse;
	int MaxContainerAmount;
	int CurrentContainerAmount;
	int SpaceSize;

	//Container()
	//{
	//	ContainerAmount = 0;
	//	StartOfContainer = 0;
	//	ContainerPointer = 0;
	//	EndOfContainer = 0;
	//	BookMark = 0;
	//	StorageUse = 0.0;
	//	CurrentContainerAmount = 0;
	//	this->CurrentSize = (uint8_t*)ContainerPointer - (uint8_t*)StartOfContainer;
	//
	//
	//}

	Container() { MaxContainerAmount = 5000; };

	Container(int Amount) //const _Type& Default
		:StartOfContainer(new _Type[Amount]), UsagePointer(StartOfContainer), EndOfContainer(StartOfContainer + Amount)
	{
		MaxContainerAmount = Amount;
		this->MaxSize = (uint8_t*)EndOfContainer - (uint8_t*)StartOfContainer;
		this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
		BookMark = 0;
		StorageUse = ((CurrentSize / MaxSize) * 100.0);
		CurrentContainerAmount = 0;
		DestinationPointer = 0;
		SourcePointer = 0;
		SpacePointer = UsagePointer;
		SpaceSize = Amount;
		//ContainerDefault = Default;
	}

	void SetCurrentSize()
	{
		this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
	}
	void SetStorageUsage()
	{
		this->StorageUse = (100.0 *((float)CurrentSize / (float)MaxSize));
	}


	void SpaceRefreshINC(const int& Increase)
	{
		if((SpacePointer + Increase) < EndOfContainer)
		{
			this->SpacePointer += Increase;
		}
		if((SpacePointer + Increase) >= EndOfContainer)
		{
		    this->SpacePointer = EndOfContainer - 1;
		}
	}

	void StatsRefreshINC(const int& Increase)
	{
		if ((UsagePointer + Increase) < EndOfContainer)
		{
			this->UsagePointer += Increase;
			this->CurrentContainerAmount += Increase;
			this->SpaceSize -= Increase;
		}
		if ((UsagePointer + Increase) >= EndOfContainer)
		{
			this->UsagePointer = EndOfContainer - 1;
			this->CurrentContainerAmount = MaxContainerAmount;
			this->SpaceSize = 0;
		}
		this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
		this->StorageUse = (((float)CurrentSize / (float)MaxSize));
	}

	void SpaceRefreshDIC(const int& Decrease)
	{
		if ((SpacePointer - Decrease) > StartOfContainer)
		{
			this->SpacePointer -= Decrease;
		}
		if((SpacePointer - Decrease) >= StartOfContainer)
		{
			SpacePointer = StartOfContainer;
		}
	}

	void StatsRefreshDIC(const int& Decrease)
	{
		if ((UsagePointer - Decrease) > StartOfContainer)
		{
			this->UsagePointer -= Decrease;
			this->CurrentContainerAmount -= Decrease;
			this->SpaceSize += Decrease;
		}
		if((UsagePointer - Decrease) <= StartOfContainer)
		{
			this->UsagePointer = StartOfContainer;
			this->CurrentContainerAmount = 0;
			this->SpaceSize = MaxContainerAmount;
		}
		this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
		this->StorageUse = (((float)CurrentSize / (float)MaxSize));

	}
	//Put Negative if strip size is smaller
	void RefreshContainer(const int& DataIncreaseDecrease)
	{
	    //if the if it's in bound
		if ((UsagePointer + DataIncreaseDecrease) < EndOfContainer && (UsagePointer + DataIncreaseDecrease) > StartOfContainer)
		{
		this->UsagePointer += DataIncreaseDecrease;
		this->SpacePointer += DataIncreaseDecrease;
		this->CurrentContainerAmount += DataIncreaseDecrease;
		this->SpaceSize -= DataIncreaseDecrease;
		this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
		this->StorageUse = (((float)CurrentSize / (float)MaxSize));
		}
		else
		{   //if it's over bounds
	        if ((UsagePointer + DataIncreaseDecrease) >= EndOfContainer)
			{
				int CalcIncrement = (EndOfContainer - UsagePointer);

				this->UsagePointer += CalcIncrement;
				this->SpacePointer += CalcIncrement;
				this->CurrentContainerAmount += CalcIncrement;
				this->SpaceSize -= CalcIncrement;
				this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
				this->StorageUse = (((float)CurrentSize / (float)MaxSize));
			
			}
	
		}

		
	}
	
	void RefreshContainerDIC(const int& Decrease)
	{
		if ((UsagePointer - Decrease) > StartOfContainer)
		{
			if (SpacePointer > StartOfContainer)
			{
				this->SpacePointer -= Decrease;
			}
			if (UsagePointer > StartOfContainer)
			{
				this->UsagePointer -= Decrease;
				this->CurrentContainerAmount -= Decrease;
				this->SpaceSize += Decrease;
			}
			this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
			this->StorageUse = (((float)CurrentSize / (float)MaxSize));
		}
		else
		{
			//if it's under bounds
			if ((UsagePointer - Decrease) <= StartOfContainer)
			{
				this->UsagePointer = StartOfContainer;
				this->SpacePointer = StartOfContainer;
				this->CurrentContainerAmount = 0;
				this->SpaceSize = MaxContainerAmount;
				this->CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)StartOfContainer;
				this->StorageUse = (((float)CurrentSize / (float)MaxSize));
			}
		}
	}


	void ManualContainerDelete()
	{
		delete[] StartOfContainer;
		UsagePointer = 0;
		StartOfContainer = 0;
		MaxContainerAmount = 0;
		BookMark = 0;
	}


	


	//Sets a book mark and sets it to the beginning
	//sets a book mark too




	
	//////////////////////////////Public Usage Functions/////////////////////////////////////////////



	//Save this function
	//Replace 1 pice of data with given data






	//Array of Elements being copied into entire strip
	//NewDataArray needs to have the same amount of data as AmountOfObjects
	void DynamicDataStrip(int ObjectID, int AmountOfObjects, _Type* NewDataArray)
	{
		for (int i = 0; i < AmountOfObjects; i++)
		{
			Add(NewDataArray);
			NewDataArray++;
		}
	}






	
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////// | //////////////// | //////////////////////////////////////
	////////////////////////////// |  USER FUNCTIONS  | //////////////////////////////////////
	////////////////////////////// V //////////////// V //////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	//Function List: 
	//  Add,			   ClearStrip
	//  Replace,           MoveStrip,
	//	AddDuplicate,      CopyStrip,
	//	ReplaceDuplicate,  RetreiveData,
	//	InsertStrip,       PrintContainerData,
	//	DeleteStrip,       

	Container* GetAddress(int Spot)
	{
		return StartOfContainer + Spot;
	}

	bool CheckBounds(int RequestedSpot)
	{
		if (RequestedSpot == -1) return false;
		//InBounds
		if (StartOfContainer + RequestedSpot >= StartOfContainer && StartOfContainer + RequestedSpot < EndOfContainer)
		{
			return true;
		}

		//Out Of Bounds
		return false;
	}

	//Add Singular Data to top
	void AddSpecific(unsigned int Spot, const _Type& NewData)
	{
		//User error if the first argument is false
		if (UsagePointer < EndOfContainer)
		{
			CopyToSpot(Spot, NewData);
			return;
		}
		else
		{
			std::cout << "ADDITION ERROR:: Container Limit Reached " << endl;
		}
	}

	void Add(const _Type& NewData)
	{
		//User error if the first argument is false
	
		if (UsagePointer < EndOfContainer)
		{
			CopyToSpace(NewData);
			RefreshContainer(1);
			
			return;
		}
		else
		{
			std::cout << "ADDITION ERROR:: Container Limit Reached " << CurrentContainerAmount << " " << MaxContainerAmount << endl;
		}

	}


	//Replace Singular Data
	void Replace(int Spot, const _Type& NewData)
	{
		//User error if the first argument is false
		if ((StartOfContainer + Spot) < EndOfContainer)
		{
			CopyToSpot(Spot, NewData);
			return;
		}
		else
		{
			std::cout << Spot << " REPLACE ERROR:: Index not within container" << endl;
			std::cout << " REPLACE ERROR:: Index overiding data" << endl;
			return;
		}
	}

	//Add singular data in multiples to the top
	void AddDuplicate(int AmountOfDuplicates, const _Type& Data)
	{
		//User error if the first argument is false
		if ((UsagePointer + AmountOfDuplicates) <= EndOfContainer)
		{

			for (int i = 0; i < AmountOfDuplicates; i++)
			{
				Add(Data);
			}
			return;
		}
		else
		{
			std::cout << "DUPLICATION ERROR:: Size too large " << endl;
			return;
		}
	}

	//Replaces an intire strip with duplicates
	void ReplaceDuplicate(int Spot, int Size, const _Type& NewData)
	{
		for (int i = 0; i < Size; i++)
		{
			CopyNewData(Spot, NewData);
		}
	}

	//void Insert(const _Type& Data, const int& Spot)
	//{
	//	//User error if the first argument is false
	//	if ((UsagePointer + Size) < EndOfContainer)
	//	{
	//		RaiseStrip(Spot, 1, Data);
	//		RefreshContainer(1); //refresh the containern every Element we add
	//		return;
	//	}
	//	else
	//	{
	//		std::cout << "Insertion ERROR::Size too large " << endl;
	//		return;
	//	}
	//}

	

	//Creates An Empty Strip
	void InsertStripNEW(const int& Spot, const int& Size, const _Type& Zero)
	{
		//Throw Error If Out Of Bounds
		if ((UsagePointer + Size - 1) < EndOfContainer)
		{
			//New Spot Is Below Current Position Of Space
			if ((StartOfContainer + Spot) <= SpacePointer)
			{
				//MoveSpace Down
				Raise(SpacePointer, Size, Zero, Spot);  

				//Update Stats
				//StatsRefreshINC(Size);
				RefreshContainer(Size);
		
				return;
			}
			//New Spot Is Above Current Position Of Space
			if((StartOfContainer + Spot) > SpacePointer) 
			{
				//Move Space Up
				Drop(SpacePointer, Size, Zero, Spot + SpaceSize);
				//UpdateStats
				StatsRefreshINC(Size);
				return;
			}	
		}
		else
		{
			std::cout << "Insertion ERROR::Size too large " << endl;
			return;
		}
	}


	void DeleteStripNEW(const int& Spot, const int& Size, const _Type& Zero)
	{
		//cout << "Trying to delete " << endl;
		//User error if the first argument is false
		if ((UsagePointer - Size) >= StartOfContainer)
		{
			//above space pointer              
			if ((StartOfContainer + Spot) > SpacePointer)
			{
				//std::cout << "(" << Size << ") Elements Deleted" << endl;
				Raise((StartOfContainer + SpaceSize + Spot - 1), Size, Zero, ((SpacePointer) - StartOfContainer));
				RefreshContainerDIC(Size);
				return;
			}
			//below space pointer
			if ((StartOfContainer + Spot) < SpacePointer)
			{
				//std::cout << "(" << Size << ") Elements Deleted" << endl;
				Drop((StartOfContainer + Spot), Size, Zero, (SpacePointer - StartOfContainer));
				RefreshContainerDIC(Size);
				return;
			}
		}
		else
		{
			std::cout << "Deletion ERROR::Size too large " << endl;
			return;
		}

		cout << "Not all paths for DeleteStripNew are handled" << endl;
	}

	//Moves an intire strip, input -1 to "NewSpot" to move to the top
	void MoveStrip(int OriginalSpot, unsigned int Size, int NewSpot, const _Type& Zero)
	{
		//User error if the first argument is false
		if((StartOfContainer + OriginalSpot + Size) < EndOfContainer && (StartOfContainer + NewSpot + Size) < EndOfContainer )
		{
			if (NewSpot < 0) //- 1 to just push to the top
			{
				//Setup
				SourcePointer = StartOfContainer + OriginalSpot;
				DestinationPointer = UsagePointer;

				//Move strip
				while (SourcePointer < (StartOfContainer + OriginalSpot + Size))
				{
					*DestinationPointer = *SourcePointer;
					DestinationPointer++;
					SourcePointer++;
				}

				// Delete old strip
				DeleteStrip(OriginalSpot, Size, Zero); 

				//Set Back Pointers
				SourcePointer = 0;
				DestinationPointer = 0;
				return;
			}
			if (NewSpot > 0) //for specific move location
			{
				InsertStrip(NewSpot, Size, Zero); //Make Space for data to move to

				//Setup
				SourcePointer = StartOfContainer + OriginalSpot;
				DestinationPointer = StartOfContainer + NewSpot;

				//MoveData
				//you could also write it as DestinationPointer < StartOfContainer + NewSpot + Size
				while (SourcePointer < (StartOfContainer + OriginalSpot + Size))
				{
					*DestinationPointer = *SourcePointer;
					DestinationPointer++;
					SourcePointer++;
				}
				DeleteStrip(OriginalSpot, Size, Zero); // Delete old strip
				//Set Back Pointers
				SourcePointer = 0;
				DestinationPointer = 0;
			}
		}
		else
		{
			std::cout << "Error is one of the following: " << endl;
			std::cout << "MOVE ERROR:: Spot is not within the container" << endl;
			std::cout << "MOVE ERROR:: NewSpot is not within the container" << endl;
			std::cout << "MOVE ERROR:: Size of Spot or NewSpot is not within the container" << endl;
		}
	
	}

	//Makes a copy of an intire strip, input -1 to "NewSpot" to copy to the top
	void CopyStrip(int Spot, unsigned int Size, int NewSpot, const _Type& Zero)
	{
		//User error if the first argument is false
		if ((StartOfContainer + Spot + Size) < EndOfContainer && (StartOfContainer + NewSpot + Size) < EndOfContainer)
		{
			if (NewSpot < 0) //- 1 to just push to the top
			{
				//Setup
				SourcePointer = StartOfContainer + Spot;
				DestinationPointer = UsagePointer;

				//Copy strip
				while (SourcePointer < (StartOfContainer + Spot + Size))
				{
					*DestinationPointer = *SourcePointer;
					DestinationPointer++;
					SourcePointer++;
				}

				//Set Back Poiunters & Refresh Container Data
				SourcePointer = 0;
				DestinationPointer = 0;
				RefreshContainer(Size);
				return;
			}
			if (NewSpot > 0) //for specific move location
			{
				InsertStrip(NewSpot, Size, Zero); //Make Space for data to move to
				//Setup
				SourcePointer = StartOfContainer + Spot;
				DestinationPointer = StartOfContainer + NewSpot;

				//MoveData
				//you could also write it as DestinationPointer < StartOfContainer + NewSpot + Size
				while (SourcePointer < (StartOfContainer + Spot + Size))
				{
					*DestinationPointer = *SourcePointer;
					DestinationPointer++;
					SourcePointer++;
				}
				//Set Back Pointers
				SourcePointer = 0;
				DestinationPointer = 0;
			}
		}
		else
		{
			std::cout << "Error is one of the following: " << endl;
			std::cout << "MOVE ERROR:: Spot is not within the container" << endl;
			std::cout << "MOVE ERROR:: NewSpot is not within the container" << endl;
			std::cout << "MOVE ERROR:: Size of Spot or NewSpot is not within the container" << endl;
		}

	}

	//Clears an intire strip
	void ClearStrip(int Spot, unsigned int Size, _Type& Zero)
	{
		//Setup
		SourcePointer = StartOfContainer + Spot;

		//Clear the strip
		while (SourcePointer < (StartOfContainer + Spot + Size))
		{
			*SourcePointer = Zero;
			SourcePointer++;
		}
		//Set Back Pointers
		SourcePointer = 0;
	}

	void PrintContainerData()
	{
		std::cout << "" << endl;
		std::cout << "--------Container Info---------" << endl;
		std::cout << "StartOfContainer: " << StartOfContainer << endl;
		std::cout << "ContainerPointer: " << UsagePointer << endl;
		std::cout << "EndOfContainer: " << EndOfContainer << endl;
		std::cout << "Current Container Size: " << CurrentSize << endl;
		std::cout << "Max Container Size: " << MaxSize << endl;
		std::cout << "Current Container Amount: " << CurrentContainerAmount << endl;
		std::cout << "MaxContainerAmount: " << MaxContainerAmount << endl;
		std::cout << "Space: " << SpaceSize << endl;
		std::cout << "Current Storage Usage: " << StorageUse << "%" << endl;
		std::cout << "-------------------------------" << endl;
		std::cout << "" << endl;
	}

	_Type* RetrieveDataP(int Spot)
	{
		//cout << "" << << endl;
		if ((StartOfContainer + Spot) <= EndOfContainer && Spot != -1) 
		{
			SourcePointer = StartOfContainer + Spot;
			_Type* Data = SourcePointer;
			return Data;
		}
		else
		{
			std::cout << "RETREIVE ERROR:: Index is greater than container limit (" << MaxContainerAmount << ")" << "Spot: " << Spot <<  endl;
			return nullptr;
		}
	}

	_Type& RetrieveDataR(int Spot)
	{
		//cout << "" << << endl;
		if ((StartOfContainer + Spot) <= EndOfContainer && Spot != -1)
		{
			SourcePointer = StartOfContainer + Spot;
			return *SourcePointer;
		}
		else
		{
			std::cout << "RETREIVE ERROR:: Index is greater than container limit (" << MaxContainerAmount << ")" << "Spot: " << Spot << endl;
		}
	}

	
/////////////////////////////// | //////////////// | //////////////////////////////////////////
/////////////////////////////// | HELPER FUNCTIONS | //////////////////////////////////////////
/////////////////////////////// V //////////////// V //////////////////////////////////////////

	// NewSpot 2
	//void MoveSpace(int NewSpot, const _Type& Zero)
	//{
	//
	//	if ((StartOfContainer + NewSpot + SpaceSize - 1) < EndOfContainer && (StartOfContainer + NewSpot) >= StartOfContainer)
	//	{
	//		//if the New Spot is above the space
	//		if ((StartOfContainer + NewSpot) > SpacePointer)
	//		{
	//			Drop(SpacePointer , SpaceSize, Zero, NewSpot + SpaceSize);
	//			//Update space pointer
	//			SpacePointer = StartOfContainer + NewSpot;
	//			std::cout << "(" << SpaceSize << ") Spaces Moved to Position: " << SpacePointer - StartOfContainer << endl;
	//		}
	//		if (SpacePointer > (StartOfContainer + NewSpot))
	//		{
	//			std::cout << "SpacePointer Position: " << SpacePointer - StartOfContainer << endl;
	//			//raise, the source from raise stopping at the spot aswell	
	//			Raise((--SpacePointer), SpaceSize, Zero, NewSpot);
	//			//Update space pointer
	//			SpacePointer = StartOfContainer + NewSpot;
	//			std::cout << "(" << SpaceSize << ") Spaces Moved to Position: " << SpacePointer - StartOfContainer << endl;
	//		}
	//	}
	//	else
	//	{
	//		std::cout << "MOVE ERROR:: Can not change Space position - Move, out of bounds" << endl;
	//	}
	//}

	// Helper Function - Deincrements an intire strip by offset(size) "Drop"
	//stop Point is either the SpacePointer or, the spot of insert/delete
	void Drop(_Type* Spot, const unsigned int& Size, const _Type& Zero, const int& StopPoint)
	{
		//Setup
		DestinationPointer = Spot; //StartOfContainer +
		SourcePointer = DestinationPointer + Size; // correct

		if (DestinationPointer != nullptr && SourcePointer != nullptr)
		{
			//Drop
			while (SourcePointer < (StartOfContainer + StopPoint))
			{
				if (SourcePointer + 1 < EndOfContainer)
				{
					*DestinationPointer = *SourcePointer;
					SourcePointer++;
					DestinationPointer++; // ++ for both should be correct
				}
			}
		}
		else
		{
			std::cout << "DROP ERROR:: Pointer is null" << endl;
		}

		//Clears junk over drop
		ClearJunk(DestinationPointer, Size, Zero);

		//Set Back Pointers
		SourcePointer = 0;
		DestinationPointer = 0;
	}

	

	//mostly used for move functions
	//where you want to start raising - Spot
	//how much you are raising - Size
	//Type to clear - Zero
	//where you want to stop raising so that you can clear - Stop Point
	void Raise(_Type* Spot, const unsigned int& Size, const _Type& Zero, const int& StopPoint)
	{
		int Random = 0;

		//Setup
		SourcePointer = Spot; //SpacePointer
		DestinationPointer = SourcePointer + Size; // correct

		if (DestinationPointer != 0 && SourcePointer != 0)
		{
			//Raise
			while (SourcePointer > (StartOfContainer + StopPoint))
			{
				SourcePointer--;
				DestinationPointer--;
				
				*DestinationPointer = *SourcePointer;
				//cout << "Random " << Random++ << endl;
			}
			//Clear Junk under raise
			//SourcePointer++;
			ClearJunk(SourcePointer, Size, Zero);
		}
		else
		{
			std::cout << "RAISE ERROR:: Pointer is null" << endl;
		}

		//Set Back Pointers
		SourcePointer = 0;
		DestinationPointer = 0;
	}

   //Helper Function - same as clear function but takes in spot as a _Type*& for Raise and Drop
	void ClearJunk( _Type*& Spot, int Size, const _Type& Zero)
	{
		SourcePointer = Spot;
		for(int i = 0; i < Size; i++)
		{
			*SourcePointer = Zero;
			SourcePointer++;
		}
		SourcePointer = 0;
	}

	void CopyToSpace(const _Type& Copy)
	{
		if (UsagePointer < EndOfContainer)
		{
			SourcePointer = SpacePointer;
			*SourcePointer = Copy;
			return;
		}
		else
		{
			std::cout << "ERROR:: Container Limit Reached" << endl;
		}
	}

	void CopyToSpot(int Spot, const _Type& Copy)
	{
		if (UsagePointer < EndOfContainer)
		{
			SourcePointer = StartOfContainer + Spot;
			*SourcePointer = Copy;
			SourcePointer = 0;
			return;
		}
		else
		{
			std::cout << "ERROR:: Container Limit Reached" << endl;
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////////
};



#endif
