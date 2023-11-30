/*
Team: Pet Adoption
Group: Lauren Matthews, Alaisha Johnson, Joshua Douglas
*/

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
    Size TEXT,
    AvailableForAdoption TEXT NOT NULL,
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

INSERT INTO Customer_Profile (FirstName, LastName, PhoneNumber, Email, Cust_Address) VALUES 
('Jacob', 'Johnson', '(904)635-2476', 'jacob.johnson@gmail.com', '2654 Serail Dr, Tampa, FL'),
('Jane', 'Smith', '(967)654-3210', 'jane.smith@yahoo.com', '456 Oak St, Townburg, AL'),
('Bob', 'White', '(555)789-4561', 'bob.white@yahoo.com', '123 Main St, Houston, TX'),
('David', 'Brown', '(573)489-1045', 'david.brown@aol.com', '493 Rosey Dr, Lafayette, LA'),
('Lindsey', 'Harth', '(395)204-1894', 'lindsey.harth@gmail.com', '205 Pine St, Hamlet, TN');

INSERT INTO Breed_Info (BreedName, HairType, DiseasesProneTo) VALUES 
('Labrador', 'Short', 'Hip Dysplasia'),
('Poodle', 'Curly', 'Progressive Retinal Atrophy'),
('German Shepherd', 'Medium', 'Elbow Dysplasia'),
('Beagle', 'Short', 'Epilepsy'),
('Bulldog', 'Short', 'Respiratory Problems');

INSERT INTO Dog_Profile (BreedID, DogName, Age, Size, AvailableForAdoption, Dog_Description) VALUES 
(1, 'Buddy', 2, 'Medium', 'Yes', 'Very friendly and affectionate'),
(3, 'Rocky', 3, 'Large', 'Yes', 'Gorgeous and energetic dog'),
(4, 'Daisy', 1, 'Small', 'No', 'The sweetest dog with a bubbly personality'),
(5, 'Max', 4, 'Small', 'Yes', 'Happy dog with a warm personality'),
(2, 'Bella', 2, 'Medium', 'No', 'Calm and quiet dog that will bring peace to your life');

INSERT INTO Adoption_Record (CustomerID, DogID, AdoptionDate) VALUES 
(1, 3, '2022-01-15'),
(3, 5, '2022-08-02'),
(2, 3, '2023-05-18'),
(4, 5, '2023-09-20');

