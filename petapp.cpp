/*
Team: Pet Adoption
Group: Lauren Matthews, Alaisha Johnson, Joshua Douglas
*/
#include <stdlib.h>
#include <iostream>
#include <iomanip>
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
void updateDogAge();
void deleteDog();
void showAllDogs();
void showAllCustomers();
void findall();
void totalDogs();

int main(void) {
    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("petAdoption");

        int option = 1;

        while (option != 0) {
            cout << "\n------------------------------------------"
                 << "MENU"
                 << "------------------------------------------"
                 << "\n\n1. Add a Dog"
                 << "\n2. Add a Customer"
                 << "\n3. Find a Dog by id"
                 << "\n4. Find a Customer by id"
                 << "\n5. Find Adoption Record by Customer id"
                 << "\n6. Find Breed info by Breed id"
                 << "\n7. Update a dogs age"
                 << "\n8. Delete a dog"
                 << "\n9. Show all Dogs"
                 << "\n10. Show all Customers"
                 << "\n11. Show all"
                 << "\n12. Total dogs available for adoption"
                 << "\n0. Exit\n"
                 << "------------------------------------------"
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
                    updateDogAge();
                    break;
                case 8:
                    deleteDog();
                    break;
                case 9:
                    showAllDogs();
                    break;
                case 10:
                    showAllCustomers();
                    break;
                case 11:
                    findall();
                    break;
                case 12:
                    totalDogs();
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
//CASE 1
void addDog(){ 
  string dogName, dogDescription, breedName, hairType, diseasesProneTo,  size, availableForAdoption;
    int age, breedID;

    cout << "------------------------------------------"
         << "Enter the New Dog's Information"
         << "------------------------------------------";
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
    cin.ignore();
    getline(cin, dogDescription);



    prep_stmt = con->prepareStatement("INSERT INTO Dog_Profile (BreedID, DogName, Age, Size, AvailableForAdoption, Dog_Description) VALUES (?,?,?,?,?,?)");
    prep_stmt->setInt(1, breedID);
    prep_stmt->setString(2, dogName);
    prep_stmt->setInt(3, age);
    prep_stmt->setString(4, size);
    prep_stmt->setString(5, availableForAdoption);
    prep_stmt->setString(6, dogDescription);

    prep_stmt->executeUpdate();

    cout << "Dog added successfully!" << endl;
}

//CASE 2
void addCustomer(){ 
string custFName, custLName, Email, Cust_Address;
int PhoneNumber;

    cout << "------------------------------------------"
         << "Enter the New Customer's Information"
         << "------------------------------------------";
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

//CASE 3
void findDogbyid() {
     
 
 int id;
cout << "------------------------------------------"
     << "Find a dog by it's ID"
     << "------------------------------------------";
 cout << "Enter the Dog ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Dog_Profile WHERE DogID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     cout << "DogId | BreedId | DogName | Age | Size | AvailableForAdoption | Dog_Description | " <<endl;
     cout << res->getString("DogId") << "     |    ";
     cout << res->getString("BreedId") << "    | ";
     cout << res->getString("DogName") << "   | ";
     cout << res->getString("Age") << "   | ";
     cout << res->getString("Size") << "| ";
     cout << res->getString("AvailableForAdoption") << "                 |  ";
     cout << res->getString("Dog_Description") << endl;
 
 }
}

//CASE 4
void findCustomerbyid() {
     
 
 int id;

cout << "------------------------------------------"
     << "Find a customer by their ID"
     << "------------------------------------------";
 cout << "Enter the Customer ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Customer_Profile WHERE CustomerID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
 cout << "CustomerID | FirstName | LastName | PhoneNumber |      Email             | Cust_Address " <<endl;    
     cout << res->getString("CustomerID") << "          | ";
     cout << res->getString("FirstName") << "     | ";
     cout << res->getString("LastName") << "   | ";
     cout << res->getString("PhoneNumber") << " | ";
     cout << res->getString("Email") << " | ";
     cout << res->getString("Cust_Address") << endl;
 }
     
 }

//CASE 5
 void findAdoptionRecord(){    
 
 int id;
 cout << "------------------------------------------"
      << "Adoption Record Locator"
      << "------------------------------------------";
    
 cout << "Enter the Customer ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Adoption_Record WHERE CustomerID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
 cout << "AdoptionID | CustomerId | DogID | AdoptionDate |" <<endl;    
     cout << res->getString("AdoptionID") << "          | ";
     cout << res->getString("CustomerId") << "           | ";
     cout << res->getString("DogID") << "      | ";
     cout << res->getString("AdoptionDate") << endl;
 }
 }

//CASE 6
void findBreedInfo(){ 
 
 int id;
     cout << "------------------------------------------"
          << "Adoption Record Locator"
          << "------------------------------------------";
 cout << "Enter the Breed ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Breed_Info WHERE BreedID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
 cout << "BreedID | BreedName | HairType | DiseasesProneTo " <<endl;    
     cout << res->getString("BreedID") << "       | ";
     cout << res->getString("BreedName") << "   | ";
     cout << res->getString("HairType") << "   | ";
     cout << res->getString("DiseasesProneTo") << endl;
 }
 }

//CASE 7
void updateDogAge(){ 
 
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

//CASE 8
void deleteDog(){ 
 
 int id;
    
 cout << "Enter the Dog ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("Delete FROM Dog_Profile WHERE DogID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();

 cout << "Dog Deleted Successfully ";


 }

//CASE 9
void showAllDogs(){  
 

prep_stmt = con->prepareStatement("SELECT * FROM Dog_Profile");

res = prep_stmt->executeQuery();

 cout << "\n------------------------------------------"
      << "OUR DOGS"
      << "------------------------------------------" << endl;

cout << "DogId | BreedId | DogName | Age | Size | AvailableForAdoption | Dog_Description | " <<endl;
 while (res->next()) {

 /* Access column data by alias or column name */

     cout << res->getString("DogID") << "     | ";
     cout << res->getString("BreedID") << "       | ";
     cout << res->getString("DogName") << "    | ";
     cout << res->getString("Age") << "  | ";
     cout << res->getString("Size") << " | ";
     cout << res->getString("AvailableForAdoption") << "                   | ";
     cout << res->getString("Dog_Description") << endl;
 }
 }

//CASE 10
void showAllCustomers(){   
 

prep_stmt = con->prepareStatement("SELECT * FROM Customer_Profile");

res = prep_stmt->executeQuery();

cout << "------------------------------------------"
      << "OUR CUSTOMERS"
      << "------------------------------------------" << endl;

cout << "CustomerID | FirstName | LastName | PhoneNumber | Email | Cust_Address |" <<endl;    
 
 while (res->next()) {

 /* Access column data by alias or column name */
  
     cout << res->getString("CustomerID") << " | ";
     cout << res->getString("Firstname") << " | ";
     cout << res->getString("LastName") << " | ";
     cout << res->getString("PhoneNumber") << " | ";
     cout << res->getString("Email") << " | ";
     cout << res->getString("Cust_Address") << endl;
 }
 }

//CASE 11
void findall(){   
 
showAllCustomers();
showAllDogs();

 }
//CASE 12
 void totalDogs(){
    prep_stmt = con->prepareStatement("Select COUNT(DogID) AS TotalDogs FROM Dog_Profile");
    res = prep_stmt->executeQuery();

    while (res->next()){
        cout << "Total Dogs: " << res->getInt("TotalDogs") << endl;
    }
 }
