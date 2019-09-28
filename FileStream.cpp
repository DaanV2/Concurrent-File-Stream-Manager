#include "stdafx.h"
#include "FileStream.h"

namespace DaanV2 {
	namespace Concurrent {

		FileStream::FileStream(Stream^ stream, String^ Filepath) : Stream() {
			this->_baseStream = stream;
			this->_waitHandle = gcnew EventWaitHandle(true, EventResetMode::AutoReset);
			this->_Need = 0;
			this->_Filepath = Filepath;
		}

		FileStream::FileStream(String^ Filepath, FileMode& Mode) : 
			FileStream(gcnew FileStream(Filepath, Mode), Filepath) { }

		FileStream::FileStream(String^ Filepath, FileAccess& Access) : 
			FileStream(gcnew FileStream(Filepath, Access), Filepath) { }

		FileStream::FileStream(String^ Filepath, FileMode & Mode, FileAccess & Access) : 
			FileStream(gcnew FileStream(Filepath, Mode, Access), Filepath) { }

		void FileStream::Lock() {
			this->_waitHandle->WaitOne();
		}

		void FileStream::Unlock() {
			this->_waitHandle->Set();
		}

		inline void FileStream::IncreaseNeed() {
			Interlocked::Increment(this->_Need);
		}

		inline void FileStream::DecreaseNeed() {
			Interlocked::Decrement(this->_Need);
		}

		void FileStream::Flush() {
			this->_baseStream->Flush();
		}

		long long FileStream::Seek(long long offset, System::IO::SeekOrigin origin) {
			return this->_baseStream->Seek(offset, origin);
		}

		void FileStream::SetLength(long long value) {
			this->_baseStream->SetLength(value);
		}

		int FileStream::Read(array<unsigned char, 1>^ buffer, int offset, int count) {
			return this->_baseStream->Read(buffer, offset, count);
		}

		void FileStream::Write(array<unsigned char, 1>^ buffer, int offset, int count) {
			this->_baseStream->Write(buffer, offset, count);
		}
	}
}