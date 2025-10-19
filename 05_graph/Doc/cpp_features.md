
## C++ Features Used in AdjacencyMatrixGraph.cpp

| Feature | Description / Why it’s useful | C Comparison |
|---------|-------------------------------|-------------|
| Initializer list (`: Graph(vertices), matrix(...)`) | Calls the base class constructor and initializes member variables before the constructor body runs. | In C, you’d assign struct members after allocation manually. |
| std::vector | Dynamic array with automatic memory management; handles resizing and cleanup automatically. | In C, you’d use `malloc`/`free` or fixed-size arrays. |
| 2D vector (`vector<vector<int>>`) | Stores adjacency matrix as a dynamic 2D array. | In C, you’d need `int**` and manual allocation loops. |
| override keyword | Ensures the derived class method correctly overrides a virtual base class method; compiler error if signatures don’t match. | C has no inheritance, so no equivalent. |
| const method (`bool isEdge(...) const`) | Guarantees the function does not modify the object; enforced by the compiler. | C cannot enforce read-only access for functions. |
| explicit constructor | Prevents implicit type conversion (e.g., `Graph g = 5;` would fail). | C has no constructors. |
| std::cout / std::endl | Type-safe C++ I/O streams replacing `printf`. | C uses `printf`, `puts`, etc. |
| Automatic memory management | Vectors automatically allocate and free memory when objects go out of scope. | In C, you must manually call `malloc` and `free`. |
| Range-based loop (optional) | Can iterate over containers without index arithmetic (used in modern C++11+). | In C, you must manually loop over arrays with indices or pointers. |

dot -Tpng graph.dot -o graph.png