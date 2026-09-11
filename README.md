# Shamir's Secret Sharing (C++)
This project is a secure, efficient C++ implementation of Shamir's Secret Sharing algorithm, which cryptographically splits a mathematical secret into multiple distributed shares, requiring a predefined minimum threshold of those shares to successfully reconstruct the original data.

## The Mathematics Behind the Algorithm
Shamir's Secret Sharing is built on the concept of polynomial interpolation over a finite field. It relies on the mathematical principle that it takes exactly $t$ points to uniquely define a polynomial of degree $t-1$.
### 1. Splitting the Secret

To share a secret $S$ with a threshold of $t$ (the minimum number of shares required to reconstruct it), the algorithm constructs a random polynomial $f(x)$ of degree $t-1$:
  
$$f(x) = S + a_1x + a_2x^2 + \dots + a_{t-1}x^{t-1} \pmod p$$
* **The Secret:** The constant term $a_0$ is set to the secret $S$ (i.e., $f(0) = S$).

* **The Coefficients:** The remaining coefficients ($a_1, a_2, \dots, a_{t-1}$) are chosen randomly from a uniform distribution over a finite field of prime size $p$.

* **The Shares:** The algorithm generates $n$ shares by evaluating the polynomial at $n$ non-zero points. Each participant receives a share represented as a coordinate pair: $(x_i, f(x_i))$.
### 2. Reconstructing the Secret

When $t$ or more participants pool their shares, the original polynomial can be reconstructed using **Lagrange Interpolation**. Because we only need the secret $S$ (which is $f(0)$), we evaluate the interpolated polynomial directly at $x = 0$:

$$S = f(0) = \sum_{i=1}^{t} y_i \prod_{j=1, j \neq i}^{t} \frac{-x_j}{x_i - x_j} \pmod p$$

If fewer than $t$ shares are provided, the polynomial remains entirely undetermined, meaning the secret is completely mathematically secure.
## Engineering Architecture & Learnings
Developing this cryptographic algorithm from scratch required several deliberate architectural and engineering decisions:
* **Finite Field Encapsulation:** Standard computer arithmetic handles division using floating-point approximations, which destroys cryptographic data. I engineered a dedicated `FiniteField` class to handle modular addition, multiplication, and specifically modular multiplicative inverses (using the Extended Euclidean Algorithm or Fermat's Little Theorem) to ensure perfect mathematical precision.

* **Algorithmic Optimization:** During the reconstruction phase, the naive approach would iterate over all available shares. I optimized the `ReconstructSecret` function to selectively process exactly the $t$ shares required for interpolation. This reduces the time complexity and avoids wasting CPU cycles on redundant $O(t^2)$ field operations.

* **Strict Separation of Concerns:** The core library strictly abstracts the finite field math from the application state. The library handles pure cryptographic calculation, while the CLI/application layer handles share subset selection and user input.

* **Automated Testing Pipeline:** The implementation is backed by a GoogleTest suite integrated directly into the CMake pipeline, verifying the determinism of the polynomial generation and the mathematical accuracy of the Lagrange reconstruction.
## Build and Run Instructions
This project uses CMake as its build system. Ensure you have a C++ compiler and CMake installed on your system.

### **1. Build the Project**
Navigate to the project root and run the following commands to generate the build files and compile the executable:

```bash
cmake -B build
cmake --build build
```

### 2. **Run the Application**
Once compiled, you can run the interactive command-line application:

```Bash
./build/shamir_program
```

### 3. **Run the Test Suite**
To execute the automated GoogleTest suite and verify cryptographic correctness:

```Bash
cd build
ctest
```