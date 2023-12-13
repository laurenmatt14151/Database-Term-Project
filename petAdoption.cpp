/*
Team: Pet Adoption
Group: Lauren Matthews, Alaisha Johnson, Joshua Douglas
*/
#include <stdlib.h>
#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

//Compile:
// g++ -I/usr/include petapp.cpp -o petapp -I /usr/local/lib -lmysqlcppconn
// 
// Execute:
// ./petapp
// 

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
sql::PreparedStatement *prep_stmt;

void addDog();
void addCustomer();
void findDogbyid();
void findCustomerbyid();
void findAdoptionRecord();
void findBreedInfo();
void showAllDogs();
void showAllCustomers();
void findall();
void deleteDog();
void UpdateDogAge();

int main(void) {
    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("petAdoption");

        int option = 1;

        while (option != 0) {
            cout << "\n1. Add a Dog"
                 << "\n2. Add a Customer"
                 << "\n3. Find a Dog by id"
                 << "\n4. Find a Customer by id"
                 << "\n5. Find Adoption Record by Customer id"
                 << "\n6. Find Breed info by Breed id"
                 << "\n7. Show all Dogs"
                 << "\n8. Show all Customers"
                 << "\n9. Show all"
                 << "\n10. Delete a Dog"
                 << "\n11. Update a Dog age"
                 << "\n0. Exit"
                 << "\n\nChoice: ";
            cin >> option;

            switch (option) {
                case 0:
                    cout << "Exiting program..." << endl;
                    return EXIT_SUCCESS;
                case 1:
                    addDog();
                    break;
                case 2:
                    addCustomer();
                    break;
                case 3:
                    findDogbyid();
                    break;
                case 4:
                    findCustomerbyid();
                    break;
                case 5:
                    findAdoptionRecord();
                    break;
                case 6:
                    findBreedInfo();
                    break;
                case 7:
                    showAllDogs();
                    break;
                case 8:
                    showAllCustomers();
                    break;
                case 9:
                    findall();
                    break;
                case 10:
                    deleteDog();
                    break;
                case 11:
                    UpdateDogAge();
                    break;
            }
        }
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    cout << endl;
    return EXIT_SUCCESS;
}



void findDogbyid() {
     
 
 int id;
    
 cout << "Enter the Dog ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Dog_Profile WHERE DogID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     cout << "DogId | BreedId | DogName | Age | Size | AvailableForAdoption | Dog_Description | " <<endl;
     cout << res->getString("DogId") << " | ";
     cout << res->getString("BreedId") << " | ";
     cout << res->getString("DogName") << " | ";
     cout << res->getString("Age") << " | ";
     cout << res->getString("Size") << " | ";
     cout << res->getString("AvailableForAdoption") << endl;
     cout << res->getString("Dog_Description") << endl;
 
 }
}
void findCustomerbyid() {
     
 
 int id;
    
 cout << "Enter the Customer ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Customer_Profile WHERE CustomerID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
 cout << "CustomerID | FirstName | LastName | PhoneNumber | Email | Cust_Address |" <<endl;    
     cout << res->getString("CustomerID") << " | ";
     cout << res->getString("FirstName") << " | ";
     cout << res->getString("LastName") << " | ";
     cout << res->getString("PhoneNumber") << " | ";
     cout << res->getString("Email") << endl;
     cout << res->getString("Cust_Address") << endl;
 }
     
 }

 void findAdoptionRecord(){    
 
 int id;
    
 cout << "Enter the Customer ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Adoption_Record WHERE CustomerID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
 cout << "AdoptionID | CustomerId | DogID | AdoptionDate |" <<endl;    
     cout << res->getString("AdoptionID") << " | ";
     cout << res->getString("CustomerId") << " | ";
     cout << res->getString("DogID") << " | ";
     cout << res->getString("AdoptionDate") << endl;
 }
 }


void UpdateDogAge(){ 
 
 int id;
 int age;
    
 cout << "Enter the Dog id : ";
 cin >> id;
 cout << "Enter the Dog  new Age : ";
 cin >> age;
    
 
prep_stmt = con->prepareStatement("UPDATE Dog_Profile SET Age = ? WHERE DogID = ?");
prep_stmt->setInt(1, age);
prep_stmt->setInt(2, id);
res = prep_stmt->executeQuery();

 cout << "Dog Age updated successfully ";
 }
 


void findBreedInfo(){ 
 
 int id;
    
 cout << "Enter the Breed ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Breed_Info WHERE BreedID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
 cout << "BreedID | BreedName | HairType | DiseasesProneTo " <<endl;    
     cout << res->getString("BreedID") << " | ";
     cout << res->getString("BreedName") << " | ";
     cout << res->getString("HairType") << " | ";
     cout << res->getString("DiseasesProneTo") << " | ";
 }
 }

void deleteDog(){ 
 
 int id;
    
 cout << "Enter the Dog ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("Delete FROM Dog_Profile WHERE DogID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();

 cout << "Dog Deleted Successfully ";


 }
 





void addDog(){ 
  string dogName, dogDescription, breedName, hairType, diseasesProneTo,  size, availableForAdoption;
    int age, breedID;

    cout << "Enter Dog Name: ";
    cin >> dogName;

    cout << "Enter Breed ID: ";
    cin >> breedID;

    cout << "Enter Dog Age: ";
    cin >> age;

    cout << "Enter Dog size: ";
    cin >> size;

    cout << "Is available For Adoption: ";
    cin >> availableForAdoption;

    cout << "Enter Dog description: ";
    cin >> dogDescription;
    getline(cin, dogDescription);



    prep_stmt = con->prepareStatement("INSERT INTO Dog_Profile (BreedID, DogName,Age,Size,AvailableForAdoption,Dog_Description) VALUES (?, ?, ?,?,?,?)");
    prep_stmt->setInt(1, breedID);
    prep_stmt->setString(2, dogName);
    prep_stmt->setInt(3, age);
    prep_stmt->setString(4, size);
    prep_stmt->setString(5, availableForAdoption);
    prep_stmt->setString(6, dogDescription);

    prep_stmt->executeUpdate();

    cout << "Dog added successfully!" << endl;
}

void addCustomer(){ 
string custFName, custLName, Email, Cust_Address;
int PhoneNumber;

    cout << "Enter first Name: ";
    cin >> custFName;

    cout << "Enter last name: ";
    cin >> custLName;

    cout << "Enter Phone Number: ";
    cin >> PhoneNumber;

    cout << "Enter email: ";
    cin >> Email;

    cout << "Enter Address: ";
    cin >> Cust_Address;


     
    prep_stmt = con->prepareStatement("INSERT INTO Customer_Profile (FirstName,LastName,PhoneNumber,Email,Cust_Address) VALUES (?,?,?,?,?)");
    prep_stmt->setString(1, custFName);
    prep_stmt->setString(2, custLName);
    prep_stmt->setInt(3, PhoneNumber);
    prep_stmt->setString(4, Email);
    prep_stmt->setString(5, Cust_Address);


    prep_stmt->executeUpdate();

    cout << "Customer added successfully!" << endl;
 
}


void showAllDogs(){  
 

prep_stmt = con->prepareStatement("SELECT * FROM Dog_Profile");

res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
cout << "DogId | BreedId | DogName | Age | Size | AvailableForAdoption | Dog_Description | " <<endl;     
     cout << res->getString("DogID") << " | ";
     cout << res->getString("BreedID") << " | ";
     cout << res->getString("DogName") << " | ";
     cout << res->getString("Age") << " | ";
     cout << res->getString("Size") << " | ";
     cout << res->getString("AvailableForAdoption") << " | ";
     cout << res->getString("Dog_Description") << endl;
 }
 }

void showAllCustomers(){   
 

prep_stmt = con->prepareStatement("SELECT * FROM Customer_Profile");

res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
 cout << "CustomerID | FirstName | LastName | PhoneNumber | Email | Cust_Address |" <<endl;    
     cout << res->getString("CustomerID") << " | ";
     cout << res->getString("Firstname") << " | ";
     cout << res->getString("LastName") << " | ";
     cout << res->getString("PhoneNumber") << " | ";
     cout << res->getString("Email") << " | ";
     cout << res->getString("Cust_Address") << endl;
 }
 }


void findall(){   
 prep_stmt = con->prepareStatement("SELECT Dog_Profile.DogID, Dog_Profile.BreedID, Dog_Profile.DogName, Dog_Profile.Age, Dog_Profile.Size, Dog_Profile.AvailableForAdoption, Dog_Profile.Dog_Description, Customer_Profile.CustomerID, Customer_Profile.FirstName, Customer_Profile.LastName, Customer_Profile.PhoneNumber, Customer_Profile.Email, Customer_Profile.Cust_Address FROM Dog_Profile JOIN Customer_Profile ON Dog_Profile.DogID = Customer_Profile.CustomerID");

res = prep_stmt->executeQuery();

while (res->next()) {

 /* Access column data by alias or column name */
 cout << "CustomerID | FirstName | LastName | PhoneNumber | Email | Cust_Address |" <<endl;    
     cout << res->getString("CustomerID") << " | ";
     cout << res->getString("Firstname") << " | ";
     cout << res->getString("LastName") << " | ";
     cout << res->getString("PhoneNumber") << " | ";
     cout << res->getString("Email") << " | ";
     cout << res->getString("Cust_Address") << endl;
     cout << "DogId | BreedId | DogName | Age | Size | AvailableForAdoption | Dog_Description | " <<endl;     
     cout << res->getString("DogID") << " | ";
     cout << res->getString("BreedID") << " | ";
     cout << res->getString("DogName") << " | ";
     cout << res->getString("Age") << " | ";
     cout << res->getString("Size") << " | ";
     cout << res->getString("AvailableForAdoption") << " | ";
     cout << res->getString("Dog_Description") << endl;
 }


//showAllCustomers();
//showAllDogs();


 }

















 
