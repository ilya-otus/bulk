#pragma once

template<typename T>
class IOutputItem
{
public:
    virtual ~IOutputItem() = default;
    bool available() const {
        return static_cast<const T*>(this)->isAvailable();
    }
    template<typename U>
    friend IOutputItem<T>& operator<<(IOutputItem<T> &outputItem, const U &value) {
        outputItem.dump(value);
        return outputItem;
    }
protected:
    template<typename U>
    void dump(const U &value) {
        static_cast<T*>(this)->output(value);
    }
};

