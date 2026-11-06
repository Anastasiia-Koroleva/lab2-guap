#include "Train.h"

Train::Train() : destination_("Неизвестно"), trainNumber_(0), departureTime_("00:00") {
    std::cout << "Train: конструктор по умолчанию\n";
}

Train::Train(const std::string& destination, int trainNumber, const std::string& departureTime)
    : destination_(destination), trainNumber_(trainNumber), departureTime_(departureTime) {
    std::cout << "Train: конструктор с параметрами (" << destination_ << ")\n";
}

Train::Train(const Train& other)
    : destination_(other.destination_), trainNumber_(other.trainNumber_), departureTime_(other.departureTime_) {
    std::cout << "Train: конструктор копирования (" << destination_ << ")\n";
}

Train::~Train() {
    std::cout << "Train: деструктор (" << destination_ << ")\n";
}

void Train::setDestination(const std::string& dest) { destination_ = dest; }
void Train::setTrainNumber(int num) { trainNumber_ = num; }
void Train::setDepartureTime(const std::string& time) { departureTime_ = time; }

std::ostream& operator<<(std::ostream& out, const Train& t) {
    out << "Поезд №" << t.trainNumber_ 
        << " | Направление: " << t.destination_ 
        << " | Время отправления: " << t.departureTime_;
    return out;
}

std::istream& operator>>(std::istream& in, Train& t) {
    std::cout << "Введите пункт назначения: ";
    in >> t.destination_;
    std::cout << "Введите номер поезда: ";
    in >> t.trainNumber_;
    std::cout << "Введите время отправления (чч:мм): ";
    in >> t.departureTime_;
    return in;
}