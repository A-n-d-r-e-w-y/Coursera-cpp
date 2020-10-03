#include <iostream>
#include "vector"
#include "algorithm"
#include "iterator"
#include <sstream>
#include "set"
#include "map"

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};


struct Person {
    int age = 0;  // возраст
    Gender gender = Gender::MALE;  // пол
    bool is_employed = false;  // имеет ли работу
};


template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
            begin(range_copy), middle, end(range_copy),
            [](const Person& lhs, const Person& rhs) {
                return lhs.age < rhs.age;
            }
    );
    return middle->age;
}


bool pred_female(const Person& p)
{
    return static_cast<Gender>(p.gender) == Gender::FEMALE;
}


bool pred_male(const Person& p)
{
    return static_cast<Gender>(p.gender) == Gender::MALE;
}


bool pred_employed_females(const Person& p)
{
    return static_cast<Gender>(p.gender) == Gender::FEMALE && p.is_employed;
}


bool pred_unemployed_females(const Person& p)
{
    return static_cast<Gender>(p.gender) == Gender::FEMALE && !p.is_employed;
}


bool pred_employed_males(const Person& p)
{
    return static_cast<Gender>(p.gender) == Gender::MALE && p.is_employed;
}


bool pred_unemployed_males(const Person& p)
{
    return static_cast<Gender>(p.gender) == Gender::MALE && !p.is_employed;
}


vector<Person> GetPersonsByCondition(const vector<Person>& persons, bool pred(const Person&))
{
    vector<Person> res;
    copy_if(begin(persons),
            end(persons),
            back_inserter(res),
            [pred](const Person& p){return pred(p);}
    );
    return res;
}





void PrintStats(vector<Person> persons)
{
    cout<<"Median age = "<<ComputeMedianAge(begin(persons), end(persons)) << endl;

    vector<Person> res = GetPersonsByCondition(persons, pred_female);
    cout<<"Median age for females = "<<ComputeMedianAge(begin(res), end(res)) << endl;

    res = GetPersonsByCondition(persons, pred_male);
    cout<<"Median age for males = "<<ComputeMedianAge(begin(res), end(res)) << endl;

    res = GetPersonsByCondition(persons, pred_employed_females);
    cout<<"Median age for employed females = "<<ComputeMedianAge(begin(res), end(res)) << endl;

    res = GetPersonsByCondition(persons, pred_unemployed_females);
    cout<<"Median age for unemployed females = "<<ComputeMedianAge(begin(res), end(res)) << endl;

    res = GetPersonsByCondition(persons, pred_employed_males);
    cout<<"Median age for employed males = "<<ComputeMedianAge(begin(res), end(res)) << endl;

    res = GetPersonsByCondition(persons, pred_unemployed_males);
    cout<<"Median age for unemployed males = "<<ComputeMedianAge(begin(res), end(res)) << endl;

}



int main() {

    vector<Person> persons = {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true},
    };
    PrintStats(persons);


    return 0;
}
