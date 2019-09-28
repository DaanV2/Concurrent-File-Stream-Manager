#pragma once
#ifndef DaanV2_Concurrent_DriveManager_Class_Included
#define DaanV2_Concurrent_DriveManager_Class_Included

#include "stdafx.h"
#include "FileStream.h"

using namespace System;
using namespace System::Collections::Generic;

namespace DaanV2 {
	namespace Concurrent {
		//DOLATER class description of DriveManager
		public ref class DriveManager {
		private:
			Dictionary<String^, FileStream^>^ _Files;
			EventWaitHandle^ _waitHandle;

		public:
			//Creates a new instance of DriveManager
			DriveManager();

			FileStream^ Open(String^ Filepath);

			inline FileStream^ Open(String^ Filepath, FileMode Mode, FileAccess Access);

			void Close(FileStream^ Stream);

			inline void Lock();

			inline void Unlock();
		};
	}
}

#endif // !DaanV2.Concurrent_DriveManager_Class_Included