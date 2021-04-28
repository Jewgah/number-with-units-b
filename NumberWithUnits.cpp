/**
 * NumberWithUnits Assignment
 * C++ Course @Ariel_University
 * 
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

namespace ariel {

    static map<string, map<string, double>> hmap;


    //Constructor
    NumberWithUnits::NumberWithUnits(double value, const string& unit) {

        if (hmap.count(unit) == ZERO) {
            throw invalid_argument("Unit " + unit + " not found");
        }

        //Initialize units
        this->value = value;
        this->unit = unit;
    }

    //fills the map with infos in text file
    void NumberWithUnits::read_units(ifstream& file) {

        string unit_1;
        string unit_2;
        double num_1 = ZERO;
        double num_2 = ZERO;

        string equal_sign;

        while(file >> num_1 >> unit_1 >> equal_sign >> num_2 >> unit_2) {


            hmap[unit_1][unit_2] = num_2;
            hmap[unit_2][unit_1] = ONE / num_2;
            hmap[unit_1][unit_1] = ONE;
            hmap[unit_2][unit_2] = ONE;

            //set links between units using hmp
            for (const auto &key1 : hmap[unit_1]){
                for (const auto &key2 : hmap[unit_2]) {
                    hmap[key1.first][key2.first] = hmap[key1.first][unit_1] * hmap[unit_1][unit_2] * hmap[unit_2][key2.first];
                    hmap[key2.first][key1.first] = 1 / hmap[key1.first][key2.first];
                }
            }
        }
    }

    //converts the unit using the hashmap
    static double convert(double value, const string& from, const string& to) {

        double result = ZERO;
            try { result = value * hmap.at(from).at(to); }
            catch(const exception& e) {
                throw invalid_argument{"Unit " + from + "can't be converted to " + to};
            }
         return result;
    }  
    
    // NumberWithUnits comparator
    static int compare(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {

        double zbao = convert(unit_num_2.getValue(),unit_num_2.getUnit(), unit_num_1.getUnit());
        double val = unit_num_1.getValue();

        if(val - zbao > TOLERANCE) {
            return 1;
        }

        else if(zbao - val > TOLERANCE) {
            return -1;
        }
        
        else{
            return 0;
        }
    }

    // Getters
    double NumberWithUnits::getValue() const { return this->value; }
    string NumberWithUnits::getUnit() const { return this->unit; }

    //Setters
    void NumberWithUnits::setValue(double val) {this->value = val;}
    void NumberWithUnits::setUnit(string val) {this->unit = val;}

    /**********************  Overloading Operators  **************************/

    // + operators

    NumberWithUnits operator+(const NumberWithUnits& unit_num) {
        return NumberWithUnits(unit_num.getValue(), unit_num.getUnit());
    }

    NumberWithUnits operator+(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        double cmp = convert(unit_num_2.getValue(), unit_num_2.getUnit(), unit_num_1.getUnit());
        return NumberWithUnits(unit_num_1.getValue() + cmp, unit_num_1.getUnit());
    }


    // ++ operators
    NumberWithUnits &NumberWithUnits::operator++() {
        this->value = this->value + ONE;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int) {
        return NumberWithUnits{this->value++, this->unit};
    }


    // += operator
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& unit_num_1) {
        if(this->unit == unit_num_1.unit) {
            this->value = this->value + unit_num_1.value;
            return *this;
        }

        try {
            double v = hmap.at(unit_num_1.unit).at(this->unit);
            this->value = this->value + (v * unit_num_1.value);
            return *this;
        } catch(const exception &e) {
            throw std::invalid_argument("Unit" + unit_num_1.unit + "can't be converted to " + this->unit);
        }
    }

    // - operators
    NumberWithUnits operator-(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        double cmp = convert(unit_num_2.getValue(), unit_num_2.getUnit(), unit_num_1.getUnit());
        return NumberWithUnits(unit_num_1.getValue()-cmp, unit_num_1.getUnit());
    }
    NumberWithUnits operator-(const NumberWithUnits& unit_num) {
        return NumberWithUnits(-unit_num.getValue(), unit_num.getUnit());
    }


    // -- operators
    NumberWithUnits &NumberWithUnits::operator--() {
        this->value = this->value - ONE;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int) {
        return NumberWithUnits{this->value--, this->unit};
    }


    // -= operator
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& unit_num_1) {
            if(this->unit == unit_num_1.unit) {
            this->value = this->value - unit_num_1.value;
            return *this;
        }

        try {
            double v = hmap.at(unit_num_1.unit).at(this->unit);
            this->value = this->value - (v * unit_num_1.value);
            return *this;
        } catch(const exception &e) {
            throw std::invalid_argument("Unit " + unit_num_1.unit + "can't be converted to " + this->unit);
        }
    }

    // * operators
    NumberWithUnits operator*(const NumberWithUnits& unit_num, double number) {
        return NumberWithUnits(unit_num.getValue() *number, unit_num.getUnit());
    }
    NumberWithUnits operator*(double number, const NumberWithUnits& unit_num) {
        return NumberWithUnits(unit_num.getValue() * number, unit_num.getUnit());
    }

    // *= operators
    NumberWithUnits operator*=(NumberWithUnits& unit_num, double number) {
        return NumberWithUnits(unit_num.value = unit_num.getValue() * number, unit_num.getUnit());
    }
    NumberWithUnits operator*=(double number, NumberWithUnits& unit_num) {
        return NumberWithUnits(number * unit_num.getValue(), unit_num.getUnit());
    }

    /** equality operators */

    // == operator
    bool operator==(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        return compare(unit_num_1, unit_num_2) == ZERO;
    }

    // != operator
    bool operator!=(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        return compare(unit_num_1, unit_num_2) != ZERO;
    }

    // < and <= operators
    bool operator<(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        return compare(unit_num_1, unit_num_2) < ZERO;
    }
    bool operator<=(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        return compare(unit_num_1, unit_num_2) <= ZERO;
    }

    // > and >= operators
    bool operator>(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        return compare(unit_num_1, unit_num_2) > ZERO;
    }
    bool operator>=(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2) {
        return compare(unit_num_1, unit_num_2) >= ZERO;
    }

    // << operator
    ostream& operator<<(ostream& os, const NumberWithUnits& unit_num) {
        os << unit_num.getValue() << '[' << unit_num.getUnit() << ']';
        return os;
    }


    /** Input and Output Stream operators **/
    // >> operator
    istream& operator>>(istream& is, NumberWithUnits& unit_num) {

        double value = 0;
        string unit;
        char ch = ']';

        is >> value >> ch;

        while(ch != ']') {
            if(ch != '[') {
                unit.insert(unit.end(), ch);
            }
            is >> ch;
        }

        if(hmap.empty()) {
            throw std::invalid_argument("units don't match");
        }

        hmap.at(unit);

        if(hmap[unit][unit] == 0 && unit != unit) {
            throw std::invalid_argument("types cannot match " + unit + " != " + unit);
        }

        unit_num.value = value;
        unit_num.unit = unit;
        return is;
    }

}