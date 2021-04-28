/**
 * NumberWithUnits Assignment
 * C++ Course @Ariel_University
 * 
 * Author: Jordan Perez
 * https://www.github.com/jewgah
 * 
 * */


#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace ariel {

    const int ZERO = 0;
    const int ONE = 1;
    const double TOLERANCE = 0.00001;

    class NumberWithUnits {

        private:
            double value;
            string unit;

        public:
            //constructor
            NumberWithUnits(double value, const string& unit);

            //default constructor
            NumberWithUnits() {}

            //deconstructor
            ~NumberWithUnits() {}

            //Setters
            void setValue(double val);
            void setUnit(string val);

            //Getters
            double getValue() const;
            string getUnit() const;

            //read_units method
            static void read_units(ifstream& file);

            //operators
            friend NumberWithUnits operator+(const NumberWithUnits& unit_num); // + operator
            friend NumberWithUnits operator+(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2); // + operator
            NumberWithUnits &operator++(); // ++ operator
            NumberWithUnits operator++(int); // ++ operator
            NumberWithUnits &operator+=(const NumberWithUnits& unit_num_1); // += operator
            friend NumberWithUnits operator-(const NumberWithUnits& unit_num);// - operator
            friend NumberWithUnits operator-(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2);// - operator
            NumberWithUnits &operator--(); // -- operator
            NumberWithUnits operator--(int); // -- operator
            NumberWithUnits &operator-=(const NumberWithUnits& unit_num_1); // -= operator
            friend NumberWithUnits operator*(const NumberWithUnits& unit_num, double number); // * operator
            friend NumberWithUnits operator*(double num, const NumberWithUnits& unit_num); // * operator
            friend NumberWithUnits operator*=(NumberWithUnits& unit_num, double number); // *= operator
            friend NumberWithUnits operator*=(double number, NumberWithUnits& unit_num); // *= operator

            //operators to compare
            friend bool operator==(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2); // == operator
            friend bool operator!=(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2); // != operator
            friend bool operator<(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2); // < operator
            friend bool operator<=(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2); // <= operator
            friend bool operator>(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2); // > operators
            friend bool operator>=(const NumberWithUnits& unit_num_1, const NumberWithUnits& unit_num_2); // >= operator

            //input and output operators
            friend istream& operator>>(istream& is, NumberWithUnits& unit_num); // >> operator
            friend ostream& operator<<(ostream& os, const NumberWithUnits& unit_num); // << operator


    };
}
