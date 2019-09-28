#include "stdafx.h"
#include "DriveManager.h"

namespace DaanV2 {
	namespace Concurrent {
		DriveManager::DriveManager() {
			this->_Files = gcnew Dictionary<String^, FileStream^>();
			this->_waitHandle = gcnew EventWaitHandle(true, EventResetMode::AutoReset);
		}

		FileStream^ DriveManager::Open(String^ Filepath) {
			return this->Open(Filepath, FileMode::OpenOrCreate, FileAccess::ReadWrite);
		}

		inline FileStream^ DriveManager::Open(String^ Filepath, FileMode Mode, FileAccess Access) {
			FileStream^ Out;

			this->Lock();

			if (this->_Files->ContainsKey(Filepath)) {
				Out = this->_Files[Filepath];
			}
			else {
				Out = gcnew FileStream(Filepath, Mode, Access);
				this->_Files[Filepath] = Out;
			}

			//Increase need and signoff
			Out->IncreaseNeed();
			this->Unlock();

			return Out;
		}

		void DriveManager::Close(FileStream^ Stream) {
			this->Lock();

			Stream->DecreaseNeed();

			//Check if stream can be closed
			if (Stream->Need == 0) {
				Stream->Lock();

				if (Stream->Need == 0) {
					this->_Files->Remove(Stream->Filepath);
					Stream->Flush();
					Stream->Close();
				}

				Stream->Unlock();
			}

			this->Unlock();
		}

		inline void DriveManager::Lock() {
			this->_waitHandle->WaitOne();
		}

		inline void DriveManager::Unlock() {
			this->_waitHandle->Set();
		}
	}
}