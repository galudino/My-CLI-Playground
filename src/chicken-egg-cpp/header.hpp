#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class egg;
class bird;
class chicken;
class penguin;

class bird {
public:
    virtual ~bird() {}
    virtual auto lay_egg() -> std::unique_ptr<egg> = 0;
};

class egg {
public:
    using birdmaker = std::function<std::unique_ptr<bird>()>;

    egg(birdmaker bm) : m_make_bird{bm} { }
    auto hatch() -> std::unique_ptr<bird>;
private:
    birdmaker m_make_bird; 
    bool m_hatched{};
};

class chicken : public bird {
public:
    auto lay_egg() -> std::unique_ptr<egg> override {
        std::cout << "Laying an egg for a chicken." << std::endl;
        return std::make_unique<egg>(s_make_chicken);
    }

    static auto mother_chicken() -> std::shared_ptr<chicken> {
        return s_mother_chicken;
    }
private:
    static const egg::birdmaker s_make_chicken;
    static std::shared_ptr<chicken> s_mother_chicken;
};

class penguin : public bird {
public:
    auto lay_egg() -> std::unique_ptr<egg> override {
        std::cout << "Laying an egg for a penguin." << std::endl;
        return std::make_unique<egg>(s_make_penguin);
    }

    static auto mother_penguin() -> std::shared_ptr<penguin> {
        return s_mother_penguin;
    }
private:
    static const egg::birdmaker s_make_penguin;
    static std::shared_ptr<penguin> s_mother_penguin;
};

#endif /* HEADER_HPP */

