# C-Containers

```text
 $$$$$$\         $$$$$$\                       $$\               $$\                                         
$$  __$$\       $$  __$$\                      $$ |              \__|                                        
$$ /  \__|      $$ /  \__| $$$$$$\  $$$$$$$\ $$$$$$\    $$$$$$\  $$\ $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$$\
$$ |            $$ |      $$  __$$\ $$  __$$\\_$$  _|   \____$$\ $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  _____|
$$ |            $$ |      $$ /  $$ |$$ |  $$ | $$ |     $$$$$$$ |$$ |$$ |  $$ |$$$$$$$$ |$$ |  \__|\$$$$$$\ 
$$ |  $$\       $$ |  $$\ $$ |  $$ |$$ |  $$ | $$ |$$\ $$  __$$ |$$ |$$ |  $$ |$$   ____|$$ |       \____$$\
\$$$$$$  |      \$$$$$$  |\$$$$$$  |$$ |  $$ | \$$$$  |\$$$$$$$ |$$ |$$ |  $$ |\$$$$$$$\ $$ |      $$$$$$$  |
 \______/        \______/  \______/ \__|  \__|  \____/  \_______|\__|\__|  \__| \_______|\__|      \_______/
```

A collection of container data structures written in C.

The project started as a way to better understand how common containers work under the hood and eventually turned into a small library of reusable implementations.

Current focus:

* Stability
* Clean memory management
* Reasonable performance
* Single-header implementations
* Keeping the code easy to read

## Implemented

* Dynamic Array/Vector
* Linked List
* Stack
* Queue
* Hash Map

## Building

Clone the repository:

```bash
git clone https://github.com/ManandeepSingh1196/C-Containers.git
cd C-Containers
```

Build the project:

```bash
make
```

Run tests:

```bash
make test
```

Run with Valgrind:

```bash
make valgrind
```

### Single-header containers

Every container lives in its own header and can be dropped into a project without additional setup.

### No unnecessary cleverness

The goal is not to produce the shortest code possible.

The goal is to produce code that I can come back to six months later and still understand.

## Project Structure

```text
src/
├── vector.h
├── linked_list.h
├── stack.h
├── queue.h
└── hashmap.h

tests/
examples/
```

## Roadmap

Things I'd like to add:

* Generic container support
* Deque
* Priority Queue
* Tree structures
* Common algorithms
* Benchmarks
* Better documentation

## Why?

Mostly because implementing stuff is fun.



