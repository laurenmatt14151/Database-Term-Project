/*
Team: Pet Adoption
Group: Lauren Matthews, Alaisha Johnson, Joshua Douglas
*/

#include <stdlib.h>
#include <iostream>
#include<string>
/*
 Include directly the different
 headers from cppconn/ and mysql_driver.h + mysql_util.h
 (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

// This program retrieves all of the musicians

// Compile:
// g++ -I/usr/include petapp.cpp -o petapp -I /usr/local/lib -lmysqlcppconn
// 
// Execute:
// ./petapp
// 
 sql::Driver *driver;
 sql::Connection *con;
 sql::Statement *stmt;
 sql::ResultSet *res;
 sql::PreparedStatement  *prep_stmt;

void addDog();
void addCustomer();
void findDogbyid();
void findCustomerbyid();
void findAdoptionRecord();
void findBreedInfo();
void showAllDogs();
void showAllCustomers();
void findall();

int main(void)
{

try {

   
 /* Create a connection */
 driver = get_driver_instance();

  
con = driver->connect("tcp://127.0.0.1:3306", "root", "");

/* Connect to the MySQL music database */
    
 con->setSchema("petAdoption");
 //stmt = con->createStatement();
    
 int option = 6;
 
 while (option != 0) {
     
     cout << endl;
     cout << "1. Add a Dog" << endl;
     cout << "2. Add a Customer" << endl;
     cout << "3. Find a Dog by id" << endl;
     cout << "4. Find a Customer by id" << endl;
     cout << "5. Find Adoption Record by Customer id" << endl;
     cout << "6. Find Breed info by Breed id" << endl;
     cout << "7. Show all Dogs" << endl;
     cout << "8. Show all Customers" << endl;
     cout << "9. Show all" << endl;
     cout << "0. Exit" << endl << endl;
     
     cout << "Choice : ";
     cin >> option;
     
     switch(option) {
         case 0: cout << "Exiting program..." << endl;
                 return EXIT_SUCCESS; 

         case 1: addDog();
                 break;  

         case 2: addCustomer();
                 break;             
                 
         case 3: findDogbyid();
                 break;
             
         case 4: findCustomerbyid();
                 break;
         
         case 5: findAdoptionRecord();
                 break;
         
         case 6: findBreedInfo();
                 break;             
        
         case 7: showAllDogs();
                 break;
         
         case 8: showAllCustomers();
                 break;             
                 
         case 9: findall();
                 break;             
             
             
     }
 }
 

 delete res;
 delete stmt;
 delete con;
} catch (sql::SQLException &e) {
 cout << "# ERR: SQLException in " << __FILE__;
 cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
 cout << "# ERR: " << e.what();
 cout << " (MySQL error code: " << e.getErrorCode();
 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}
cout << endl;
return EXIT_SUCCESS;

}
//case 1
void addDog(){ //incomplete
 
}

//case 2
void addCustomer(){    //incomplete
 
 
}

//case 3
void findDogbyid() {
     
 
 int id;
    
 cout << "Enter the Dog ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Dog_Profile WHERE DogID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("DogId") << " ";
     cout << res->getString("BreedId") << " ";
     cout << res->getString("DogName") << " ";
     cout << res->getString("Age") << " ";
     cout << res->getString("Size") << " ";
     cout << res->getString("AvailableForAdoption") << endl;
     cout << res->getString("Dog_Description") << endl;
 
 }
}

//case 4
void findCustomerbyid() {
     
 
 int id;
    
 cout << "Enter the Customer ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Customer_Profile WHERE CustomerID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("CustomerID") << " ";
     cout << res->getString("FirstName") << " ";
     cout << res->getString("LastName") << " ";
     cout << res->getString("PhoneNumber") << " ";
     cout << res->getString("Email") << endl;
     cout << res->getString("Cust_Address") << endl;
 }
     
 }

//case 5
 void findAdoptionRecord(){    
 
 int id;
    
 cout << "Enter the Customer ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Adoption_Record WHERE CustomerID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("AdoptionID") << " ";
     cout << res->getString("CustomerId") << " ";
     cout << res->getString("DogID") << " ";
     cout << res->getString("AdoptionDate") << " ";
 }
 }

//case 6
void findBreedInfo(){ 
 
 int id;
    
 cout << "Enter the Breed ID : ";
 cin >> id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Breed_Info WHERE BreedID = ?");
prep_stmt->setInt(1, id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("BreedID") << " ";
     cout << res->getString("BreedName") << " ";
     cout << res->getString("HairType") << " ";
     cout << res->getString("DiseasesProneTo") << " ";
 }
 }

//case 7
void showAllDogs(){  
 

prep_stmt = con->prepareStatement("SELECT * FROM Dog_Profile");

res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("DogID") << " ";
     cout << res->getString("BreedID") << " ";
     cout << res->getString("DogName") << " ";
     cout << res->getString("Age") << " ";
     cout << res->getString("Size") << " ";
     cout << res->getString("AvailableForAdoption") << " ";
     cout << res->getString("Dog_Description") << endl;
 }
 }

//case 8
void showAllCustomers(){   
 

prep_stmt = con->prepareStatement("SELECT * FROM Customer_Profile");

res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("CustomerID") << " ";
     cout << res->getString("Firstname") << " ";
     cout << res->getString("LastName") << " ";
     cout << res->getString("PhoneNumber") << " ";
     cout << res->getString("Email") << " ";
     cout << res->getString("Cust_Address") << endl;
 }
 }

//case 9
void findall(){   
 
showAllCustomers();
showAllDogs();

 }

 
