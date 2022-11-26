// Middle_1_module_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>


class Vehicle
{
public:
    Vehicle()= default;
    virtual ~Vehicle()= default;

    virtual std::ostream& print(std::ostream& _out) = 0;

    friend std::ostream& operator<<(std::ostream& _out, Vehicle& _vehicle)
    {
        return _vehicle.print(_out);
    };
};


class WaterVehicle : virtual public Vehicle
{
public:
    explicit WaterVehicle(float _draft){
        Draft = _draft;
    };

    std::ostream& print(std::ostream& _out) override
    {
        _out << "Draft: " << Draft;
        return _out;
    }

private:
    float Draft{0.0f};
};


class RoadVehicle : virtual public Vehicle
{
public:
    explicit RoadVehicle(float _groundClearance){
        GroundClearance = _groundClearance;
    };

    std::ostream& print(std::ostream& _out) override
    {
        _out << "Ride height: " << GroundClearance;
        return _out;
    }
private:
    float GroundClearance{0.0f};
};


class Point
{
public:
    Point(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    friend std::ostream& operator<<(std::ostream& out, const Point& v)
    {
        out << "x=" << v.x << " ";
        out << "y=" << v.y << " ";
        out << "z=" << v.z << " ";
        return out;
    }

private:
    float x{0};
    float y{0};
    float z{0};
};


class Circle : public WaterVehicle
{
public:
    Point CirclePoint{0, 0, 0};
    Circle(Point _circlePoint, float _draft): WaterVehicle(_draft), Vehicle() {
        CirclePoint = _circlePoint;
    };

    std::ostream& print(std::ostream& _out) override
    {
        _out << "Circle " << CirclePoint << " ";
        return WaterVehicle::print(_out);
    }
};


class Wheel
{
public:
    explicit Wheel(float _diametr)
    {
        Diameter = _diametr;
    };

    float GetDiametr() const
    {
        return Diameter;
    }

private:
    float Diameter{0.0f};
};


class Engine
{
public:

    explicit Engine(float _power)
    {
        Power = _power;
    };

    float GetPower() const
    {
        return Power;
    }
private:
    float Power = 0.0f;
};


class Bicycle : public RoadVehicle
{
public:
    Wheel ForwardWheel{0};
    Wheel BackWheel{0};

    Bicycle(Wheel _forwardWheel,
            Wheel _backWheel,
            float _groundClearance) : RoadVehicle(_groundClearance), Vehicle()
    {
        ForwardWheel = _forwardWheel;
        BackWheel = _backWheel;
    }

    std::ostream &print(std::ostream &_out) override {
        _out << "Bicycle Wheels: ";
        _out << ForwardWheel.GetDiametr() << " ";
        _out << BackWheel.GetDiametr() << " ";
        return RoadVehicle::print(_out);
    };

};


class Car : public RoadVehicle
{
public:
    Engine CarEngine{0};
    Wheel ForwardWheelLeft{0};
    Wheel ForwardWheelRight{0};
    Wheel BackWheelLeft{0};
    Wheel BackWheelRight{0};

    Car(Engine _carEngine,
        Wheel _forwardWheelLeft,
        Wheel _forwardWheelRight,
        Wheel _backWheelLeft,
        Wheel _backWheelRight,
        float _groundClearance) : RoadVehicle(_groundClearance), Vehicle()
    {
        CarEngine = _carEngine;
        ForwardWheelLeft = _forwardWheelLeft;
        ForwardWheelRight = _forwardWheelRight;
        BackWheelLeft = _backWheelLeft;
        BackWheelRight = _backWheelRight;
    };

    std::ostream &print(std::ostream &_out) override
    {
        _out << "Car ";
        _out << "Engine: " << CarEngine.GetPower() << " ";
        _out << "Wheels: ";
        _out << ForwardWheelLeft.GetDiametr() << " ";
        _out << ForwardWheelRight.GetDiametr() << " ";
        _out << BackWheelLeft.GetDiametr() << " ";
        _out << BackWheelRight.GetDiametr() << " ";
        return RoadVehicle::print(_out);
    };

};


Car& getHighestPower(const std::vector<Vehicle*>& AllVehicle)
{
    Car* MaxPowerVehicle;
    float MaxPower = 0.0f;
    for(Vehicle* OneVehicle: AllVehicle)
    {
        Car* CarVehicle = dynamic_cast<Car*>(OneVehicle);
        if (CarVehicle){
            float CurrentCarPower = CarVehicle->CarEngine.GetPower();
            if (CurrentCarPower >= MaxPower)
            {
                MaxPower = CurrentCarPower;
                MaxPowerVehicle = CarVehicle;
            }
        }
    }
    return *MaxPowerVehicle;
}


int main()
{
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
    std::cout << c << '\n';

    Bicycle t(Wheel(20), Wheel(20), 300);
    std::cout << t << '\n';


    std::vector<Vehicle*> v;

    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));

    v.push_back(new Circle(Point(1, 2, 3), 7));

    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));

    v.push_back(new WaterVehicle(5000));

    for (Vehicle* one_vehicle : v)
    {
        if(one_vehicle)
            std::cout << *one_vehicle << std::endl;
    }


    //TODO: Вывод элементов вектора v здесь
    std::cout << "The highest power is " << getHighestPower(v) << '\n'; // реализуйте эту функцию

    //TODO: Удаление элементов вектора v здесь
    for (Vehicle* one_vehicle : v)
        delete one_vehicle;

    v.clear();

};
