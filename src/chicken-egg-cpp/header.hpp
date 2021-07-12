#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

class egg;
class bird;
class chicken;
class penguin;

class bird {
public:
    virtual ~bird() {}
    virtual std::unique_ptr<egg> lay_egg() = 0;
};

class egg {
public:
    using birdmaker = std::function<std::unique_ptr<bird>()>;

    egg(birdmaker bm) : m_make_bird(bm){}

    std::unique_ptr<bird> hatch() {
        if (m_hatched) {
            throw std::logic_error("Egg already hatched");
        }
        
        std::cout << "Hatching a ";

        m_hatched = true;
        return m_make_bird();
    }
private:
    birdmaker m_make_bird; 
    bool m_hatched = false;
};

class chicken : public bird {
public:
    std::unique_ptr<egg> lay_egg() override {
        std::cout << "Laying an egg for a chicken" << std::endl;
        return std::make_unique<egg>([]{ 
            std::cout << "chicken" << std::endl; 
            return std::make_unique<chicken>(); 
        });
    }
};

class penguin : public bird {
public:
    std::unique_ptr<egg> lay_egg() override {
        std::cout << "Laying an egg for a penguin" << std::endl;
        return std::make_unique<egg>([]{
            std::cout << "penguin" << std::endl;
            return std::make_unique<penguin>();
        });
    }
};

#endif /* HEADER_HPP */

