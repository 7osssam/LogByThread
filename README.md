
# LogByThread Library

## Overview

`LogByThread` is a multi-threaded logging system implemented in C++ using the Qt framework. The project features asynchronous log handling, custom log message formatting, and thread-safe operations. The logging system consists of two main components: `Logger` and `LogWorker`.

## Folder Structure

```
LogByThread
│
├── build                  # Build directory
│   └── demo
│
├── demo                   # Demo application
│   ├── CMakeLists.txt
│   └── main.cpp
│
├── include                # Library source files
│   ├── CMakeLists.txt
│   ├── logger.cpp
│   ├── logger.h
│   ├── logworker.cpp
│   └── logworker.h
│
└── CMakeLists.txt         # Root CMake configuration file

```

## Dependencies

- Qt (Core, Concurrent)
- CMake (version 3.14 or higher)

### Build Instructions

1. **Clone the Repository:**

   ```sh
   git clone https://github.com/7osssam/LogByThread.git
   cd LogByThread
   ```

2. **Create Build Directory:**

   ```sh
   mkdir build
   cd build
   ```

3. **Run CMake:**

   ```sh
   cmake ..
   ```

4. **Build the Project:**

   ```sh
   cmake --build .
   ```

## Usage

After building the project, an executable named `demo` will be created in the `build/demo` directory. You can run this executable to see the logging system in action.

### Running the Demo

```sh
./demo/demo
```

## Library Overview

### Logger

The `Logger` class handles the main logging functionality. It provides methods to start and suspend logging, set the log flush size, and customize log message output.

**Key Methods:**

- `startLogging()`:
	- Starts the logging process.
- `suspendLogging()`:
	- Suspends the logging process.
- `setLogFlushSize(quint64 size)`:
	- Sets the size of the log flush.
- `myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)`:
	- Custom message handler for Qt logging.

### LogWorker

The `LogWorker` class handles writing log messages to a file. It runs in a separate thread and ensures thread-safe file operations.

**Key Slots:**

- `onWriteLog(const QString &logStr)`:
	- Slot to write a log string to the log file.
- `onSetLogFlushSize(quint64 size)`:
	- Slot to set the log flush size.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

## License

This library is licensed under the MIT License. Feel free to use it in your projects.
