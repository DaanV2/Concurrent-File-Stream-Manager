#pragma once
#ifndef DaanV2_Concurrent_FileStream_Class_Included
#define DaanV2_Concurrent_FileStream_Class_Included

#include "stdafx.h"

using namespace System;
using namespace System::IO;
using namespace System::Threading;

namespace DaanV2 {
	namespace Concurrent {
		//DOLATER class description of FileStream
		public ref class FileStream : public Stream {
		private:
			Stream^ _baseStream;
			String^ _Filepath;
			EventWaitHandle^ _waitHandle;
			Int64 _Need;

		public:
			//Creates a new instance of FileStream
			FileStream(Stream ^ stream, String ^ Filepath);

			//Creates a new instance of FileStream
			FileStream(String^ Filepath, FileMode& Mode);

			//Creates a new instance of FileStream
			FileStream(String^ Filepath, FileAccess& Access);

			//Creates a new instance of FileStream
			FileStream(String ^ Filepath, FileMode & Mode, FileAccess & Access);

			void Lock();

			void Unlock();

			inline void IncreaseNeed();

			inline void DecreaseNeed();

			property Int64 Need {
				Int64 get() { return this->_Need; }
			}

			property String^ Filepath {
				String^ get() { return this->_Filepath; }
			}

			// Inherited via Stream
#pragma region Abstract stream
#pragma region Properties

			virtual property bool CanRead {
				 bool get() override { return this->_baseStream->CanRead; }
			}

			virtual property bool CanSeek {
				bool get() override { return this->_baseStream->CanSeek;  }
			}

			virtual property bool CanWrite {
				bool get() override { return this->_baseStream->CanWrite; }
			}

			virtual property long long Length {
				long long get() override { return this->_baseStream->Length;  }
			}

			virtual property long long Position {
				long long get() override { return this->_baseStream->Position; }
				void set(long long value) override { this->_baseStream->Position = value; }
			}
#pragma endregion

#pragma region Methods

			virtual void Flush() override;

			virtual long long Seek(long long offset, System::IO::SeekOrigin origin) override;

			virtual void SetLength(long long value) override;

			virtual int Read(array<unsigned char, 1>^ buffer, int offset, int count) override;

			virtual void Write(array<unsigned char, 1>^ buffer, int offset, int count) override;

#pragma endregion
#pragma endregion
		};
	}
}

#endif // !DaanV2.Concurrent_FileStream_Class_Included