#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFLEN 64

struct Dog {
    char name[12];
    void (*bark)();
    void (*bringBackTheFlag)();
    void (*death)(struct Dog*);
};

struct DogHouse {
    char address[16];
    char name[8];
};

int eraseNl(char* line) {
    int i = 0;
    while (line[i] != '\n' && line[i] != '\0') i++;
    if (line[i] == '\n') line[i] = '\0';
    return 0;
}

void bark() {
    int i;
    for (i = 3; i > 0; i--) {
        puts("Bark!!!");
        sleep(1);
    }
}

void bringBackTheFlag() {
    char flag[32];
    FILE* flagFile = fopen(".passwd", "r");
    if (flagFile == NULL) {
        puts("fopen error");
        exit(1);
    }
    fread(flag, 1, 32, flagFile);
    flag[31] = '\0'; // Ensure the string is null-terminated
    fclose(flagFile);
    printf("Flag: %s\n", flag);
}

void death(struct Dog* dog) {
    printf("%s run under a car... %s 0-1 car\n", dog->name, dog->name);
    // Here we would normally free the dog, but let's simulate the UAF
}

struct Dog* newDog(char* name) {
    struct Dog* dog = (struct Dog*)malloc(sizeof(struct Dog)); // Casting
    if (!dog) {
        puts("Failed to allocate memory for dog.");
        exit(1);
    }
    printf("You buy a new dog. %s is a good name for him\n", name);
    strncpy(dog->name, name, 12);
    dog->name[11] = '\0'; // Ensure the string is null-terminated
    dog->bark = bark;
    dog->bringBackTheFlag = bringBackTheFlag;
    dog->death = (void (*)(struct Dog*))death;
    return dog;
}

void attachDog(struct DogHouse* dogHouse, struct Dog* dog) {
    if (dogHouse && dog) {
        printf("%s lives in %s.\n", dog->name, dogHouse->address);
    }
}

void destruct(struct DogHouse* dogHouse) {
    if (dogHouse) {
        puts("You break the dog house.");
        free(dogHouse);
    } else {
        puts("You do not have a dog house.");
    }
}

struct DogHouse* newDogHouse() {
    char line[BUFLEN] = {0};
    struct DogHouse* dogHouse = (struct DogHouse*)malloc(sizeof(struct DogHouse)); // Casting
    if (!dogHouse) {
        puts("Failed to allocate memory for dog house.");
        exit(1);
    }
    puts("Where do you build it?");
    fgets(line, BUFLEN, stdin);
    eraseNl(line);
    strncpy(dogHouse->address, line, 16);
    puts("How do you name it?");
    fgets(line, BUFLEN, stdin);
    eraseNl(line);
    strncpy(dogHouse->name, line, 8);
    puts("You build a new dog house.");
    return dogHouse;
}

int main() {
    int end = 0;
    char order = -1;
    char line[BUFLEN] = {0};
    struct Dog* dog = NULL;
    struct DogHouse* dogHouse = NULL;

    while (!end) {
        puts("1: Buy a dog\n2: Make him bark\n3: Bring me the flag\n4: Watch his death\n5: Build dog house\n6: Give dog house to your dog\n7: Break dog house\n0: Quit");
        order = getc(stdin);
        while (getc(stdin) != '\n'); // Clear the rest of the line

        switch (order) {
            case '1':
                puts("How do you name him?");
                fgets(line, BUFLEN, stdin);
                eraseNl(line);
                dog = newDog(line);
                break;
            case '2':
                if (!dog) {
                    puts("You do not have a dog.");
                    break;
                }
                dog->bark();
                break;
            case '3':
                if (!dog) {
                    puts("You do not have a dog.");
                    break;
                }
                dog->bringBackTheFlag();
                break;
            case '4':
                if (!dog) {
                    puts("You do not have a dog.");
                    break;
                }
                dog->death(dog);
                free(dog); // Simulate the proper freeing here
                dog = NULL; // Prevent use after free by nullifying the pointer
                break;
            case '5':
                dogHouse = newDogHouse();
                break;
            case '6':
                if (!dog) {
                    puts("You do not have a dog.");
                    break;
                }
                if (!dogHouse) {
                    puts("You do not have a dog house.");
                    break;
                }
                attachDog(dogHouse, dog);
                break;
            case '7':
                destruct(dogHouse);
                dogHouse = NULL; // Prevent dangling pointer by nullifying after free
                break;
            case '0':
                end = 1;
                break;
            default:
                puts("Invalid option.");
        }
    }

    // Cleanup before exit
    if (dog) free(dog);
    if (dogHouse) free(dogHouse);

    return 0;
}
