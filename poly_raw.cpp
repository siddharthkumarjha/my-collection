#include <cstdio>
#include <stdexcept>

class Animal
{
        virtual void speak (void) = 0;
        virtual void legs (void) = 0;
        public:
        void trigger_proxy(Animal *ptr);
        virtual ~Animal(void) 
        {
                std::printf("Animal destroyed!!\n");
        }
};
class Human : public Animal
{
        public:
                void speak(void) override;
                void legs(void) override;
                ~Human(void)
                {
                        std::printf("Human destroyed!!\n");
                }
};
class Duck : public Animal
{
        public:
                void speak(void) override;
                void legs(void) override;
                ~Duck(void)
                {
                        std::printf("Duck destroyed!!\n");
                }
};

void Human::speak(void)
{
        std::printf("Human speak speak!!\n");
}
void Human::legs(void)
{
        std::printf("Humans are bipedal...\n");
}
void Duck::speak(void)
{
        std::printf("Duck speak speak!!\n");
}
void Duck::legs(void)
{
        std::printf("Ducks are bipedal...\n");
}

void Animal::trigger_proxy(Animal *ptr)
{
        if(ptr == nullptr)
                throw std::runtime_error("\ntrigger_proxy called with null Animal pointer\n");

        ptr->speak();
        ptr->legs();
}

int main(void)
{
        Animal *ptr = nullptr;

        ptr = new Human();
        ptr->trigger_proxy(ptr);
        std::printf("\n");

        delete ptr;
        ptr = nullptr;

        std::printf("\n");

        ptr = new Duck();
        ptr->trigger_proxy(ptr);
        std::printf("\n");

        delete ptr;
        ptr = nullptr;

        std::printf("\n");

        ptr->trigger_proxy(ptr);
        return 0;
}
