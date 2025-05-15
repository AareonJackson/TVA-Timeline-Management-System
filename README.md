# TVA Timeline Management System

A C++ implementation of the Time Variance Authority (TVA) timeline management system from Marvel's Loki. Features a singly linked list representing the sacred timeline with branching nexus events that can be created and pruned. Includes both text and visual timeline representations with proper memory management.

## Features

- **Sacred Timeline**: Singly linked list implementation representing years in chronological order
- **Nexus Events**: Dynamic creation of timeline branches using innovative pointer array technique
- **Timeline Pruning**: Ability to remove branches and restore the sacred timeline
- **Visual Representation**: ASCII art visualization of the timeline and its branches
- **Memory Management**: Proper allocation and deallocation with no memory leaks

## Implementation Details

### Classes

**Node Class:**
- Contains year, branch count, and next pointer
- Two constructors: default and parameterized

**Timeline Class:**
- Private: size and head pointer
- Public methods: constructor, createNexusEvent, print, vprint, prune, destructor

### Key Algorithm

The program uses an innovative technique to create branching timelines:
- Normal nodes point to the next node in sequence
- When a nexus event occurs, the next pointer is converted to point to a dynamically allocated array of node pointers
- This allows a single pointer to reference both the original timeline and the branch
- The branch count indicates when to interpret the pointer as an array vs. single node

## Usage

```bash
g++ main.cpp -o tva
./tva [seed] [nexus_events] [start_year] [timeline_length]
```

**Parameters:**
- `seed`: Random seed for reproducible results
- `nexus_events`: Number of timeline branches to create
- `start_year`: Starting year of the timeline
- `timeline_length`: Number of years in the timeline

**Example:**
```bash
./tva 40 4 1970 50
```

## Output

The program displays:
1. Initial sacred timeline
2. Created nexus events with locations and sizes
3. Visual representation of branched timeline
4. Step-by-step pruning of branches
5. Restored sacred timeline

## Memory Safety

- All dynamic memory is properly allocated and deallocated
- Valgrind testing shows no memory leaks
- Proper handling of complex pointer structures

## Files

- `main.cpp` - Complete implementation
- Sample output files demonstrating various test cases

---

*For all time. Always.*
