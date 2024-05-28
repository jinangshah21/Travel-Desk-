#include<bits/stdc++.h>
using namespace std::literals::chrono_literals;
using namespace std;
class Trip;
class node{
private:
    node* left,* right,* parent; bool isred; int index;int departuretime;
    Trip *tripnodeptr;
public:
      node *getLeftPtr() const
    {
        return left;
    }

    node *getRightPtr() const
    {
        return right;
    }

    node *getParentPtr() const
    {
        return parent;
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
    void setLeftPtr(node *left)
    {
        left = left;
    }

    void setRightPtr(node *right)
    {
        right = right;
    }

    void setParentPtr(node *parent)
    {
        parent = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }
	node(int departuretime = 0, Trip *tripenodeptr = nullptr, node *parentptr = nullptr,bool red = true)
        : left(nullptr), right(nullptr), parent(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr), isred(red) {}

	// node(std::string name, int indexval, bool red = true,node* p=nullptr){
	// 	value = name;
	// 	left = nullptr; right = nullptr;
	// 	isred = red;
	// 	parent = p;
	// 	index = indexval;
	// }
	// int get_index(){
	// 	return index;
	// }
	friend class redblack_tree;
};

class redblack_tree{
private:
	node* root;
	node* getuncle(node* child){
		if (child->parent->parent->right == child->parent) return child->parent->parent->left;
		return child->parent->parent->right;
	}
	
	int left_rotate(node* address){
		node* rightchild = address->right;
		node* parents = address->parent;
		address->right = rightchild->left;
		if (address->right!=nullptr){address->right->parent = address;}
		rightchild->left = address;
		address->parent = rightchild;

		rightchild->parent = parents;
		if (parents==nullptr){root = rightchild;}
		else if (parents->left==address){parents->left = rightchild;}
		else if (parents->right==address){parents->right = rightchild;}

		return 0;
	}
	int right_rotate(node* address){
		node* leftchild = address->left;
		node* parents = address->parent;
		address->left = leftchild->right;
		if (leftchild->right!=nullptr){leftchild->right->parent = address;}
		leftchild->right = address;
		address->parent = leftchild;

		if (parents==nullptr){root = leftchild;leftchild->parent = nullptr;}
		else if (parents->left==address){parents->left = leftchild;leftchild->parent = parents;}
		else if (parents->right==address){parents->right = leftchild;leftchild->parent = parents;}

		return 0;
	}
	int correct(node* address){
		if (address==nullptr) return 0;
		node* uncle;
		while (address->parent->isred){
			uncle = getuncle(address);
			if (uncle!=nullptr and uncle->isred){
				uncle->isred = false;
				address->parent->isred = false;
				address->parent->parent->isred = true;
				address = address->parent->parent;
			}
			else{
				if (address->parent==address->parent->parent->left){
					if (address==address->parent->right){
						left_rotate(address->parent);
						address = address->left;
					}
					right_rotate(address->parent->parent);

					address->parent->isred = false; address->parent->right->isred = true;address->parent->left->isred = true;
					break;
				}
				else{
					if (address==address->parent->left){
						right_rotate(address->parent);
						address = address->right;
					}
					left_rotate(address->parent->parent);

					address->parent->isred = false; address->parent->left->isred = true;address->parent->right->isred = true;
					break;
				}
			}
			if (address==root) break;
		}
		root->isred = false;
		return 0;
	}

	int deletefix(node* dbparent,bool rights){
		while (dbparent!=nullptr){
			if (rights){
				if (dbparent->left->isred){
					dbparent->isred = true;
					dbparent->left->isred = false;
					right_rotate(dbparent);
				}
				else{
					if ((dbparent->left->left==nullptr or dbparent->left->left->isred==false) and (dbparent->left->right==nullptr or dbparent->left->right->isred==false)){
						dbparent->left->isred = true;
						if (dbparent!=root and dbparent->parent->left==dbparent){rights = false;}
						else if (dbparent!=root){rights = true;}
						if (dbparent->isred){dbparent->isred = false; return 0;}
						dbparent = dbparent->parent;
					}
					else{
						if (dbparent->left->left==nullptr or dbparent->left->left->isred==false){
							dbparent->left->isred = true; dbparent->left->right->isred = false;
							left_rotate(dbparent->left);
						}
						dbparent->left->isred = dbparent->isred;
						dbparent->isred = false;
						dbparent->left->left->isred = false;
						right_rotate(dbparent);
						dbparent = nullptr;
					}
				}
			}
			else{
				if (dbparent->right->isred){
					dbparent->isred = true;
					dbparent->right->isred = false;
					left_rotate(dbparent);
				}
				else{
					if ((dbparent->right->left==nullptr or dbparent->right->left->isred==false) and (dbparent->right->right==nullptr or dbparent->right->right->isred==false)){
						dbparent->right->isred = true;
						if (dbparent!=root and dbparent->parent->left==dbparent){rights = false;}
						else if (dbparent!=root){rights = true;}
						if (dbparent->isred){dbparent->isred = false; return 0;}
						dbparent = dbparent->parent;
					}
					else{
						if (dbparent->right->right==nullptr or dbparent->right->right->isred==false){
							dbparent->right->isred = true; dbparent->right->left->isred = false;
							right_rotate(dbparent->right);
						}
						dbparent->right->isred = dbparent->isred;
						dbparent->isred = false;
						dbparent->right->right->isred = false;
						left_rotate(dbparent);
						dbparent = nullptr;
					}
				}
			}
		}
		root->isred = false;
		return 0;
	}

	int prerec(node* ptr){
		if (ptr==nullptr) return 0;
		std::cout<<ptr->getDepartureTime()<<' ';
		if (ptr->isred) std::cout<<"R ";
		prerec(ptr->left);
		prerec(ptr->right);
		return 0;
	}
public:
	redblack_tree(){
		root = nullptr;
	}
	int insert(int depttime,Trip* trip){
		if (root==nullptr){root = new node(depttime, trip,nullptr,false); return 0;}
		node* temp = root;
		bool flag = true;
		while (flag){
			if (depttime>temp->getDepartureTime()){
				if (temp->right==nullptr){
					temp->right = new node(depttime,trip, temp,true);
					flag = false;
				}
				temp = temp->right;
			}	
			else if (depttime<temp->getDepartureTime()){
				if (temp->left==nullptr){
					temp->left = new node(depttime,trip, temp,true);
					flag = false;
				}
				temp = temp->left;
			}
			else return 0;
		}
		correct(temp);
		return 0;
	}
	node* search(int name){
		node* temp = root;
		while(temp!=nullptr){
			if (temp->getDepartureTime()==name){return temp;}
			else if (name>temp->getDepartureTime()) temp = temp->right;
			else temp = temp->left;
		}
		return nullptr;
	}

	int deletenode(int name){
		node* temp = root;
		bool rights=true;
		while(temp!=nullptr){
			if (name>temp->getDepartureTime()){
				temp = temp->right;
				rights = true;
			}
			else if (name<temp->getDepartureTime()){
				temp = temp->left;
				rights = false;
			}
			else{
				if (temp->left==nullptr and temp->right==nullptr and temp->isred){
					if (rights){temp->parent->right=nullptr;}
					else {temp->parent->left = nullptr;}
					delete temp; return 0;
				}
				if (temp->left==nullptr and temp->right==nullptr){
					if (rights){temp->parent->right=nullptr;}
					else{temp->parent->left=nullptr;}
					node* p = temp->parent;
					delete temp;
					return deletefix(p,rights);
				}
				else if (temp->left==nullptr){
					temp->setDepartureTime(temp->right->getDepartureTime());
					temp->index = temp->right->index;
					delete temp->right;
					temp->right = nullptr;
					return 0;
				}
				else if (temp->right==nullptr){
					temp->setDepartureTime(temp->left->getDepartureTime());
					temp->index = temp->left->index;
					delete temp->left;
					temp->left = nullptr;
					return 0;
				}
				else{
					node* temporary = temp->right;
					while (temporary->left!=nullptr){
						temporary = temporary->left;
					}
					temp->setDepartureTime(temporary->getDepartureTime());
					temp->index = temporary->index;
					if (temporary->right!=nullptr){
						temporary->setDepartureTime(temporary->right->getDepartureTime());
						temporary->index = temporary->right->index;
						delete temporary->right;
						temporary->right = nullptr;
						return 0;
					}
					if (temporary->isred){
						node* p = temporary->parent;
						delete temporary;
						if (p==temp) p->right = nullptr;
						else p->left = nullptr;
						return 0;
					}
					if (temporary->parent==temp){
						temp->right = nullptr;
						delete temporary;
						deletefix(temp,true);
					}
					else{
						temporary->parent->left = nullptr;
						node* p = temporary->parent;
						delete temporary;
						deletefix(p,false);
					}
					return 0;
				}
			}
		}
		return 0;
	}

	node* getRoot(){
		return this->root;
	}
	void setRoot(node*Node){
		this->root=Node;
	}

	int preorder(){
		prerec(root); std::cout<<'\n';
		return 0;
	}
};

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

// This Class creates a Tree for given Destination and pickup Location object
class TransportService
{
public:
    TransportService(std::string name) : name(name), rbt(new redblack_tree()) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    redblack_tree *getRBT() const
    {
        return rbt;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setRBT(redblack_tree* newrbt)
    {
        this->rbt=newrbt;
    }

    void addTrip(int key, Trip *trip)
    {
		rbt->insert(key,trip);

        // node *a = this->BSThead;
        // node *prev = NULL;
        // if (a == NULL)
        // {
        //     BinaryTreeNode *newnode = new node(key, trip, NULL);
        //     this->setBSTHead(newnode);
        //     this->BSThead->setTripNodePtr(trip);
        //     this->BSThead->setDepartureTime(key);
        //     return;
        // }
        // while (a != NULL)
        // {
        //     prev = a;
        //     if (key < a->getDepartureTime())
        //         a = a->getLeftPtr();
        //     else if (key == a->getDepartureTime())
        //         break;
        //     else
        //         a = a->getRightPtr();
        // }
        // BinaryTreeNode *newnode = new BinaryTreeNode(key, trip, prev);
        // if (prev->getDepartureTime() > key)
        //     prev->setLeftPtr(newnode);
        // else if (prev->getDepartureTime() == key)
        // {
        //     newnode->setLeftPtr(prev->getLeftPtr());
        //     prev->getLeftPtr()->setParentPtr(newnode);
        //     prev->setLeftPtr(newnode);
        // }
        // else
        //     prev->setRightPtr(newnode);
    }

private:
    std::string name;
    redblack_tree *rbt;
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
            node *iter = (locations[i]->serviceptrs[j])->getRBT()->getRoot();

            
			 show(iter, after_time, before_time,tr);
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
        std::vector<Trip *> temp;
        if(i==locations.size()) return temp;
        TransportService *service = locations[i]->getServicePtr(destination);
		if(service==nullptr) return temp;
        node *iter = service->getRBT()->getRoot();
		show(iter, after_time, before_time,temp);
        return temp;
    }

    // Function to filter out trips Between after time and before time
    void show(node *iter, int after, int before, vector<Trip *>& tr)
    {
        if (iter == NULL)
            return;
        else
        {
            show(iter->getLeftPtr(), after, before,tr);
            // std::cout<<iter->getDepartureTime()<<" ";
            if (iter->getDepartureTime() >= after && iter->getDepartureTime() < before)
            {
                tr.push_back(iter->getTripNodePtr());
            }
            show(iter->getRightPtr(), after, before,tr);
        }
        // std::cout<<tr.size()<<" ";
    }

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
