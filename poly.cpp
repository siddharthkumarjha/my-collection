#include <cstdio>
#include <memory>
#include <expected>

class Animal
{
        private:
                virtual void speak (void) = 0;
                virtual void legs (void) = 0;
        public:
                std::expected<void, std::string> trigger_proxy(std::unique_ptr<Animal> &ptr);
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

std::expected<void, std::string> Animal::trigger_proxy(std::unique_ptr<Animal> &ptr)
{
        if(ptr == nullptr)
                return std::unexpected("trigger_proxy called when unique_ptr ptr is null");
        ptr->speak();
        ptr->legs();
        return {};
}

int main(void)
{
        std::unique_ptr<Animal> ptr = nullptr;

        ptr = std::make_unique<Human>();
        auto num = ptr->trigger_proxy(ptr);
        if(!num.has_value())
                std::printf("\nError msg: %s", num.error().c_str());
        std::printf("\n");

        ptr = nullptr;
        std::printf("\n");

        ptr = std::make_unique<Duck>();
        num = ptr->trigger_proxy(ptr);
        if(!num.has_value())
                std::printf("\nError msg: %s", num.error().c_str());
        std::printf("\n");

        ptr = nullptr;
        num = ptr->trigger_proxy(ptr);
        if(!num.has_value())
                std::printf("\nError msg: %s", num.error().c_str());
        return 0;
}
