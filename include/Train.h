#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Train {
private:
    std::string destination_;  
    int trainNumber_;           
    std::string departureTime_; 

public:
    Train();
    Train(const std::string& destination, int trainNumber, const std::string& departureTime);
    Train(const Train& other);
    ~Train();

    void setDestination(const std::string& dest);
    void setTrainNumber(int num);
    void setDepartureTime(const std::string& time);

    std::string getDestination() const { return destination_; }
    int getTrainNumber() const { return trainNumber_; }
    std::string getDepartureTime() const { return departureTime_; }

    friend std::ostream& operator<<(std::ostream& out, const Train& t);
    friend std::istream& operator>>(std::istream& in, Train& t);
};