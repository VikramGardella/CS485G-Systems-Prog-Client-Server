Author: Vikram Gardella

Course: CS485G

Program Description: A simple server with 4 client applications(incomplete).

Execution: Run the server like so: "./simpled 1024 123" where "1024" is the
port number (must be 1024 or greater because anything lower is reserved)
and the secret key you have decided on is "123". Run the client applications
like so: "./ssSet localhost 1024 123 apple 5" where localhost is the
machine name (can also be an IP address), "1024" is the port number (must
match the server's port to even get an initial connection), "123" is the
pass key (must match the server's key to get access and be able to perform
the desired task), "apple" is the variable, and "5" is the desired value
for that variable.

Technical Problems/Limitations: Splitting a char* and a char array using
spaces as the delimiters has proven most cumbersome and I am finding dealing
with them rather than strings in c++ is more difficult and annoying. The
amount of local variables that can be stored in my 2-Dimensional character
pointer-pointer array deal is limited to 64 but that can be easily
increased, although the whole "set" and "get" don't function properly.
