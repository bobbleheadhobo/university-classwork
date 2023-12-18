# Joey Troyer
# 11/09/23
# purpose: Simulates the memory managment of an OS. Such as starting and stopping processes and compaction.

class MemoryManagement:
    def __init__(self, size) -> None:
        self.RAM = [False] * size # array of user defined size to act as ram
        self.processes = {}       # dictionary to store the base and size of each process

    def main(self):
        while True:
            command = input()
            command = command.upper()
            cmd = command.split()

            try:
                # Execute the given command
                if cmd[1] == "START":
                    self.start_process(cmd[2], int(cmd[3]), int(cmd[0]))
                elif cmd[1] == "LOC":
                    self.locate(cmd[2], int(cmd[3]))
                elif cmd[1] == "DUMP":
                    self.dump()
                elif cmd[1] == "DUMP_FREE":
                    self.dump_free_memory()
                elif cmd[1] == "STOP":
                    self.stop_process(cmd[2])
                elif cmd[1] == "END":
                    print("Simulation ending...")
                    exit(0);
                else:
                    raise Exception()
            except Exception as e:
                print(f"Invalid command {command}")
                continue

    # PRE: self, the pid od the process, the size of the process and the time stamp of the command
    # POST: Check if there is enough free memory. Adds processes to dictionary and carves out availble memory in the array for it
    def start_process(self, pid, size, time):
        # make sure no more than 10 processes
        if len(self.processes) >= 10:
            print("MAXIMUM NUMBER OF PROCESSES REACHED. CANNOT START NEW PROCESS.")
            return

        # make sure process is not already running
        if pid in self.processes:
            print(f"PROCESS {pid} ALREADY RUNNING!")
            return

        # get next starting position of free memory
        base_address = self.find_free_memory(size)

        # not enough space
        if base_address == -1:
            print("NOT ENOUGH SPACE")
            return
        
        # enough space but need to compact memory first
        if base_address == -2:
            base_address = self.garbage_collect(time) # returns new base address

        # allocate the memory
        for i in range(base_address, base_address + size):
            self.RAM[i] = True

        # store process details
        self.processes[pid] = {'base': base_address, 'size': size}
        print(f"STARTED PROCESS {pid} OF SIZE {size}")



    # PRE: self and the pid of the process to stop
    # POST: removes process from dictionary and deallocates memory in the array for it
    def stop_process(self, pid):

        if pid not in self.processes:
            print(f"PROCESS {pid} IS NOT RUNNING!")
            return

        # get base and size of the process
        base_address = self.processes[pid]['base']
        size = self.processes[pid]['size']

        # allocate the memory
        for i in range(base_address, base_address + size):
            self.RAM[i] = False

        # delete process details
        del self.processes[pid]
        print(f"PROCESS {pid} STOPPED")
        

    # PRE: self
    # POST: print all active processes to terminal
    def dump(self):
        if not self.processes:
            print("NO PROCESSES RUNNING")
        else:
            print("PROCESS   BASE   BOUND   SIZE")
            # print each item in my dictionary
            for pid, details in self.processes.items(): # for each item in dict
                print(f"{pid:<9} {(details['base']):<6} {(details['base'] + details['size'] - 1):<6}  {details['size']:<6}")

    # PRE: self
    # POST: print all the holes in the ram array
    def dump_free_memory(self):
        last_address = 0
        total_free_space = 0
        total_ram = len(self.RAM)

        print("FREE MEMORY SEGMENTS:")
        #loop through all the processes in order of lowest base to greatest base
        for pid, details in sorted(self.processes.items(), key=lambda x: x[1]['base']):
            base = details['base']
            size = details['size']

            # calculate size from the end of the last process to the start of the next one
            free_space = base - last_address
            total_free_space += free_space
            if free_space > 0:
                print(f"{last_address} - {base - 1} (SIZE: {free_space})")

            # set last address to the end location of the last process
            last_address = base + size

        # Check for free space past the end of the last process
        if last_address < total_ram:
            free_space = total_ram - last_address
            total_free_space += free_space
            print(f"{last_address} - {total_ram - 1} (SIZE: {free_space})")

        # if no free space
        if total_free_space == 0:
            print("NO FREE SPACE!")



    # PRE: self and the size of the new process to add
    # POST: Goes through ram array and looks for free memory of specific size
    def find_free_memory(self, size):
        free_count = 0
        total_free_count = 0

        # iterates through each element in the array and its value
        for i, byte in enumerate(self.RAM):
            if byte != True: # if the space is not empty
                free_count += 1
                total_free_count += 1
                if free_count == size:
                    return i - size + 1 # return the staring location of the space
            else:  
                free_count = 0

        # check if we need to garbage collect
        if total_free_count >= size:
            return -2 # garbage collect
        
        return -1 # not enough space
    

    # PRE: self, the time of the start process command that needs to be made space for
    # POST: Removes all holes from memory. Returns the next free spot in memory
    #
    # STRAT: To prevent 'over writing' data it sorts all processes by base and then moves each process to over to fill the hole.
    # Moving each process by lowest to greatest base until it has moved all processes. It then returns the next free spot in memory
    def garbage_collect(self, time):
        next_free_spot = 0
        
        # loops through the processes in order of lowest to greatest base
        for pid, details in sorted(self.processes.items(), key=lambda x: x[1]['base']):
            base = details['base']
            size = details['size']

            # if the memory is not already in the next free spot move it
            if base != next_free_spot:

                for i in range(size):
                    # Move data from old position to new position
                    self.RAM[next_free_spot + i] = self.RAM[base + i]
                    # Mark the old position as free
                    self.RAM[base + i] = False

            # Update the base address of the process
            self.processes[pid]['base'] = next_free_spot

            # Update the position for the next process
            next_free_spot += size

        print(f"GARBAGE COLLECTION COMPLETED AT TIME {time}")
        return next_free_spot
    
    # PRE: self, the pid of the process to locate, the virtual memory location you want
    # POST: calculates the physical address of the process
    def locate(self, pid, va):
        
        # checks if the process is not running
        if pid not in self.processes:
            print(f"PROCESS {pid} IS NOT RUNNING!")
            return

        # calculate pa
        pa = self.processes[pid]['base'] + va

        # make sure pa is in memory space of process
        if pa >= self.processes[pid]['base'] + self.processes[pid]['size'] or pa < self.processes[pid]['base']:
            print(f"VIRTUAL ADDRESS {va} OUTSIDE MEMORY FOR {pid}")
            return
        
        print(f"PROCESS {pid} AT PHYSICAL LOCATION {pa}")



             




        





        
### STARTING POINT ###
starting = True
print("Simulation started")

# loops until user enters ram size
while starting:
    command = input()
    command = command.upper()
    cmd = command.split()
    if "RAM" not in cmd:
        print("PLEASE ENTER RAM FOLLOWED BY THE SIZE (EXPL: RAM 8000)")
        continue

    starting = False
    
    # creates MemoryManagement class
    mem = MemoryManagement(int(cmd[1]))
    print(f"Created RAM of size {cmd[1]}")
    mem.main()
