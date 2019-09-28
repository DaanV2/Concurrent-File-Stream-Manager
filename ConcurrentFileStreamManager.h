#pragma once
#ifndef DaanV2_Concurrent_ConcurrentFileStreamManager_Class_Included
#define DaanV2_Concurrent_ConcurrentFileStreamManager_Class_Included

#include "stdafx.h"
#include "DriveManager.h"

using namespace System;
using namespace System::Collections::Concurrent;

namespace DaanV2 {
	namespace Concurrent {
		//DOLATER class description of ConcurrentFileStreamManager
		public ref class ConcurrentFileStreamManager {
		private:
			ConcurrentDictionary<String^, DriveManager^>^ _Drives;
			System::Func<String^, DriveManager^>^ _CreateNew;

			inline DriveManager^ Get(String^ Filepath);
			DriveManager^ Create(String^ Key);

		public:
			//Creates a new instance of ConcurrentFileStreamManager
			ConcurrentFileStreamManager();

			FileStream^ Open(String^ Filepath);

			void Close(FileStream^ Stream);
		};
	}
}

#endif // !DaanV2.Concurrent_ConcurrentFileStreamManager_Class_Included