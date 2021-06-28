#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

class egg;

class bird {
public:
    virtual ~bird() {}
    virtual egg *lay_egg() = 0;
};

class egg {
public:
    using birdmaker = std::function<bird *()>;

    egg(birdmaker bm) : m_make_bird(bm){}

    bird *hatch() {
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
    egg *lay_egg() {
        return new egg([]{ 
            std::cout << "chicken" << std::endl; 
            return new chicken; 
        });
    }
};

class penguin : public bird {
public:
    egg *lay_egg() {
        return new egg([]{
            std::cout << "penguin" << std::endl;
            return new chicken;
        });
    }
};

#endif /* HEADER_HPP */

