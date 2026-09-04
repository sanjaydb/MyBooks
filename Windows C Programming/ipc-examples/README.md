# Windows IPC Examples in C

Ten small examples of Windows inter-process communication and synchronization.

| Program | Purpose |
| --- | --- |
| `named_pipe_server.c` | Receive a message through a named pipe. |
| `named_pipe_client.c` | Send a message through a named pipe. |
| `shared_memory_writer.c` | Publish text through a named file mapping. |
| `shared_memory_reader.c` | Read text from the shared mapping. |
| `mailslot_receiver.c` | Receive a local mailslot message. |
| `mailslot_sender.c` | Send a local mailslot message. |
| `anonymous_pipe.c` | Capture a child process's output through an anonymous pipe. |
| `mutex_demo.c` | Coordinate two processes with a named mutex. |
| `semaphore_demo.c` | Limit concurrent worker threads with a semaphore. |
| `event_demo.c` | Signal a waiting thread with an event object. |

## Build

From a Developer Command Prompt for Visual Studio:

```bat
cl /W4 named_pipe_server.c
cl /W4 named_pipe_client.c
cl /W4 shared_memory_writer.c
```

For paired examples, start the server, receiver, or writer first in one terminal, then start its matching program in another. All named objects use the local session and the examples exchange only short text messages.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
