#ifndef ITEM_HPP
#define ITEM_HPP

class Item
{
public:
    Item(int w = 0, int v = 0);
    int getWeight() const;
    int getValue() const;
    void setWeight(int w);
    void setValue(int v);
    double getDensity() const;

private:
    int weight_;
    int value_;
};

#endif
