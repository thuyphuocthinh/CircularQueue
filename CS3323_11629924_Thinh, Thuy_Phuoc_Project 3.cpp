// Troy ID: 11629924
// Full name: Thinh, Thuy Phuoc

#include <bits/stdc++.h>

// Shooter Class
class Shooter
{
public:
    Shooter() {}
    Shooter(std::string name, int bulletCount)
    {
        this->name = name;
        this->bulletCount = bulletCount;
        this->initialBulletCount = bulletCount;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    std::string getName()
    {
        return name;
    }

    void setBulletCount(int bulletCount)
    {
        this->bulletCount = bulletCount;
    }

    int getBulletCount()
    {
        return bulletCount;
    }

    void setInitialBulletCount(int initialBulletCount)
    {
        this->initialBulletCount = initialBulletCount;
    }

    int getInitialBulletCount()
    {
        return initialBulletCount;
    }

    void shooting()
    {
        if (bulletCount > 0)
            bulletCount--;
    }

    int getQuantity()
    {
        return bulletCount;
    }

    void display()
    {
        std::cout << name << "'s remaining bullets is " << bulletCount << "\n";
    }

private:
    std::string name;
    int bulletCount;
    int initialBulletCount;
};

// Queue ADT
class QueType
{
public:
    QueType(int max)
    {
        maxQue = max + 1;
        front = maxQue - 1;
        rear = maxQue - 1;
        items = new Shooter[maxQue];
        length = 0;
    }
    QueType()
    {
        maxQue = 500;
        front = maxQue - 1;
        rear = maxQue - 1;
        items = new Shooter[maxQue];
        length = 0;
    }
    ~QueType()
    {
        delete[] items;
    }
    void MakeEmpty()
    {
        front = maxQue - 1;
        rear = maxQue - 1;
        length = 0;
    }
    bool IsEmpty() const
    {
        return (rear == front);
    }
    bool IsFull() const
    {
        return ((rear + 1) % maxQue == front);
    }
    void Enqueue(Shooter item)
    {
        if (IsFull())
            std::cout << "Queue is full"
                      << "\n";
        else
        {
            rear = (rear + 1) % maxQue;
            items[rear] = item;
            length++;
        }
    }
    void Dequeue(Shooter &item)
    {
        if (IsEmpty())
            std::cout << "Queue is empty"
                      << "\n";
        else
        {
            front = (front + 1) % maxQue;
            item = items[front];
            length--;
        }
    }
    int GetLength() const
    {
        return length;
    }

private:
    Shooter *items;
    int maxQue;
    int front;
    int rear;
    int length;
};

// App that provides interfaces to run the program
class App
{
public:
    App() {}
    // run method
    void run()
    {
        std::string inputFileName, outputFileName;
        std::cout << "Type in input file name (extension: .txt): ";
        std::cin >> inputFileName;
        std::cout << "Type in output file name (extension: .txt): ";
        std::cin >> outputFileName;
        std::ifstream inputFile(inputFileName);
        std::ofstream outputFile(outputFileName);
        std::cout << "Processing..." << "\n";
        // get input
        if (inputFile.is_open())
        {
            std::string name;
            int bullet;
            while (!inputFile.eof())
            {
                inputFile >> name >> bullet;
                Shooter shooter(name, bullet);
                shootingRange.Enqueue(shooter);
                outputFile << "Shooter: " << shooter.getName() << " " << "added to the queue. Remaining Bullets: " << shooter.getQuantity() << "\n";
            }
            outputFile << "--------------------------------------------------------------------" << "\n";
            inputFile.clear();
            inputFile.close();
        }

        // process
        while (!shootingRange.IsEmpty())
        {
            Shooter shooter;
            shootingRange.Dequeue(shooter);
            shooter.shooting();
            if (shooter.getQuantity() == 0)
            {
                outputFile << shooter.getName() << " " << "is completed!" << "\n";
            }
            else
            {
                outputFile << shooter.getName() << " " << "needs to shoot" << " " << shooter.getQuantity() << " " << "more bullets" << "\n";
                shootingRange.Enqueue(shooter);
                outputFile << shooter.getName() << " " << "was sent back to the queue. Remaining bullets: " << shooter.getQuantity() << "\n";
            }
        }

        std::cout << "Done" << "\n";
        std::cout << "Let's open the file " << outputFileName << " in the same directory to see the result." << "\n";
    }

private:
    QueType shootingRange;
};

int main()
{
    // create an app
    App app;
    // run the program
    app.run();
    return 0;
}