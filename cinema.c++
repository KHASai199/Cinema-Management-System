#include <iostream>
#include <string>
using namespace std;

const int MAX_TICKETS = 100;

class Person
{
protected:
    string name;

public:
    Person() {}
    Person(string n) { name = n; }

    void setName(string n) { name = n; }

    void setName()
    {
        cout << "Enter name: ";
        getline(cin, name);
    }

    string getName() { return name; }
};

class Customer : public Person
{
public:
    Customer() {}
    Customer(string n) : Person(n) {}
};

class MovieNode
{
public:
    string movieName;
    MovieNode *next;

    MovieNode(string name)
    {
        movieName = name;
        next = NULL;
    }
};

class MovieList
{
private:
    MovieNode *head;

public:
    MovieList()
    {
        head = NULL;
    }

    void addMovie(string name)
    {
        MovieNode *newNode = new MovieNode(name);
        newNode->next = head;
        head = newNode;
    }

    void displayMovies()
    {
        cout << "\n=== Available Movies ===\n";
        MovieNode *temp = head;
        int index = 1;

        while (temp != NULL)
        {
            cout << index << ". " << temp->movieName << endl;
            temp = temp->next;
            index++;
        }
    }

    string getMovieByNumber(int n)
    {
        MovieNode *temp = head;
        int index = 1;

        while (temp != NULL)
        {
            if (index == n)
                return temp->movieName;

            temp = temp->next;
            index++;
        }

        return "";
    }
};

class NodeQ
{
public:
    string name;
    NodeQ *next;

    NodeQ(string n)
    {
        name = n;
        next = NULL;
    }
};

class Queue
{
private:
    NodeQ *front;
    NodeQ *rear;

public:
    Queue()
    {
        front = rear = NULL;
    }

    bool isEmpty() { return front == NULL; }

    void enqueue(string name)
    {
        NodeQ *newNode = new NodeQ(name);
        if (rear == NULL)
        {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    string dequeue()
    {
        if (isEmpty())
            return "";

        NodeQ *temp = front;
        string name = temp->name;

        front = front->next;
        if (front == NULL)
            rear = NULL;

        delete temp;
        return name;
    }

    void display()
    {
        cout << "\n=== Waiting List ===\n";
        if (isEmpty())
        {
            cout << "No customers waiting.\n";
            return;
        }

        NodeQ *curr = front;
        while (curr != NULL)
        {
            cout << curr->name << endl;
            curr = curr->next;
        }
    }
};

class Ticket
{
public:
    Customer customer;
    string movieName;
    int seatNumber;
    bool isBooked;

    Ticket()
    {
        isBooked = false;
    }
};

class BookingSystem
{
private:
    Ticket tickets[MAX_TICKETS];
    int ticketCount;

    Queue waitingList;
    MovieList movieList;

public:
    BookingSystem()
    {
        ticketCount = 0;

        movieList.addMovie("Avatar 2");
        movieList.addMovie("Spider-Man");
        movieList.addMovie("The Conjuring");
        movieList.addMovie("Fast & Furious 10");
    }

    void bookTicket()
    {
        if (ticketCount >= MAX_TICKETS)
        {
            cin.ignore();
            Customer c;
            c.setName();
            waitingList.enqueue(c.getName());
            cout << "All seats full. Customer added to waiting list.\n";
            return;
        }

        int seatNumber;
        int movieChoice;
        cin.ignore();

        Customer customer;
        customer.setName();

        movieList.displayMovies();
        cout << "Choose movie number: ";
        cin >> movieChoice;

        string movieName = movieList.getMovieByNumber(movieChoice);
        if (movieName == "")
        {
            cout << "Invalid movie.\n";
            return;
        }

        cout << "Enter seat number (1-" << MAX_TICKETS << "): ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > MAX_TICKETS || tickets[seatNumber - 1].isBooked)
        {
            cout << "Invalid or already booked seat.\n";
            return;
        }

        tickets[seatNumber - 1].customer = customer;
        tickets[seatNumber - 1].movieName = movieName;
        tickets[seatNumber - 1].seatNumber = seatNumber;
        tickets[seatNumber - 1].isBooked = true;

        ticketCount++;

        cout << "Ticket booked successfully!\n";
    }

    void cancelTicket()
    {
        int seatNumber;
        cout << "Enter seat number to cancel: ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > MAX_TICKETS || !tickets[seatNumber - 1].isBooked)
        {
            cout << "Seat not found or not booked.\n";
            return;
        }

        tickets[seatNumber - 1].isBooked = false;
        ticketCount--;

        cout << "Ticket cancelled.\n";

        if (!waitingList.isEmpty())
        {
            string nextCustomer = waitingList.dequeue();

            tickets[seatNumber - 1].customer.setName(nextCustomer);
            tickets[seatNumber - 1].movieName = "Auto Assigned";
            tickets[seatNumber - 1].isBooked = true;

            ticketCount++;

            cout << "Seat assigned automatically to waiting customer: "
                 << nextCustomer << endl;
        }
    }
    void displayTickets()
    {
        cout << "\n=== Booked Tickets ===\n";
        bool found = false;

        for (int i = 0; i < MAX_TICKETS; i++)
        {
            if (tickets[i].isBooked)
            {
                found = true;
                cout << "Seat: " << tickets[i].seatNumber
                     << ", Name: " << tickets[i].customer.getName()
                     << ", Movie: " << tickets[i].movieName << endl;
            }
        }

        if (!found)
            cout << "No tickets booked.\n";
    }
    void showTicketDetails()
    {
        int seatNumber;
        cout << "Enter seat number: ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > MAX_TICKETS ||
            !tickets[seatNumber - 1].isBooked)
        {
            cout << "Seat not found or not booked.\n";
            return;
        }

        Ticket t = tickets[seatNumber - 1];

        cout << "Customer: " << t.customer.getName() << endl;
        cout << "Movie: " << t.movieName << endl;
        cout << "Seat: " << t.seatNumber << endl;
    }
    void revenue()
    {
        cout << "Total revenue: " << ticketCount * 50 << " EGP\n";
    }
    void countBookedTickets()
    {
        cout << "Total booked tickets: " << ticketCount << endl;
    }
    void showWaitingList()
    {
        waitingList.display();
    }
};
int main()
{
    BookingSystem system;
    int choice;

    do
    {
        cout << "\n=== Cinema Ticket Booking ===\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Display All Tickets\n";
        cout << "4. Show Ticket Details\n";
        cout << "5. Show Revenue\n";
        cout << "6. Count Booked Tickets\n";
        cout << "7. Show Waiting List\n";
        cout << "8. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.bookTicket();
            break;
        case 2:
            system.cancelTicket();
            break;
        case 3:
            system.displayTickets();
            break;
        case 4:
            system.showTicketDetails();
            break;
        case 5:
            system.revenue();
            break;
        case 6:
            system.countBookedTickets();
            break;
        case 7:
            system.showWaitingList();
            break;
        case 8:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}
