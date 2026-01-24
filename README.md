*This project has been created as part of the 42 curriculum by moatieh*

# minitalk

## Description

minitalk is a client-server communication program that transmits strings using only UNIX signals. The project demonstrates inter-process communication (IPC) using signals to send data bit by bit.

The project includes:
- **server**: Receives and displays messages sent by clients, displays its PID on startup
- **client**: Sends strings to the server using the server's PID

Available signals:
- `SIGUSR1`: represents bit 0
- `SIGUSR2`: represents bit 1

This implementation uses a **bit-by-bit transmission algorithm** where each character is broken down into 8 bits and sent sequentially using UNIX signals. The server reconstructs the character from the received bits and displays the complete message.

**Communication Flow:** Client sends each character as 8 bits (MSB first) → Server receives bits and reconstructs characters → Server acknowledges each bit with SIGUSR1

## Instructions

### Compilation
```bash
make        # creates both server and client
```

### Usage
```bash
# Terminal 1 - Start the server
./server
# Output: Server PID: 12345

# Terminal 2 - Send a message
./client 12345 "Hello, World!"
# Server displays: Hello, World!
```

### Example
```bash
./server
Server PID: 54321

# In another terminal:
./client 54321 "42 Network"
# Server terminal will display: 42 Network
```

## How It Works

1. **Server startup**: Displays its Process ID (PID) and waits for signals
2. **Client transmission**: 
   - Takes server PID and message as arguments
   - Converts each character to binary (8 bits)
   - Sends each bit using SIGUSR1 (0) or SIGUSR2 (1)
   - Waits for acknowledgment before sending next bit
3. **Server reception**:
   - Receives signals and reconstructs bits into characters
   - Sends acknowledgment (SIGUSR1) after each bit
   - Displays complete message when null terminator is received

## Features

- **Signal-based communication** using SIGUSR1 and SIGUSR2
- **Acknowledgment system** ensures reliable bit transmission
- **Bit-by-bit encoding** transmits data at the binary level
- **Synchronous transmission** with blocking until acknowledgment received
- **Handles multiple messages** server runs continuously

## Resources

**Signals & IPC:**
- [Signal Handling - Wikipedia](https://en.wikipedia.org/wiki/Signal_(IPC))
- [UNIX Signal Programming Guide](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)
- [sigaction man page](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [Bitwise Operations Tutorial](https://en.wikipedia.org/wiki/Bitwise_operation)