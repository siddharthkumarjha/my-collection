#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>

class Animal
{
        private:
                virtual void speak (void) = 0;
                virtual void legs (void) = 0;
        public:
                void trigger_proxy(const std::unique_ptr<Animal> &ptr);
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
        protected:
                Duck(void)
                {
                        throw std::runtime_error("hmm, looks like you aren't allowed to create this object!!\n");
                }
        public:
                static std::optional<Duck *> Factory_func(void)
                {
                        try {
                                return new Duck();
                        } catch (std::runtime_error &E) {
                                std::cerr << E.what();
                        }
                        return std::nullopt;
                }

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

void Animal::trigger_proxy(const std::unique_ptr<Animal> &ptr)
{
        ptr->speak();
        ptr->legs();
        std::printf("\n");
}

int main(void)
{
        std::unique_ptr<Animal> ptr = nullptr;

        ptr = std::make_unique<Human>();
        ptr->trigger_proxy(ptr);

        ptr = nullptr;
        std::printf("\n");

        const auto &factory_ptr = Duck::Factory_func();
        if(factory_ptr.has_value())
        {
                ptr = std::unique_ptr<Duck>(factory_ptr.value());
                ptr->trigger_proxy(ptr);
        }

        return 0;
}
