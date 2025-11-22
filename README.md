# Adventure Game Inventory System – Fibonacci Heap Implementation

## Overview
This project implements an inventory system for managing two types of gems: diamonds and moissanites.  
The system uses **Fibonacci heaps** to efficiently support insertion, extraction, merging, and special removal operations.

Two separate heaps are maintained:
- **Max-heap** for storing diamond values  
- **Min-heap** for storing moissanite values  

All values are integers, and all heap operations are fully dynamic.

---

## Features

### Core Functionality
- Create and destroy both heaps
- Insert diamonds and moissanites into their respective heaps
- Extract:
  - the **largest diamond** (from the max Fibonacci heap)
  - the **smallest moissanite** (from the min Fibonacci heap)
- Merge the two heaps when required
- Print the current state of both heaps

### Special Removal Operation
Includes functionality to remove **k largest diamonds**, using repeated extract-max operations on the Fibonacci max-heap.

---

## Command Interface
The program supports a simple text-based command system:

V – create both heaps
B – destroy heaps
D[x] – insert diamond with value x
M[x] – insert moissanite with value x
T – extract largest diamond
P – extract smallest moissanite
G – print current heap contents
L – merge heaps
R[k] – remove k largest diamonds
## Implementation Details
- Fibonacci heaps are used for both max and min heap structures  
- Loose coupling between heap logic and game logic  
- Error handling for invalid operations and empty heaps  
- No recursion used in heap operations  
