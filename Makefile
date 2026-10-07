CC = gcc
CFLAGS = -Wall -Wextra -std=c11
PTHREAD = -pthread

BIN = bin

.PHONY: all directories pipe fifo scheduler memory filesystem concurrency launcher clean run

all: directories pipe fifo scheduler memory filesystem concurrency launcher

directories:
	mkdir -p $(BIN)

pipe:
	$(CC) $(CFLAGS) src/pipe/pipe_demo.c -o $(BIN)/pipe_demo
	$(CC) $(CFLAGS) src/pipe/ipc_benchmark.c -o $(BIN)/ipc_benchmark
	$(CC) $(CFLAGS) src/pipe/bidirectional_pipe.c -o $(BIN)/bidirectional_pipe

fifo:
	$(CC) $(CFLAGS) src/fifo/fifo_writer.c -o $(BIN)/fifo_writer
	$(CC) $(CFLAGS) src/fifo/fifo_reader.c -o $(BIN)/fifo_reader

scheduler:
	$(CC) $(CFLAGS) src/scheduling/scheduler.c -o $(BIN)/scheduler

memory:
	$(CC) $(CFLAGS) src/memory/memory_manager.c -o $(BIN)/memory_manager

filesystem:
	$(CC) $(CFLAGS) src/filesystem/file_io_demo.c -o $(BIN)/file_io_demo
	$(CC) $(CFLAGS) src/filesystem/file_metadata.c -o $(BIN)/file_metadata
	$(CC) $(CFLAGS) src/filesystem/directory_demo.c -o $(BIN)/directory_demo
	$(CC) $(CFLAGS) src/filesystem/buffer_demo.c -o $(BIN)/buffer_demo
	$(CC) $(CFLAGS) src/filesystem/mmap_demo.c -o $(BIN)/mmap_demo

concurrency:
	$(CC) $(CFLAGS) $(PTHREAD) src/concurrency/thread_demo.c -o $(BIN)/thread_demo
	$(CC) $(CFLAGS) $(PTHREAD) src/concurrency/race_condition.c -o $(BIN)/race_condition
	$(CC) $(CFLAGS) $(PTHREAD) src/concurrency/mutex_demo.c -o $(BIN)/mutex_demo
	$(CC) $(CFLAGS) $(PTHREAD) src/concurrency/signal_demo.c -o $(BIN)/signal_demo
	$(CC) $(CFLAGS) $(PTHREAD) src/concurrency/deadlock_demo.c -o $(BIN)/deadlock_demo
	$(CC) $(CFLAGS) src/concurrency/process_monitor.c -o $(BIN)/process_monitor

launcher:
	$(CC) $(CFLAGS) src/ipc_system.c -o $(BIN)/ipc_system

clean:
	rm -f $(BIN)/pipe_demo
	rm -f $(BIN)/ipc_benchmark
	rm -f $(BIN)/bidirectional_pipe
	rm -f $(BIN)/fifo_writer
	rm -f $(BIN)/fifo_reader
	rm -f $(BIN)/scheduler
	rm -f $(BIN)/memory_manager
	rm -f $(BIN)/file_io_demo
	rm -f $(BIN)/file_metadata
	rm -f $(BIN)/directory_demo
	rm -f $(BIN)/buffer_demo
	rm -f $(BIN)/mmap_demo
	rm -f $(BIN)/thread_demo
	rm -f $(BIN)/race_condition
	rm -f $(BIN)/mutex_demo
	rm -f $(BIN)/signal_demo
	rm -f $(BIN)/deadlock_demo
	rm -f $(BIN)/process_monitor
	rm -f $(BIN)/ipc_system

run:
	./$(BIN)/ipc_system
