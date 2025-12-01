# GDB Guide — Practical debugging for this C++98 project

This guide collects a short, repeatable workflow and commands to debug the `ex00` project with `gdb`. It assumes you are working from `/home/shkaruna/42project/cpp09/ex00` and that your executable is `./btc` (adjust names as needed).

Keep it handy when you want to step through `BitcoinExchange::loadDatabase` or `processInput`.

---

## 1) Build with debug symbols (must do this first)
- Ensure the compiler emits debug symbols and avoids optimizations that confuse stepping. Edit the `Makefile` to include:
  - `-g -O0` in `CXXFLAGS` (or equivalent variable)
- Then from `ex00` run:

```bash
make clean
make
```

If `make` still builds with optimizations, explicitly set CXXFLAGS in the Makefile or call make like:

```bash
make CXXFLAGS="-g -O0"
```

---

## 2) Start gdb and pass program arguments
Start `gdb` with the binary (you can also call `gdb ./btc` and pass args to `run`):

```bash
gdb ./btc
# inside gdb
(gdb) run data.csv
```

Or from shell (one-liner):

```bash
gdb --args ./btc data.csv
(gdb) run
```

---

## 3) Useful breakpoints to set before running
Pick breakpoints by function name or file/line. Examples:

```
(gdb) break main
(gdb) break BitcoinExchange::loadDatabase
# or at a file line (replace NUMBER with the actual line number)
(gdb) break ex00/BitcoinExchange.cpp:45
```

If your code uses namespaces or has mangled names, break by file/line is more robust.

---

## 4) Canonical loop-debugging pattern (for `getline` problems)
When you have a loop like `while (std::getline(file, line))`, use these steps:

1. Set a breakpoint at the line that calls `getline`.
2. Run the program so it stops there for the first iteration.
3. Use `next` or `step` to execute the `getline` call.
4. Inspect the read string and stream state:

```
(gdb) print line.c_str()      # show the extracted text
(gdb) print file.eof()
(gdb) print file.fail()
(gdb) print file.good()
```

If `getline` is failing unexpectedly, the stream's `fail()` will be true. Remember: `std::getline` returns `istream&` which converts to `true` in boolean context if the read succeeded.

If you want to perform a `getline` manually from gdb to test an iteration:

```
(gdb) call std::getline(file, line)
(gdb) print line.c_str()
(gdb) print file.fail()
```

`call` executes the function in the debugged process — useful for targeted checks.

---

## 5) Inspecting `std::map` and STL objects
Modern `gdb` often provides libstdc++ pretty-printers that give nice views for `std::map`. If not:

- You can still inspect `size()` and a few elements:

```
(gdb) print mymap.size()
(gdb) print mymap.begin()->first
(gdb) print mymap.begin()->second
(gdb) print (--mymap.end())->first  # may require stepping into expression depending on gdb
```

- If pretty-printing is missing, enable it (path varies by distro). The simplest way is to install or enable libstdc++ printers for your gdb. See your distribution docs or add them to `~/.gdbinit`.

---

## 6) Conditional breakpoints & watchpoints
- Break when a specific line number or condition occurs:

```
(gdb) break BitcoinExchange.cpp:LINE if lineNo==42
```

- Watch a variable or expression for changes (use sparingly for heavy STL objects):

```
(gdb) watch btc._database.size()
```

Watchpoints stop when the watched expression changes.

---

## 7) Common small checks for file-reading bugs
- Confirm file opened: `print file.is_open()`
- Confirm stream state after a failed read: `print file.fail()`, `print file.eof()`
- Reveal trailing CR (`\r`) if Windows CRLF exists:

```
(gdb) print (int) line[line.size()-1]
```

- Print the raw line with visible delimiters to spot whitespace:

```
(gdb) printf "[%d] '%s'\n", lineNo, line.c_str()
```

(Using `printf` inside gdb formats the output nicely.)

---

## 8) Step vs next vs finish
- `step` (or `s`) steps into a function call
- `next` (or `n`) steps over (executes the function and stops after it)
- `finish` resumes until current function returns and shows the return value

Use `next` to execute `getline` calls without stepping into internals; use `step` if you want to see library internals (rarely needed).

---

## 9) Example gdb session (copy/paste friendly)

```
# from shell
gdb --args ./btc data.csv
# inside gdb
(gdb) break BitcoinExchange::loadDatabase
(gdb) run
# when stopped at loadDatabase
(gdb) next           # step to the ifstream construction / header skip
(gdb) break BitcoinExchange.cpp:LINE_OF_GETLINE
(gdb) continue
# Now program stops at getline each iteration
(gdb) next
(gdb) print line.c_str()
(gdb) print file.eof()
(gdb) print file.fail()
(gdb) continue       # resume until next breakpoint
# after the loop completes, inspect map
(gdb) print _database.size()
(gdb) print _database.begin()->first
(gdb) print _database.rbegin()->first
```

Replace `LINE_OF_GETLINE` with the line number where you call `std::getline` in `loadDatabase`.

---

## 10) Restarting and re-running after code changes
- Recompile with `make` outside gdb.
- Use `run` again from gdb to restart the program. If you edited source while gdb is running, you may need to `quit` and re-launch gdb after recompilation.

---

## 11) When you suspect a memory issue: run valgrind
If the program crashes, memory corruption may be involved. Run this (slower) check:

```bash
valgrind --leak-check=full ./btc data.csv
```

Valgrind runs outside gdb and will report leaks and invalid accesses.

---

## 12) Final tips and etiquette
- Keep builds with `-g -O0` while debugging. Optimizations may inline or reorder variables, confusing the debugger.
- Use focused breakpoints (function or file:line) rather than stopping at the program start every time.
- Use `print` and `printf` inside gdb to inspect values; `call` is powerful but actually runs code in your process.
- If you are debugging I/O loops, inspect the stream state right after the read.

---

If you want, I can now:
- Produce a short set of `gdb` commands using the **exact** file paths/line numbers from your `BitcoinExchange.cpp` (I can read the file and give `break file:line` commands), or
- Walk you interactively through one live gdb session (I’ll tell you what to type and what to inspect at each stop).

Which would you like next?