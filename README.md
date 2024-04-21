# Dog-Simulation-Game

One-line description: A C interactive game simulation where players can adopt a dog, interact with it, and manage dog-related assets like dog houses.

Summary: This C program is an interactive simulation game that provides players with the ability to adopt a virtual dog, interact through predefined actions, and manage a dog house. The game is implemented using structures to represent the dog and dog house, encapsulating functionalities like barking, fetching a flag from a file, and simulating the dog's death. Players can interact with the game through a text-based menu that allows them to buy a dog, make the dog perform actions, build and manage a dog house, and simulate the dog's death.

**Key Features:**
- **Dog Adoption:** Players can name and adopt a new dog, dynamically allocated in memory.
- **Interactions:** The dog can bark multiple times, fetch a flag from a file, and players can simulate its death, which includes deallocating the dog from memory.
- **Dog House Management:** Players can build a dog house by specifying its address and name, attach the dog to the dog house, and eventually break the dog house, freeing its allocated memory.
- **Memory Management:** The program handles dynamic memory allocation and deallocation for dogs and dog houses, ensuring proper management of resources to prevent memory leaks.
- **Security Considerations:** The simulation includes use-after-free protection by nullifying pointers post-deallocation, although it playfully introduces potential security risks in functions like fetching flags, highlighting common pitfalls in C programming.

This simulation serves as an educational tool to demonstrate basic memory management in C, struct usage, and simple file I/O operations within a playful, interactive context. It allows beginner programmers to explore these fundamental concepts in a controlled environment while managing the lifecycle of game entities.
