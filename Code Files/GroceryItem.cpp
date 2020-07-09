#include <cmath>
#include <iostream>
#include <utility>
#include <iomanip>
#include <string>
#include "GroceryItem.hpp"

namespace
{
    constexpr auto EPSILON = 1.0E-4;
}
GroceryItem::GroceryItem(const std::string& productName,
    const std::string& brandName,
    const std::string& upcCode,
    double              price)
    : _upcCode(upcCode),
    _brandName(brandName),
    _productName(productName),
    _price(price)
{}
std::string GroceryItem::upcCode() const
{
    return _upcCode;
}
std::string GroceryItem::brandName() const
{
    return _brandName;
}
std::string GroceryItem::productName() const
{
    return _productName;
}
double GroceryItem::price() const
{
    return _price;
}
void GroceryItem::upcCode(const std::string& upcCode)
{
    _upcCode = upcCode;
}
void GroceryItem::brandName(const std::string& brandName)
{
    _brandName = brandName;
}
void GroceryItem::productName(const std::string& productName)
{
    _productName = productName;
}
void GroceryItem::price(double price)
{
    _price = price;
}
std::istream& operator>>(std::istream& stream, GroceryItem& groceryItem)
{
    try
    {
        GroceryItem workingItem;
        char delimiter = ',';
        stream >> std::quoted(workingItem._upcCode) >> delimiter
            >> std::quoted(workingItem._brandName) >> delimiter
            >> std::quoted(workingItem._productName) >> delimiter
            >> workingItem._price;
        if (workingItem.upcCode() != "00000000000000")
            groceryItem = std::move(workingItem);
    }
    catch (const std::ios::failure&)
    {
        if (!stream.eof()) throw;
    }
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const GroceryItem& groceryItem)
{
    const std::string delimiter = ", ";
    stream << std::quoted(groceryItem.upcCode()) << delimiter
        << std::quoted(groceryItem.brandName()) << delimiter
        << std::quoted(groceryItem.productName()) << delimiter
        << groceryItem.price();
    return stream;
}
bool operator==(const GroceryItem& lhs, const GroceryItem& rhs)
{
    if constexpr ((true))
    {
        return !(lhs < rhs) && !(rhs < lhs);
    }
    else
    {
        return    lhs._upcCode == rhs._upcCode
            && lhs._brandName == rhs._brandName
            && lhs._productName == rhs._productName
            && std::abs(lhs._price - rhs._price) < EPSILON;
    }
}
bool operator< (const GroceryItem& lhs, const GroceryItem& rhs)
{
    if (auto result = lhs._upcCode.compare(rhs._upcCode); result != 0)   return result < 0;
    if (auto result = lhs._brandName.compare(rhs._brandName); result != 0)   return result < 0;
    if (auto result = lhs._productName.compare(rhs._productName); result != 0)   return result < 0;
    if (std::abs(lhs._price - rhs._price) >= EPSILON)                            return lhs._price < rhs._price;
    return false;
}
bool operator!=(const GroceryItem& lhs, const GroceryItem& rhs) { return !(lhs == rhs); }
bool operator<=(const GroceryItem& lhs, const GroceryItem& rhs) { return !(rhs < lhs); }
bool operator> (const GroceryItem& lhs, const GroceryItem& rhs) { return  (rhs < lhs); }
bool operator>=(const GroceryItem& lhs, const GroceryItem& rhs) { return !(lhs < rhs); }
