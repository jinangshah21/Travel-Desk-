#include <iostream>
#include <vector>
#include <map>

class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

// This Class creates a Tree for given Destination and pickup Location object
class TransportService
{
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead() const
    {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    void addTrip(int key, Trip *trip)
    {
        BinaryTreeNode *a = this->BSThead;
        BinaryTreeNode *prev = NULL;
        if (a == NULL)
        {
            BinaryTreeNode *newnode = new BinaryTreeNode(key, trip, NULL);
            this->setBSTHead(newnode);
            this->BSThead->setTripNodePtr(trip);
            this->BSThead->setDepartureTime(key);
            return;
        }
        while (a != NULL)
        {
            prev = a;
            if (key < a->getDepartureTime())
                a = a->getLeftPtr();
            else if (key == a->getDepartureTime())
                break;
            else
                a = a->getRightPtr();
        }
        BinaryTreeNode *newnode = new BinaryTreeNode(key, trip, prev);
        if (prev->getDepartureTime() > key)
            prev->setLeftPtr(newnode);
        else if (prev->getDepartureTime() == key)
        {
            newnode->setLeftPtr(prev->getLeftPtr());
            prev->getLeftPtr()->setParentPtr(newnode);
            prev->setLeftPtr(newnode);
        }
        else
            prev->setRightPtr(newnode);
    }

private:
    std::string name;
    BinaryTreeNode *BSThead;
};


class Vehicle
{
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number)
    {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }
    const std::vector<Trip *> &getTrips() const
    {
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

// this class is used to maintain each locations trips data
class Location
{
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    TransportService *getServicePtr(std::string droplocation) const
    {
        int i = 0, k = 0;
        for (i = 0; i < serviceptrs.size(); i++)
        {
            if (droplocation == serviceptrs[i]->getName())
            {
                k = 1;
                break;
            }
        }
        if (k == 0)
            return nullptr;
        else
            return serviceptrs[i];
    }

    // Setter functions
    void setName(std::string location_name)
    {
        name = location_name;
    }

    TransportService *setServicePtr(std::string droplocation)
    {
        int k = 0, i = 0;
        for (i = 0; i < serviceptrs.size(); i++)
        {
            if (serviceptrs[i]->getName() == droplocation)
            {
                k = 1;
                break;
            }
        }
        if (k == 0)
        {
            TransportService *newsrvc = new TransportService(droplocation);
            serviceptrs.push_back(newsrvc);
        }
        return nullptr;
    }

    void addTrip(Trip *trip)
    {

        if (trip->getPickUpLocation() != this->name)
        {
            return;
        }
        else
        {
            int i = 0;
            while (i != trips.size())
            {
                if (trip->getVehicle()->getVehicleNumber() == trips[i]->getVehicle()->getVehicleNumber() && trip->getDepartureTime() == trips[i]->getDepartureTime())
                    return;
                i++;
            }
            this->trips.push_back(trip);
            for (i = 0; i < serviceptrs.size(); i++)
            {
                if (serviceptrs[i]->getName() == trip->getDropLocation())
                    break;
            }
            serviceptrs[i]->addTrip(trip->getDepartureTime(), trip);
        }
    }
    std::vector<TransportService *> serviceptrs;

private:
    std::string name;
    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const
    {
        BinaryTreeNode *c = this->root;
        if (this->root == NULL)
            return 0;

        else
        {
            BinaryTree a;
            BinaryTree b;
            a.root = c->getLeftPtr();
            b.root = c->getRightPtr();
            return 1 + std::max(a.getHeight(), b.getHeight());
        }
    }

    int getNumberOfNodes() const
    {
        BinaryTreeNode *c = this->root;
        if (this->root == NULL)
            return 0;

        else
        {
            BinaryTree a;
            BinaryTree b;
            a.root = c->getLeftPtr();
            b.root = c->getRightPtr();
            return 1 + a.getNumberOfNodes() + b.getNumberOfNodes();
        }
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        BinaryTreeNode *a = this->root;
        if (a == NULL)
            return NULL;
        while (a->getLeftPtr() != NULL)
        {
            a = a->getLeftPtr();
        }
        return a;
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        BinaryTreeNode *a = this->root;
        if (a == NULL)
            return NULL;
        while (a->getRightPtr() != NULL)
        {
            a = a->getRightPtr();
        }
        return a;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // return this will find the node with the given key (if it exists) or find the node with the key just larger than the given key k.
        BinaryTreeNode *a = this->root;
        while (a != NULL)
        {
            if (a->getTripNodePtr()->getDepartureTime() > key) a = a->getLeftPtr();
            else if (a->getTripNodePtr()->getDepartureTime() == key) return a;
            else a = a->getRightPtr();
        }
        return NULL;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        if(node==NULL) return NULL;
        BinaryTreeNode *a = node->getRightPtr();
        if(a==NULL){
            if(a->getParentPtr()->getParentPtr()->getRightPtr()==a->getParentPtr()) return NULL;
            else return a->getParentPtr()->getParentPtr();
        }
        while(a->getLeftPtr()!=NULL) a=a->getLeftPtr();
        return a;
    }
    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        BinaryTreeNode *a = this->searchNodeWithKey(key);
       return this->getSuccessorNode(a);
    }
    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
         if(node==NULL) return NULL;
        BinaryTreeNode *a = node->getLeftPtr();
        if(a==NULL){
            if(a->getParentPtr()->getParentPtr()->getRightPtr()==a->getParentPtr()) return a->getParentPtr()->getParentPtr();
            else return NULL;
        }
        while(a->getRightPtr()!=NULL) a=a->getRightPtr();
        return a;
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        BinaryTreeNode *a = this->searchNodeWithKey(key);
        return this->getPredecessorNode(a);
    }
};

class TravelDesk
{
public:
    // Adding a trip with Given Information
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        int i = 0, k = 0;
        Vehicle *vehicle = nullptr;
        while (i != vehicles.size())
        {
            if (vehicles[i]->getVehicleNumber() == vehicle_number)
            {
                vehicle = vehicles[i];
                k = 1;
                break;
            }
            else
                i++;
        }
        if (k == 0)
        {
            vehicle = new Vehicle(vehicle_number, seating_capacity);
            vehicles.push_back(vehicle);
        }
        k = 0;
        const std::vector<Trip *> temp = vehicle->getTrips();
        for (i = 0; i < temp.size(); i++)
        {
            if (temp[i]->getDepartureTime() == departure_time)
            {
                k = 1;
                break;
            }
        }
        if (k == 0)
        {
            Trip *newtrip = new Trip(vehicle, pick_up_location, drop_location, departure_time);
            vehicle->addTrip(newtrip);
            k = 0;
            for (i = 0; i < locations.size(); i++)
            {
                // locations[i]->addTrip(newtrip);
                if (locations[i]->getName() == pick_up_location)
                {
                    k = 1;
                    break;
                }
            }
            if (k == 0)
            {
                Location *newloc = new Location(pick_up_location);
                locations.push_back(newloc);
                newloc->setServicePtr(drop_location);
                newloc->addTrip(newtrip);
            }
            else
            {
                locations[i]->setServicePtr(drop_location);
                locations[i]->addTrip(newtrip);
            }

        }
    }
    
    // Filter Trips By pickup location and after,before times
    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {
        int i, j;
        for (i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
                break;
        }
        std::vector<Trip *> tr;
        if (i == locations.size())
            return tr;

        for (j = 0; j < (locations[i]->serviceptrs).size(); j++)
        {
            BinaryTreeNode *iter = (locations[i]->serviceptrs[j])->getBSTHead();

            std::vector<Trip *> temp = show(iter, after_time, before_time);
            for (int a = 0; a < temp.size(); a++)
            {
                int count = 0;
                for (int c = 0; c < tr.size(); c++)
                {
                    if (temp[a]->getDepartureTime() == tr[c]->getDepartureTime())
                    {
                        if (temp[a]->getDropLocation() == tr[c]->getDropLocation())
                            count = 1;
                    }
                }
                if (count == 0)
                    tr.push_back(temp[a]);
            }
        }

        return tr;
    }
 
    // filter trips by given pickup, drop location and after, before time
    std::vector<Trip *> showTripsbydestination(std::string pick_up_location, std::string destination, int after_time, int before_time)
    {
        int i;
        for (i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
                break;
        }
        std::vector<Trip *> tr;
        TransportService *service = locations[i]->getServicePtr(destination);
        BinaryTreeNode *iter = service->getBSTHead();
        std::vector<Trip *> temp = show(iter, after_time, before_time);
        for (int a = 0; a < temp.size(); a++)
        {
            int count = 0;
            for (int c = 0; c < tr.size(); c++)
            {
                if (temp[a]->getDepartureTime() == tr[c]->getDepartureTime())
                {
                    if (temp[a]->getDropLocation() == tr[c]->getDropLocation())
                        count = 1;
                }
            }
            if (count == 0)
                tr.push_back(temp[a]);
        }
        return tr;
    }

    // Function to filter out trips Between after time and before time
    std::vector<Trip *> show(BinaryTreeNode *iter, int after, int before)
    {
        static std::vector<Trip *> tr;
        if (iter == NULL)
            return tr;
        else
        {
            show(iter->getLeftPtr(), after, before);
            // std::cout<<iter->getDepartureTime()<<" ";
            if (iter->getDepartureTime() >= after && iter->getDepartureTime() < before)
            {
                tr.push_back(iter->getTripNodePtr());
            }
            show(iter->getRightPtr(), after, before);
        }
        // std::cout<<tr.size()<<" ";
        return tr;
    }

    // Booking Trip 
    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        int i = 0, j = 0;
        for (i = 0; i < vehicles.size(); i++)
        {
            if (vehicles[i]->getVehicleNumber() == vehicle_number)
                break;
        }
        std::vector<Trip *> temp = vehicles[i]->getTrips();
        for (j = 0; j < temp.size(); j++)
        {
            if (temp[j]->getDepartureTime() == departure_time && temp[j]->getPickUpLocation() == pick_up_location)
                break;
        }
        if (vehicles[i]->getSeatingCapacity()-1 == temp[j]->getBookedSeats())   
            return nullptr;
        else
        {
            temp[j]->setBookedSeats(temp[j]->getBookedSeats() + 1);
            return temp[j];
        }
        return nullptr;
    }



    // Function to get Pick-up Location Pointer
    Location *getLocation(std::string location)
    {
        for (int i = 0; i < locations.size(); i++)
        {
            if (location == locations[i]->getName())
                return locations[i];
        }
        return nullptr;
    }

private:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;
};
