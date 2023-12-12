const express = require('express');
const mysql = require('mysql');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

// MySQL connection
const connection = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: '',
  database: 'petAdoption'
});

connection.connect(err => {
  if (err) throw err;
  console.log('Connected to MySQL Server!');
});


// void addDog()
app.post('/addDog', (req, res) => {
  const { dogName, breedID, age, size, availableForAdoption, dogDescription } = req.body;

  const query = 'INSERT INTO Dog_Profile (BreedID, DogName, Age, Size, AvailableForAdoption, Dog_Description) VALUES (?, ?, ?, ?, ?, ?)';
  connection.query(query, [breedID, dogName, age, size, availableForAdoption, dogDescription], (err, results) => {
    if (err) {
      res.status(500).send('Error adding dog');
      throw err;
    }
    res.status(200).send('Dog added successfully');
  });
});

// void addCustomer()
app.post('/addCustomer', (req, res) => {
    const { custFName, custLName, PhoneNumber, Email, Cust_Address } = req.body;
  
    const query = 'INSERT INTO Customer_Profile (FirstName, LastName, PhoneNumber, Email, Cust_Address) VALUES (?, ?, ?, ?, ?)';
    connection.query(query, [custFName, custLName, PhoneNumber, Email, Cust_Address], (err, results) => {
      if (err) {
        res.status(500).send('Error adding customer');
        throw err;
      }
      res.status(200).send('Customer added successfully');
    });
  });

// findDogById()
  app.get('/findDogById', (req, res) => {
    const id = req.query.id;
    const query = 'SELECT * FROM Dog_Profile WHERE DogID = ?';
    connection.query(query, [id], (err, results) => {
        if (err) {
            res.status(500).send('Error retrieving dog');
            throw err;
        }
        res.json(results);
    });
});

// findCustomerById()
app.get('/findCustomerById', (req, res) => {
    const id = req.query.id;
    const query = 'SELECT * FROM Customer_Profile WHERE CustomerID = ?';
    connection.query(query, [id], (err, results) => {
        if (err) {
            res.status(500).send('Error retrieving customer');
            throw err;
        }
        res.json(results);
    });
});

// findAdoptionRecord()
app.get('/findAdoptionRecord', (req, res) => {
    const id = req.query.id;
    const query = 'SELECT * FROM Adoption_Record WHERE CustomerID = ?';
    connection.query(query, [id], (err, results) => {
        if (err) {
            res.status(500).send('Error retrieving adoption record');
            throw err;
        }
        res.json(results);
    });
});

// findBreedInfo()
app.get('/findBreedInfo', (req, res) => {
    const id = req.query.id;
    const query = 'SELECT * FROM Breed_Info WHERE BreedID = ?';
    connection.query(query, [id], (err, results) => {
        if (err) {
            res.status(500).send('Error retrieving breed information');
            throw err;
        }
        res.json(results);
    });
});

// showAllDogs()
app.get('/showAllDogs', (req, res) => {
    const query = 'SELECT * FROM Dog_Profile';
    connection.query(query, (err, results) => {
        if (err) {
            res.status(500).send('Error retrieving all dogs');
            throw err;
        }
        res.json(results);
    });
});

// showAllCustomers()
app.get('/showAllCustomers', (req, res) => {
    const query = 'SELECT * FROM Customer_Profile';
    connection.query(query, (err, results) => {
        if (err) {
            res.status(500).send('Error retrieving all customers');
            throw err;
        }
        res.json(results);
    });
});

// findall()
app.get('/findall', async (req, res) => {
    try {
        const dogsQuery = 'SELECT * FROM Dog_Profile';
        const customersQuery = 'SELECT * FROM Customer_Profile';

        const dogs = await queryDatabase(dogsQuery);
        const customers = await queryDatabase(customersQuery);

        res.json({ dogs, customers });
    } catch (err) {
        res.status(500).send('Error retrieving all data');
    }
});

function queryDatabase(query) {
    return new Promise((resolve, reject) => {
        connection.query(query, (err, results) => {
            if (err) reject(err);
            else resolve(results);
        });
    });
}


const port = 3000;
app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});
