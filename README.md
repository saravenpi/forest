# 🌳 Forest, the simple C socket server library
## About
Wave is a simple C socket server library.

## How to use it ?

### Prerequisites
- First you need to compile the library and add the `libforest.so` file in your codebase.
- After that copy the `forest.h` header file in your project.

Now the wave library is ready to be used!

### Example server implementation

Here is an example implementation using the wave library:
```c
#include "forest.h"

#define PORT 8083

int main(int argc, char *argv[])
{
    server_t *server = init_server(PORT);

    set_message_handler(server, default_handler);
    set_default_end_of_message(server, "\r\n");
    start_server(server);
    return 0;
}```

You can compile your webserver with:
```bash
gcc main.c -I. -lforest -L. -Wl,-rpath,.
```

🎉 And your server now ready to go !
