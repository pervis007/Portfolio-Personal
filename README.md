Project 1: Port Scanner
Description:
Port Scanner is a C++ program designed to scan a range of ports on a given host to determine which ports are open and their status. It provides a simple command-line interface for specifying the host to scan and analyzing the results.

Features:
Scans a range of ports on a specified host.
Determines whether each port is open or closed.
Provides information on open ports and their status.
How to Use:
Clone the repository to your local machine.
Compile the source code using a C++ compiler (e.g., g++).
Copy code
g++ port_scanner.cpp -o port_scanner
Run the compiled executable with the hostname or IP address as a command-line argument.
bash
Copy code
./port_scanner <hostname>
Replace <hostname> with the hostname or IP address of the target host.
Example Usage:
bash
Copy code
./port_scanner example.com
Sample Output:
kotlin
Copy code
Scanning ports on example.com...

Port 80 is open
Port 443 is open
Port 8080 is closed



Project 2: Desktop File Deleter
Description:
Desktop File Deleter is a C++ program designed to delete all files from the desktop directory except those related to video games. It recursively traverses the desktop directory, identifies video game files based on their extensions, and deletes all other files.

Features:
Deletes all files from the desktop directory except video game files.
Supports recursive traversal of subdirectories.
Provides configurable list of video game file extensions.
How to Use:
Clone the repository to your local machine.
Compile the source code using a C++ compiler (e.g., g++).
Copy code
g++ desktop_file_deleter.cpp -o desktop_file_deleter
Run the compiled executable.
bash
Copy code
./desktop_file_deleter
Note:
Ensure that you have proper authorization before running the program, as it will permanently delete files from the desktop directory.

Disclaimer:
Use this program responsibly and at your own risk. The author is not responsible for any data loss or damage caused by the misuse of this software.
