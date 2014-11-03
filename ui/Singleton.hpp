#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename T>
class Singleton {
public:
    typedef std::function<T()> ConstructFunction;
public:
    Singleton<T>(ConstructFunction func = [](){return T();})
        : ctor(func){}

    const T& getInstance() const{
        static const T val = ctor();
        return val;
    }
private:
    ConstructFunction ctor;
};

#endif // SINGLETON_HPP
