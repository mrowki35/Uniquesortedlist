# SortedUniqueVectoredList

SortedUniqueVectoredList is a C++ class that represents a sorted and unique vector-like container for storing strings. It provides efficient operations for insertion, deletion, and retrieval, while maintaining sorted and unique properties of the elements.

## Table of Contents

1. [Methods](#methods)
2. [Operators](#operators)
3. [Example](#example-usage)
## Methods

### SortedUniqueVectoredList()

- Constructor for creating an empty SortedUniqueVectoredList object.

### SortedUniqueVectoredList(const SortedUniqueVectoredList &source)

- Copy constructor for creating a SortedUniqueVectoredList object by copying another object.

### SortedUniqueVectoredList(SortedUniqueVectoredList &&another)

- Move constructor for creating a SortedUniqueVectoredList object by moving another object.

### ~SortedUniqueVectoredList()

- Destructor for releasing the allocated memory.

### SortedUniqueVectoredList& operator=(SortedUniqueVectoredList &&another)

- Move assignment operator for assigning the contents of another object to the current object.

### void insert(const std::string &value)

- Inserts a string value into the SortedUniqueVectoredList while maintaining the sorted and unique properties.

### void erase(const std::string &value)

- Erases a string value from the SortedUniqueVectoredList, if present.

### operator std::string() const

- Conversion operator that returns a string representation of the SortedUniqueVectoredList.

### bool contains(const std::string &value) const

- Checks if a string value is present in the SortedUniqueVectoredList.

### SortedUniqueVectoredList operator-(const SortedUniqueVectoredList &another) const

- Returns a new SortedUniqueVectoredList that contains the elements present in the current list but not in another list.

### SortedUniqueVectoredList& operator*=(const size_t howManyTimesMultiply)

- Multiplies the string values in the SortedUniqueVectoredList by a given factor.

### std::string& operator[](size_t index)

- Returns a mutable reference to the string value at the specified index.

### const std::string& operator[](size_t index) const

- Returns a const reference to the string value at the specified index.

## Operators

### operator=(const SortedUniqueVectoredList &another)

- Copy assignment operator for assigning the contents of another object to the current object.

### friend std::ostream& operator<<(std::ostream& stream, const SortedUniqueVectoredList& container)

- Overloaded stream insertion operator for printing the contents of the SortedUniqueVectoredList.

## Example Usage

Here's an example demonstrating how to use the SortedUniqueVectoredList:

```cpp
#include "SortedUniqueVectoredList.h"

int main() {
    SortedUniqueVectoredList list;
    list.insert("apple");
    list.insert("banana");
    list.insert("carrot");

    std::cout << list << std::endl;  // Output: ["apple", "banana", "carrot"]

    list.erase("banana");

    std::cout << list << std::endl;  // Output: ["apple", "carrot"]

    return 0;
}
