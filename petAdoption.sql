DROP database IF EXISTS petAdoption;
CREATE database petAdoption;
USE petAdoption;

CREATE TABLE Customer_Profile(
    CustomerID INT NOT NULL AUTO_INCREMENT,
    FirstName TEXT NOT NULL,
    LastName TEXT NOT NULL,
    PhoneNumber TEXT,
    Email TEXT,
    Cust_Address TEXT,
    PRIMARY KEY (CustomerID)
);

CREATE TABLE Breed_Info(
    BreedID INT NOT NULL AUTO_INCREMENT,
    BreedName TEXT NOT NULL,
    HairType TEXT,
    DiseasesProneTo TEXT,
    PRIMARY KEY (BreedID)
);

CREATE TABLE Dog_Profile(
    DogID INT NOT NULL AUTO_INCREMENT,
    BreedID INT,
    DogName TEXT,
    Age INT,
    Size INT,
    AvailableForAdoption TINYINT(1),
    Dog_Description TEXT,
    PRIMARY KEY (DogID),
    FOREIGN KEY (BreedID) REFERENCES Breed_Info(BreedID)
);

CREATE TABLE Adoption_Record(
    AdoptionID INT NOT NULL AUTO_INCREMENT,
    CustomerID INT,
    DogID INT,
    AdoptionDate TEXT NOT NULL,
    PRIMARY KEY (AdoptionID),
    FOREIGN KEY (CustomerID) REFERENCES Customer_Profile(CustomerID),
    FOREIGN KEY (DogID) REFERENCES Dog_Profile(DogID)
);

