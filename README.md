# Concurrent File Stream Manager

An API that makes sure your program can only have one stream per file. It makes sure that all threads access the same stream.

## Usage

C++ / CLI

```Cpp
    String ^ Filepath = "C:\\Test\\SomeFile.txt";
    //Creates a new manager
    ConcurrentFileStreamManager ^ Manager = gcnew ConcurrentFileStreamManager();
    //Retrieve concurrent filestream
    FileStream ^ stream = Manager->Open(Filepath);

    //Lock stream
    stream->Lock();

    //Read/Write/Seek or do all kinds of stuff with a stream here

    //Unlock stream
    stream->Unlock();

    //closes the stream and flushes
    Manager->Close(stream);
```

C#

```Csharp
    String Filepath = @"C:\Test\SomeFile.txt";
    //Creates a new manager
    ConcurrentFileStreamManager Manager = new ConcurrentFileStreamManager();
    //Retrieve concurrent filestream
    FileStream stream = Manager.Open(Filepath);

    //Lock stream
    stream.Lock();

    //Unlock stream
    stream.Unlock();

    //closes the stream and flushes
    Manager.Close(stream);
```
