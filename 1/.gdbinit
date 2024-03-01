# Switch to the 'next' layout
layout next

# Define any custom commands
define print_stack_b_values
	set $temp = stack_b
	while ($temp != 0)
		printf "stack b: %d ", $temp->value
		set $temp = $temp->next
	end
end
define print_stack_a_values
    set $temp = stack_a
    while ($temp != 0)
        printf "stack a: %d ", $temp->value
        set $temp = $temp->next
    end
end

# Any other initialization commands


#Basics of GDB
# Running GDB with args
# gdb --args ./program arg1 arg2 ...

# Starting and Controlling Program Execution
# run [args...]: Starts the execution of your program with optional arguments.
# start [args...]: Starts your program and stops at the beginning of the main function.
# continue (or c): Continues running your program until the next breakpoint.
# next (or n): Executes the next program line (steps over function calls).
# step (or s): Executes the next program line (steps into function calls).
# finish: Runs until the current function is finished.
# kill: Stops the execution of your program.

# Inspecting the Program
# list [function/line]: Shows the source code around the specified function or line number. If no argument is given, it continues listing from where it left off.
# backtrace (or bt): Displays the call stack to show the function call path that led to the current point.
# frame [number]: Selects a frame from the call stack to examine or modify.
# info locals: Displays local variables in the current frame.
# print [expression] (or p [expression]): Evaluates and prints the value of an expression.
# watch [expression]: Sets a watchpoint for an expression (breaks execution whenever the expression value changes).
# info breakpoints: Lists all breakpoints, watchpoints, and catchpoints.

# Setting Breakpoints
# break [location] (or b [location]): Sets a breakpoint at the specified location (function, line number, or address).
# delete breakpoints [number]: Deletes the specified breakpoint(s). Without a number, deletes all.
# disable breakpoints [number]: Disables the specified breakpoint(s).
# enable breakpoints [number]: Enables the specified breakpoint(s).

# Modifying Program State
# set var [variable]=value: Changes the value of a variable.
# jump [line/function]: Transfers execution to the specified line or function.
# Miscellaneous
# layout src: In TUI (Text User Interface) mode, shows the source code window.
# layout asm: In TUI mode, shows the assembly window.
# layout split: In TUI mode, shows both source and assembly.
# help [command]: Displays help for the specified command. Without an argument, it shows general help.

# Exiting GDB
# quit (or q): Exits GDB.