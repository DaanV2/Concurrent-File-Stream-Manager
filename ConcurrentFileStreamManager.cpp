#include "stdafx.h"
#include "ConcurrentFileStreamManager.h"

namespace DaanV2 {
	namespace Concurrent {
		ConcurrentFileStreamManager::ConcurrentFileStreamManager() {
			this->_Drives = gcnew ConcurrentDictionary<String^, DriveManager^>();
			this->_CreateNew = gcnew Func<String^, DriveManager^>(this->Create);
		}

		inline DriveManager^ ConcurrentFileStreamManager::Get(String^ Filepath) {
			String^ Root = System::IO::Directory::GetDirectoryRoot(Filepath);

			return this->_Drives->GetOrAdd(Root, this->_CreateNew);
		}

		DriveManager^ ConcurrentFileStreamManager::Create(String^ Key) {
			return gcnew DriveManager();
		}

		FileStream^ ConcurrentFileStreamManager::Open(String^ Filepath) {
			DriveManager^ Temp = this->Get(Filepath);
			
			return Temp->Open(Filepath);
		}

		void ConcurrentFileStreamManager::Close(FileStream^ Stream) {
			DriveManager^ Temp = this->Get(Stream->Filepath);

			Temp->Close(Stream);
		}
	}
}