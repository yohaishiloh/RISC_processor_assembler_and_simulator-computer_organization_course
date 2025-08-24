# RISC Processor – Assembler and Simulator

This repository contains the implementation of a **RISC-based processor project** for the *Computer Organization* course.  
It includes an assembler, a cycle-accurate simulator, and several assembly programs with test inputs and outputs.

---

## 📋 Overview
- **Assembler (`assembler/`)**  
  A two-pass assembler written in C.  
  - Translates `.asm` programs into machine code (`imemin.txt`, `dmemin.txt`).  
  - Handles registers, immediates, opcodes, and produces trace/debug files.  
  - Includes modular functions (`LineToCodeFunc.c`, `OpcodeConvertFunc.c`, etc.).

- **Simulator (`simulator/`)**  
  A cycle-accurate simulator written in C.  
  - Loads input memory (`imemin.txt`, `dmemin.txt`, `diskin.txt`, `irq2in.txt`).  
  - Simulates CPU, memory, and I/O devices (disk, LEDs, 7-seg display, monitor).  
  - Produces detailed outputs: `dmemout.txt`, `regout.txt`, `trace.txt`, `hwregtrace.txt`, `cycles.txt`, `monitor.yuv`.

- **Assembly programs (`assmebly programs/`)**  
  Example workloads to run on the processor:  
  - **`binom/`** – compute binomial coefficients.  
  - **`circle/`** – draw circles on the simulated monitor.  
  - **`disktest/`** – test program for disk and I/O interaction.  
  - **`mulmat/`** – matrix multiplication.  
  Each folder includes `.asm` source and expected input/output files.

- **Documentation**  
  - `computer organization assignment.pdf` – project assignment description.  
  - `computer organization project - report.pdf` – submitted final report.

---

## ▶️ How to Build and Run
1. **Assembler**
   - Navigate to `assembler/`.  
   - Compile (e.g., `gcc *.c -o assembler`).  
   - Run on an `.asm` program to generate input files for the simulator.  

2. **Simulator**
   - Navigate to `simulator/`.  
   - Compile (e.g., `gcc *.c -o simulator`).  
   - Run with generated input files.  
   - Inspect output traces (`trace.txt`, `regout.txt`, etc.).

3. **Run Assembly Examples**
   - Use the `.asm` files in `assmebly programs/`.  
   - Compare outputs with the reference files in each program folder.

---

## 🎯 Purpose
This project demonstrates the design and validation of a **RISC processor model**, focusing on:
- Instruction set implementation.  
- Assembler design (two-pass).  
- Cycle-accurate CPU and device simulation.  
- Execution of non-trivial assembly programs with I/O.

---

## 📂 Repository Structure
- assembler/ # Assembler in C
- simulator/ # Simulator in C
- assmebly programs/ # Example assembly programs with inputs/outputs
- docs/ # Project assignment and report (PDFs)
- `README.md` - Project documentation
